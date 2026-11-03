// tools/release_sign/main.cpp — sign a release's update-manifest.txt offline (issue #100).
//
// Why this is a host tool rather than part of the game: the private key must never
// reach GitHub or CI, because the whole point of the signature is that a compromised
// GitHub account (or a stolen token) cannot publish an update. The owner runs this on
// their own machine when publishing and keeps the key offline; the game only ever
// carries the public key. docs/AUTO-UPDATE.md has the trust model, and
// docs/RELEASE-CHECKLIST.md the publishing procedure.
//
//   release_sign keygen --secret=<path> --public=<path>
//   release_sign sign   --secret=<path> <file>
//   release_sign verify --public=<hex or path> <file> <sig>
//
// Key files are hex so they diff and paste cleanly: the secret is the 32-byte seed as
// 64 lowercase hex characters, the public key is the derived 32 bytes as 64, and a
// signature file holds 64 bytes as 128. The seed is stored alone on purpose: `sign`
// derives both halves with crypto_ed25519_key_pair, so a hand-edited file cannot carry a
// public half that does not belong to its seed. Ed25519 signs the file's exact bytes —
// no normalisation, no trimming — so the signed artifact is byte-for-byte what the
// updater reads.
//
// Exit codes are part of the interface, because the release checklist is a script:
// 0 success, 1 usage, 2 file or format error, 3 invalid signature.

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <map>
#include <string>
#include <vector>

#include <fcntl.h>
#include <sys/random.h>
#include <sys/stat.h>
#include <unistd.h>

#include "monocypher.h"
#include "monocypher-ed25519.h"

