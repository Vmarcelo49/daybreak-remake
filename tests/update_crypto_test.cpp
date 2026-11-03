#include "update_test_suites.h"

#include <array>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "update/crypto.h"

namespace {

using update_test::check;
using update_test::expect;

// RFC 8032 §7.1. The seed alone must reproduce both the public key and the signature, so
// these vectors prove the wrapper is standard Ed25519 and not a variant.
const char* const kTest1Public =
    "d75a980182b10ab7d54bfed3c964073a0ee172f3daa62325af021a68f707511a";
const char* const kTest1Signature =
    "e5564300c360ac729086e2cc806e828a84877f1eb8e5d974d873e065224901555fb8821590a33"
    "bacc61e39701cf9b46bd25bf5f0595bbe24655141438e7a100b";
const char* const kTest2Public =
    "3d4017c3e843895a92b70aa74d1b7ebc9c982ccf2ec4968cc0cd55f12af4660c";
const char* const kTest2Signature =
    "92a009a9f0d4cab8720e820b5f642540a2b27b5416503f8fb3762223ebdb69da085ac1e43e159"
    "96e458f3613d0f11d8c387b2eaeb4302aeeb00d291612bb0c00";

std::array<std::uint8_t, 32> keyFromHex(const std::string& hex) {
    std::array<std::uint8_t, 32> key{};
    for (std::size_t index = 0; index < key.size(); ++index) {
        if (index * 2 + 1 >= hex.size()) break;
        key[index] = static_cast<std::uint8_t>(
            std::stoi(hex.substr(index * 2, 2), nullptr, 16));
    }
    return key;
}

void testRfc8032() {
    const std::array<std::uint8_t, 32> key1 = keyFromHex(kTest1Public);
    const std::array<std::uint8_t, 32> key2 = keyFromHex(kTest2Public);

    const update::SignatureCheck test1 =
        update::verifySignature({key1}, std::string(kTest1Signature) + "\n", nullptr, 0);
    check(test1.ok && test1.keyIndex == 0, "RFC 8032 TEST 1 verifies");

    const std::uint8_t message2 = 0x72;
    const update::SignatureCheck test2 =
        update::verifySignature({key2}, std::string(kTest2Signature) + "\n", &message2, 1);
    check(test2.ok && test2.keyIndex == 0, "RFC 8032 TEST 2 verifies");

    check(!update::verifySignature({key1}, std::string(kTest2Signature) + "\n", &message2, 1)
               .ok,
          "TEST 2's signature fails under TEST 1's key");
    check(!update::verifySignature({key2}, std::string(kTest1Signature) + "\n", nullptr, 0)
               .ok,
          "TEST 1's signature fails under TEST 2's key");

    const update::SignatureCheck second =
        update::verifySignature({key1, key2}, std::string(kTest2Signature) + "\n",
                                &message2, 1);
    check(second.ok && second.keyIndex == 1, "the second trusted key matches");

    std::string flipped = kTest1Signature;
    flipped[0] = flipped[0] == '0' ? '1' : '0';
    check(!update::verifySignature({key1}, flipped + "\n", nullptr, 0).ok,
          "a flipped signature byte fails");

    std::string flippedMessage = "x";
    check(!update::verifySignature({key1}, std::string(kTest1Signature) + "\n",
                                   flippedMessage.data(), flippedMessage.size())
               .ok,
          "a flipped message byte fails");

    const std::vector<std::string> malformed = {
        std::string(),
        kTest1Signature,                      // no newline
        std::string(kTest1Signature) + "\n\n",  // two newlines
        std::string(kTest1Signature) + " ",     // space instead of newline
        std::string(128, 'A') + "\n",           // uppercase hex
        std::string(126, 'a') + "\n",           // too short
    };
    for (const std::string& signature : malformed) {
        check(!update::verifySignature({key1}, signature, nullptr, 0).ok,
              "a malformed signature file is refused");
    }
    check(!update::verifySignature({}, std::string(kTest1Signature) + "\n", nullptr, 0).ok,
          "an empty key list refuses everything");
}

std::string readFile(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(input),
                       std::istreambuf_iterator<char>());
}

bool runCommand(const std::string& command) {
    return std::system(command.c_str()) == 0;
}

// The release tool and the game's verifier must agree on the key-file and .sig formats;
// this signs with a throwaway key through tools/release_sign and verifies here.
void testReleaseSign(const char* tool) {
    if (tool == nullptr || tool[0] == '\0') {
        std::printf("update_crypto_test: release_sign cross-check skipped (no binary)\n");
        return;
    }
    namespace fs = std::filesystem;
    std::error_code code;
    const fs::path directory = fs::temp_directory_path(code) / "daybreak-update-crypto-test";
    fs::remove_all(directory, code);
    fs::create_directories(directory, code);
    const fs::path secret = directory / "test.release-secret";
    const fs::path publicKey = directory / "test.pub";
    const fs::path message = directory / "update-manifest.txt";
    {
        std::ofstream output(message, std::ios::binary);
        output << "format = 1\nversion = 1.0.0\nnotes = https://example.invalid/\n";
    }
    const std::string quote = "\"";
    const std::string binary = quote + tool + quote;
    check(runCommand(binary + " keygen --secret=" + quote + secret.string() + quote +
                     " --public=" + quote + publicKey.string() + quote + " >/dev/null"),
          "release_sign keygen runs");
    check(runCommand(binary + " sign --secret=" + quote + secret.string() + quote +
                     " --expect-public=" + quote + publicKey.string() + quote + " " +
                     quote + message.string() + quote + " >/dev/null"),
          "release_sign sign runs");

    const std::string publicText = readFile(publicKey);
    const std::string signatureText = readFile(fs::path(message.string() + ".sig"));
    const std::string messageText = readFile(message);
    check(publicText.size() == 65 && publicText.back() == '\n',
          "the public key file is 64 hex characters and a newline");
    check(signatureText.size() == 129 && signatureText.back() == '\n',
          "the .sig is 128 hex characters and a newline");

    const update::SignatureCheck signedMessage = update::verifySignature(
        {keyFromHex(publicText.substr(0, 64))}, signatureText, messageText.data(),
        messageText.size());
    check(signedMessage.ok, "a release_sign signature verifies in the game's verifier");

    std::string tampered = messageText;
    tampered.back() = 'X';
    check(!update::verifySignature({keyFromHex(publicText.substr(0, 64))}, signatureText,
                                   tampered.data(), tampered.size())
               .ok,
          "a changed manifest fails against the same signature");

    fs::remove_all(directory, code);
}

}  // namespace

int runUpdateCryptoTests(int argc, char** argv) {
    testRfc8032();
    testReleaseSign(argc > 1 ? argv[1] : nullptr);
    return update_test::report("update_crypto_test");
}

#ifndef DAYBREAK_UPDATE_SELFTEST
int main(int argc, char** argv) {
    return runUpdateCryptoTests(argc, argv);
}
#endif
