#!/usr/bin/env python3
"""Tests for `tools/release_sign` (issue #100).

The tool signs the release's update manifest with the owner's offline key, so it has to
produce standard Ed25519 (not a variant), sign exact bytes, refuse a misconfigured key
and never overwrite a key that already exists. RFC 8032 §7.1's first two vectors pin
the algorithm; throwaway keys in a temp directory cover the rest. The real release key
is never generated here.

Run through CTest (`ctest -R release_sign_test`) or directly:
    python3 tests/release_sign_test.py build/linux/release_sign
"""

import stat
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

if len(sys.argv) < 2:
    print("usage: release_sign_test.py <path to release_sign>", file=sys.stderr)
    sys.exit(2)
TOOL = Path(sys.argv.pop(1)).resolve()

# RFC 8032 §7.1. The secret key file holds Monocypher's 64-byte secret key, which is
# the RFC's 32-byte seed followed by the public half — so the RFC's values are exactly
# what the tool's own key file format carries.
RFC_TEST_1 = {
    "seed": "9d61b19deffd5a60ba844af492ec2cc44449c5697b326919703bac031cae7f60",
    "public": "d75a980182b10ab7d54bfed3c964073a0ee172f3daa62325af021a68f707511a",
    "message": b"",
    "signature": "e5564300c360ac729086e2cc806e828a84877f1eb8e5d974d873e06522490155"
                 "5fb8821590a33bacc61e39701cf9b46bd25bf5f0595bbe24655141438e7a100b",
}
RFC_TEST_2 = {
    "seed": "4ccd089b28ff96da9db6c346ec114e0f5b8a319f35aba624da8cf6ed4fb8a6fb",
    "public": "3d4017c3e843895a92b70aa74d1b7ebc9c982ccf2ec4968cc0cd55f12af4660c",
    "message": b"\x72",
    "signature": "92a009a9f0d4cab8720e820b5f642540a2b27b5416503f8fb3762223ebdb69da"
                 "085ac1e43e15996e458f3613d0f11d8c387b2eaeb4302aeeb00d291612bb0c00",
}


