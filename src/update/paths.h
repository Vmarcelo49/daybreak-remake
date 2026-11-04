#pragma once
// update/paths.h — the one path rule set for update manifests and archive entries.
//
// A manifest drives updates on Windows and Linux, and a layout change may move files
// between them, so the rules are the intersection of both filesystems (docs/AUTO-UPDATE.md):
// NTFS-reserved characters and device names, no component ending in '.' or a space, no two
// entries differing only in ASCII case, and no file that is also a directory of another
// entry. tools/package_manifest.py implements the same rules and the cross-check test runs
// both on the same fixtures, so the two halves cannot drift.
#include <string>
#include <vector>

namespace update {
namespace paths {

// One relative path: no absolute form, no drive letter, no '..', no control characters,
// no NTFS-reserved character, no component ending in '.' or a space, no device name.
bool validRelative(const std::string& path, std::string* error);

// The rules a single path cannot see, over a whole file set.
bool validSet(const std::vector<std::string>& paths, std::string* error);

// The case fold both this and the Python tool use. ASCII only on purpose: NTFS's own
// case-insensitivity for ASCII names is what a package actually collides on, and folding
// non-ASCII would need a Unicode table to stay in step with the Python side.
std::string foldCase(const std::string& path);

}  // namespace paths
}  // namespace update