namespace {

constexpr const char* kTool = "release_sign";

enum ExitCode : int {
    kOk = 0,
    kUsage = 1,
    kFailure = 2,
    kInvalid = 3,
};

[[noreturn]] void fail(int code, const std::string& message) {
    std::fprintf(stderr, "%s: %s\n", kTool, message.c_str());
    std::exit(code);
}

void usage(std::FILE* stream) {
    std::fprintf(stream,
                 "usage: release_sign keygen --secret=<path> --public=<path>\n"
                 "       release_sign sign   --secret=<path> [--expect-public=<hex or path>] <file>\n"
                 "       release_sign verify --public=<hex or path> <file> <sig>\n"
                 "\n"
                 "Ed25519-signs a file's exact bytes; sign writes <file>.sig.\n"
                 "A 64-character hex --public is taken as the key itself, anything else\n"
                 "as a key file. Exit codes: 0 success, 1 usage, 2 file or format error,\n"
                 "3 invalid signature. Formats: docs/AUTO-UPDATE.md.\n");
}

std::string hex_encode(const uint8_t* bytes, size_t size) {
    static const char kDigits[] = "0123456789abcdef";
    std::string text(size * 2, '\0');
    for (size_t i = 0; i < size; ++i) {
        text[i * 2] = kDigits[bytes[i] >> 4];
        text[i * 2 + 1] = kDigits[bytes[i] & 0x0F];
    }
    return text;
}

int hex_digit(char character) {
    if (character >= '0' && character <= '9') return character - '0';
    if (character >= 'a' && character <= 'f') return character - 'a' + 10;
    return -1;
}

bool hex_decode(const std::string& text, uint8_t* bytes, size_t size) {
    if (text.size() != size * 2) return false;
    for (size_t i = 0; i < size; ++i) {
        const int high = hex_digit(text[i * 2]);
        const int low = hex_digit(text[i * 2 + 1]);
        if (high < 0 || low < 0) return false;
        bytes[i] = static_cast<uint8_t>((high << 4) | low);
    }
    return true;
}

std::string strip_one_newline(std::string text) {
    if (!text.empty() && text.back() == '\n') text.pop_back();
    return text;
}

std::vector<uint8_t> read_bytes(const std::string& path) {
    struct stat info {};
    if (::stat(path.c_str(), &info) != 0) {
        fail(kFailure, "cannot stat " + path + ": " + std::strerror(errno));
    }
    if (!S_ISREG(info.st_mode)) {
        fail(kFailure, path + " is not a regular file");
    }
    std::FILE* file = std::fopen(path.c_str(), "rb");
    if (file == nullptr) {
        fail(kFailure, "cannot open " + path + ": " + std::strerror(errno));
    }
    std::vector<uint8_t> bytes(static_cast<size_t>(info.st_size));
    size_t total = 0;
    while (total < bytes.size()) {
        const size_t count =
            std::fread(bytes.data() + total, 1, bytes.size() - total, file);
        if (count == 0) break;
        total += count;
    }
    const bool read_failed = std::ferror(file) != 0;
    std::fclose(file);
    if (read_failed) fail(kFailure, "cannot read " + path + ": " + std::strerror(errno));
    if (total != bytes.size()) fail(kFailure, path + " changed while it was being read");
    return bytes;
}

std::string read_text(const std::string& path) {
    const std::vector<uint8_t> bytes = read_bytes(path);
    return std::string(bytes.begin(), bytes.end());
}

void write_all(int fd, const std::string& text, const std::string& path) {
    size_t written = 0;
    while (written < text.size()) {
        const ssize_t count =
            ::write(fd, text.data() + written, text.size() - written);
        if (count < 0) {
            if (errno == EINTR) continue;
            const int saved = errno;
            ::close(fd);
            fail(kFailure, "cannot write " + path + ": " + std::strerror(saved));
        }
        written += static_cast<size_t>(count);
    }
}

// `exclusive` is the key-handling rule: a secret key file is created with O_EXCL so a
// second keygen can never silently replace a key the owner has already backed up.
void write_file(const std::string& path, const std::string& text, mode_t mode,
                bool exclusive) {
    const int flags = O_WRONLY | O_CREAT | O_CLOEXEC | (exclusive ? O_EXCL : O_TRUNC);
    const int fd = ::open(path.c_str(), flags, mode);
    if (fd < 0) {
        if (exclusive && errno == EEXIST) {
            fail(kFailure, "refusing to overwrite " + path +
                               " (delete it yourself if that is really intended)");
        }
        fail(kFailure, "cannot create " + path + ": " + std::strerror(errno));
    }
    write_all(fd, text, path);
    // The mode is set on the descriptor too, so a permissive umask cannot widen a key.
    if (::fchmod(fd, mode) != 0) {
        const int saved = errno;
        ::close(fd);
        fail(kFailure, "cannot set the mode of " + path + ": " + std::strerror(saved));
    }
    if (::fsync(fd) != 0) {
        const int saved = errno;
        ::close(fd);
        fail(kFailure, "cannot flush " + path + ": " + std::strerror(saved));
    }
    if (::close(fd) != 0) {
        fail(kFailure, "cannot close " + path + ": " + std::strerror(errno));
    }
}

void fill_random(uint8_t* bytes, size_t size) {
    size_t filled = 0;
    while (filled < size) {
        const ssize_t count = ::getrandom(bytes + filled, size - filled, 0);
        if (count < 0) {
            if (errno == EINTR) continue;
            fail(kFailure, std::string("getrandom failed: ") + std::strerror(errno));
        }
        filled += static_cast<size_t>(count);
    }
}

struct Args {
    std::map<std::string, std::string> values;
    std::vector<std::string> files;
};

Args parse(int argc, char** argv) {
    Args args;
    for (int i = 2; i < argc; ++i) {
        const std::string argument = argv[i];
        if (argument.rfind("--", 0) == 0) {
            const size_t equals = argument.find('=');
            if (equals == std::string::npos) {
                fail(kUsage, "option " + argument + " needs a value (--name=value)");
            }
            args.values[argument.substr(2, equals - 2)] = argument.substr(equals + 1);
        } else {
            args.files.push_back(argument);
        }
    }
    return args;
}

void allow_only(const Args& args, std::initializer_list<const char*> allowed) {
    for (const auto& item : args.values) {
        bool known = false;
        for (const char* name : allowed) {
            if (item.first == name) known = true;
        }
        if (!known) fail(kUsage, "unknown option --" + item.first);
    }
}

std::string require(const Args& args, const char* name) {
    const auto found = args.values.find(name);
    if (found == args.values.end() || found->second.empty()) {
        fail(kUsage, std::string("--") + name + "=<path> is required");
    }
    return found->second;
}

void expect_files(const Args& args, size_t count) {
    if (args.files.size() != count) {
        fail(kUsage, "this command takes " + std::to_string(count) + " file argument(s)");
    }
}

// A public key is either 64 hex characters or a file holding them. `flag` names the
// option in the error, because both `verify --public` and `sign --expect-public` use it.
void read_public_key(const std::string& argument, uint8_t public_key[32], const char* flag) {
    if (argument.size() == 64) {
        if (!hex_decode(argument, public_key, 32)) {
            fail(kFailure, std::string(flag) + " is 64 characters but not lowercase hex");
        }
        return;
    }
    std::string text = strip_one_newline(read_text(argument));
    if (!hex_decode(text, public_key, 32)) {
        crypto_wipe(text.data(), text.size());
        fail(kFailure, argument +
                           " does not hold a 32-byte public key as 64 lowercase hex "
                           "characters");
    }
    crypto_wipe(text.data(), text.size());
}

void keygen(const Args& args) {
    allow_only(args, {"secret", "public"});
    expect_files(args, 0);
    const std::string secret_path = require(args, "secret");
    const std::string public_path = require(args, "public");

    uint8_t seed[32];
    fill_random(seed, sizeof seed);
    // The file holds the seed, not Monocypher's expanded 64-byte key: the public half is
    // derivable, and storing a second copy is what let a hand-edited file sign with a
    // mismatched half.
    std::string secret_text = hex_encode(seed, sizeof seed) + "\n";
    uint8_t secret_key[64];
    uint8_t public_key[32];
    crypto_ed25519_key_pair(secret_key, public_key, seed);  // also wipes `seed`
    crypto_wipe(seed, sizeof seed);
    crypto_wipe(secret_key, sizeof secret_key);

    // The secret is written first, and its path is printed before the public key is
    // written: if the public path is unwritable, the output still names the secret file
    // the owner has to delete before re-running. A public key whose secret was never
    // written would be the worse failure.
    write_file(secret_path, secret_text, 0600, true);
    crypto_wipe(secret_text.data(), secret_text.size());
    std::printf("%s: wrote %s (secret, mode 0600)\n", kTool, secret_path.c_str());
    write_file(public_path, hex_encode(public_key, sizeof public_key) + "\n", 0644, false);
    std::printf("%s: wrote %s\n", kTool, public_path.c_str());
    std::printf("%s: public key: %s\n", kTool,
                hex_encode(public_key, sizeof public_key).c_str());
}

void sign(const Args& args) {
    allow_only(args, {"secret", "expect-public"});
    expect_files(args, 1);
    const std::string secret_path = require(args, "secret");
    const std::string file_path = args.files[0];
    const auto expected = args.values.find("expect-public");
    if (expected != args.values.end() && expected->second.empty()) {
        fail(kUsage, "--expect-public=<hex or path> needs a value");
    }

    struct stat info {};
    if (::stat(secret_path.c_str(), &info) != 0) {
        fail(kFailure, "cannot stat " + secret_path + ": " + std::strerror(errno));
    }
    if (!S_ISREG(info.st_mode)) {
        fail(kFailure, secret_path + " is not a regular file");
    }
    // A group- or world-accessible secret is not a secret. Refuse before reading it,
    // so a misconfigured key fails the release instead of being used.
    if ((info.st_mode & 0077) != 0) {
        char mode[8];
        std::snprintf(mode, sizeof mode, "%04o",
                      static_cast<unsigned>(info.st_mode & 07777));
        fail(kFailure, secret_path + " is accessible by group or others (mode " + mode +
                           "); it must be 0600");
    }

    std::string text = strip_one_newline(read_text(secret_path));
    uint8_t seed[32];
    if (!hex_decode(text, seed, sizeof seed)) {
        crypto_wipe(seed, sizeof seed);
        fail(kFailure, secret_path +
                           " does not hold the 32-byte seed as 64 lowercase hex "
                           "characters (a 128-character file is the old, expanded-key "
                           "format; regenerate the key)");
    }
    crypto_wipe(text.data(), text.size());

    uint8_t secret_key[64];
    uint8_t public_key[32];
    crypto_ed25519_key_pair(secret_key, public_key, seed);  // also wipes `seed`
    crypto_wipe(seed, sizeof seed);

    if (expected != args.values.end()) {
        uint8_t expected_key[32];
        read_public_key(expected->second, expected_key, "--expect-public");
        if (std::memcmp(expected_key, public_key, sizeof expected_key) != 0) {
            crypto_wipe(secret_key, sizeof secret_key);
            fail(kFailure, "--expect-public " + hex_encode(expected_key, 32) +
                               " is not the key of " + secret_path + ", which derives " +
                               hex_encode(public_key, 32));
        }
    }

    const std::vector<uint8_t> message = read_bytes(file_path);
    static const uint8_t kEmptyMessage = 0;
    const uint8_t* bytes = message.empty() ? &kEmptyMessage : message.data();

    uint8_t signature[64];
    crypto_ed25519_sign(signature, secret_key, bytes, message.size());
    crypto_wipe(secret_key, sizeof secret_key);

    // A bad key must fail here, not in every player's game: check what was produced
    // against the public key derived from the same seed before writing anything.
    if (crypto_ed25519_check(signature, public_key, bytes, message.size()) != 0) {
        fail(kFailure, "the signature does not verify against the key derived from " +
                           secret_path + "; refusing to write " + file_path + ".sig");
    }

    const std::string signature_path = file_path + ".sig";
    write_file(signature_path, hex_encode(signature, sizeof signature) + "\n", 0644, false);
    std::printf("%s: signed %s -> %s (public key %s)\n", kTool, file_path.c_str(),
                signature_path.c_str(), hex_encode(public_key, sizeof public_key).c_str());
}

void verify(const Args& args) {
    allow_only(args, {"public"});
    expect_files(args, 2);
    const std::string public_argument = require(args, "public");
    const std::string file_path = args.files[0];
    const std::string signature_path = args.files[1];

    uint8_t public_key[32];
    read_public_key(public_argument, public_key, "--public");

    std::string signature_text = strip_one_newline(read_text(signature_path));
    uint8_t signature[64];
    if (!hex_decode(signature_text, signature, sizeof signature)) {
        fail(kFailure, signature_path +
                           " does not hold a 64-byte signature as 128 lowercase hex "
                           "characters");
    }

    const std::vector<uint8_t> message = read_bytes(file_path);
    static const uint8_t kEmptyMessage = 0;
    const uint8_t* bytes = message.empty() ? &kEmptyMessage : message.data();
    if (crypto_ed25519_check(signature, public_key, bytes, message.size()) != 0) {
        fail(kInvalid, "signature is INVALID for " + file_path +
                           " (wrong key, or the file changed)");
    }
    std::printf("%s: signature valid: %s\n", kTool, file_path.c_str());
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        usage(stderr);
        return kUsage;
    }
    const std::string command = argv[1];
    if (command == "help" || command == "--help" || command == "-h") {
        usage(stdout);
        return kOk;
    }
    const Args args = parse(argc, argv);
    if (command == "keygen") {
        keygen(args);
        return kOk;
    }
    if (command == "sign") {
        sign(args);
        return kOk;
    }
    if (command == "verify") {
        verify(args);
        return kOk;
    }
    fail(kUsage, "unknown command " + command);
}