class ReleaseSignTest(unittest.TestCase):
    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory(prefix="release-sign-test-")
        self.root = Path(self._tmp.name)

    def tearDown(self):
        self._tmp.cleanup()

    def run_tool(self, *args):
        return subprocess.run([str(TOOL), *args], capture_output=True, text=True)

    def keygen(self, name="release"):
        secret = self.root / (name + ".release-secret")
        public = self.root / (name + ".pub")
        result = self.run_tool(
            "keygen", "--secret=" + str(secret), "--public=" + str(public)
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        return secret, public

    def write(self, name, data):
        path = self.root / name
        path.write_bytes(data)
        return path

    def test_keygen_writes_a_0600_secret_and_a_hex_public_key(self):
        secret, public = self.keygen()
        self.assertEqual(stat.S_IMODE(secret.stat().st_mode), 0o600)
        secret_text = secret.read_text()
        public_text = public.read_text()
        self.assertRegex(secret_text, r"\A[0-9a-f]{128}\n\Z")
        self.assertRegex(public_text, r"\A[0-9a-f]{64}\n\Z")

    def test_sign_verify_round_trip(self):
        secret, public = self.keygen()
        message = self.write("update-manifest.txt", b"format = 1\nversion = 1.0.0\n")
        result = self.run_tool("sign", "--secret=" + str(secret), str(message))
        self.assertEqual(result.returncode, 0, result.stderr)
        signature = Path(str(message) + ".sig")
        self.assertRegex(signature.read_text(), r"\A[0-9a-f]{128}\n\Z")

        from_file = self.run_tool(
            "verify", "--public=" + str(public), str(message), str(signature)
        )
        self.assertEqual(from_file.returncode, 0, from_file.stderr)
        self.assertIn("signature valid", from_file.stdout)

        from_hex = self.run_tool(
            "verify", "--public=" + public.read_text().strip(), str(message),
            str(signature),
        )
        self.assertEqual(from_hex.returncode, 0, from_hex.stderr)

    def test_signature_covers_exact_bytes(self):
        secret, public = self.keygen()
        message = self.write("manifest.txt", b"a\n")
        self.assertEqual(
            self.run_tool("sign", "--secret=" + str(secret), str(message)).returncode, 0
        )
        without_newline = self.write("other.txt", b"a")
        result = self.run_tool(
            "verify", "--public=" + str(public), str(without_newline),
            str(message) + ".sig",
        )
        self.assertEqual(result.returncode, 3)
        self.assertIn("INVALID", result.stderr)

    def test_flipped_file_byte_fails(self):
        secret, public = self.keygen()
        message = self.write("manifest.txt", b"format = 1\n")
        self.assertEqual(
            self.run_tool("sign", "--secret=" + str(secret), str(message)).returncode, 0
        )
        message.write_bytes(b"format = 2\n")
        result = self.run_tool(
            "verify", "--public=" + str(public), str(message), str(message) + ".sig"
        )
        self.assertEqual(result.returncode, 3)
        self.assertIn("INVALID", result.stderr)

    def test_flipped_signature_byte_fails(self):
        secret, public = self.keygen()
        message = self.write("manifest.txt", b"format = 1\n")
        self.assertEqual(
            self.run_tool("sign", "--secret=" + str(secret), str(message)).returncode, 0
        )
        signature = Path(str(message) + ".sig")
        text = signature.read_text()
        flipped = ("0" if text[0] != "0" else "1") + text[1:]
        signature.write_text(flipped)
        result = self.run_tool(
            "verify", "--public=" + str(public), str(message), str(signature)
        )
        self.assertEqual(result.returncode, 3)

    def test_wrong_public_key_fails(self):
        secret, public = self.keygen("first")
        other_secret, other_public = self.keygen("second")
        message = self.write("manifest.txt", b"format = 1\n")
        self.assertEqual(
            self.run_tool("sign", "--secret=" + str(secret), str(message)).returncode, 0
        )
        result = self.run_tool(
            "verify", "--public=" + str(other_public), str(message),
            str(message) + ".sig",
        )
        self.assertEqual(result.returncode, 3)
        self.assertIn("INVALID", result.stderr)

    def test_keygen_refuses_to_overwrite(self):
        secret, public = self.keygen()
        secret_before = secret.read_bytes()
        public_before = public.read_bytes()
        result = self.run_tool(
            "keygen", "--secret=" + str(secret), "--public=" + str(public)
        )
        self.assertEqual(result.returncode, 2)
        self.assertIn("refusing to overwrite", result.stderr)
        self.assertEqual(secret.read_bytes(), secret_before)
        self.assertEqual(public.read_bytes(), public_before)

    def test_sign_refuses_a_group_readable_secret(self):
        secret, _ = self.keygen()
        message = self.write("manifest.txt", b"x")
        secret.chmod(0o640)
        result = self.run_tool("sign", "--secret=" + str(secret), str(message))
        self.assertEqual(result.returncode, 2)
        self.assertIn("group or others", result.stderr)

    def test_sign_refuses_a_world_readable_secret(self):
        secret, _ = self.keygen()
        message = self.write("manifest.txt", b"x")
        secret.chmod(0o644)
        result = self.run_tool("sign", "--secret=" + str(secret), str(message))
        self.assertEqual(result.returncode, 2)
        self.assertIn("group or others", result.stderr)

    def rfc_vector(self, vector, name):
        secret = self.root / (name + ".release-secret")
        secret.write_text(vector["seed"] + vector["public"] + "\n")
        secret.chmod(0o600)
        message = self.write(name + ".bin", vector["message"])
        result = self.run_tool("sign", "--secret=" + str(secret), str(message))
        self.assertEqual(result.returncode, 0, result.stderr)
        signature = Path(str(message) + ".sig")
        self.assertEqual(signature.read_text().strip(), vector["signature"])
        check = self.run_tool(
            "verify", "--public=" + vector["public"], str(message), str(signature)
        )
        self.assertEqual(check.returncode, 0, check.stderr)

    def test_rfc8032_test1_matches_the_known_signature(self):
        self.rfc_vector(RFC_TEST_1, "rfc1")

    def test_rfc8032_test2_matches_the_known_signature(self):
        self.rfc_vector(RFC_TEST_2, "rfc2")

    def test_verify_rejects_a_short_public_key(self):
        message = self.write("manifest.txt", b"x")
        result = self.run_tool(
            "verify", "--public=" + "a" * 63, str(message), str(message) + ".sig"
        )
        self.assertEqual(result.returncode, 2)

    def test_sign_rejects_a_truncated_secret(self):
        secret, _ = self.keygen()
        message = self.write("manifest.txt", b"x")
        secret.write_text("a" * 126 + "\n")
        result = self.run_tool("sign", "--secret=" + str(secret), str(message))
        self.assertEqual(result.returncode, 2)
        self.assertIn("128 lowercase hex", result.stderr)

    def test_usage_errors(self):
        self.assertEqual(self.run_tool().returncode, 1)
        self.assertEqual(self.run_tool("nonsense").returncode, 1)
        self.assertEqual(self.run_tool("sign", str(self.root)).returncode, 1)


if __name__ == "__main__":
    unittest.main(verbosity=2)
