#pragma once
#include "legacy_archive.hpp"
#include <filesystem>
#include <memory>
#include <unordered_map>

namespace daybreak {
// 0x663c20 uses _stricmp for archive keys. Preserve the C-locale ASCII byte fold;
// do not normalize separators or resolve filesystem paths inside archive names.
inline std::string archive_name_key(std::string name){
    for(char& c:name)if(c>='A' && c<='Z')c=static_cast<char>(c-'A'+'a');
    return name;
}
// Explicit ordered mount list; the caller selects a resource group.
// 0x653d40 inserts before the list end; 0x653540 searches begin -> end.
class AssetSearchPath {
    struct Mount {
        std::string path;
        LegacyArchive archive;
        std::unordered_map<std::string,std::size_t> indices;
        explicit Mount(const std::string& p):path(p),archive(p) {
            for(std::size_t i=0;i<archive.entries().size();++i) indices.emplace(archive_name_key(archive.entries()[i].name),i);
        }
    };
    std::vector<std::unique_ptr<Mount>> mounts_;
    std::unordered_map<std::string,std::string> loose_;
public:
    void append(const std::string& archive) {mounts_.push_back(std::make_unique<Mount>(archive));}
    // Port patch (PATCHES.md): the web build has no archives. Its delivery client writes each
    // decoded payload at its archive name under root, so the same keys resolve to loose files.
    void index_directory(const std::string& root) {
        namespace fs=std::filesystem;
        const fs::path base(root);
        std::error_code ec;
        for(fs::recursive_directory_iterator it(base/"data",ec),end;!ec && it!=end;it.increment(ec))
            if(it->is_regular_file(ec)) loose_.emplace(archive_name_key(fs::relative(it->path(),base,ec).generic_string()),it->path().string());
    }
    struct Asset {std::string archive;std::vector<std::uint8_t> bytes;};
    bool contains(const std::string& name)const{const auto key=archive_name_key(name);if(loose_.count(key))return true;for(const auto& mount:mounts_)if(mount->indices.count(key))return true;return false;}
    Asset read(const std::string& name) {
        const auto key=archive_name_key(name);
        for(auto& mount:mounts_) {
            auto it=mount->indices.find(key);
            if(it!=mount->indices.end()) return {mount->path,mount->archive.read(it->second,0,mount->archive.entries()[it->second].size)};
        }
        auto it=loose_.find(key);
        if(it!=loose_.end()) {
            std::ifstream file(it->second,std::ios::binary);
            if(!file) throw std::runtime_error("Loose asset read failed: "+name);
            return {it->second,std::vector<std::uint8_t>((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>())};
        }
        throw std::runtime_error("Asset not found: "+name);
    }
};
}
