#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <filesystem>
#include <string>
#include <vector>

namespace daybreak {
struct ArchiveEntry { std::string name; std::uint32_t size, offset; };
class LegacyArchive {
    std::ifstream file_;
    std::vector<ArchiveEntry> entries_;
    static std::uint32_t u32(const std::uint8_t* p) {
        return std::uint32_t(p[0]) | std::uint32_t(p[1])<<8 | std::uint32_t(p[2])<<16 | std::uint32_t(p[3])<<24;
    }
public:
    // 0x662d10: uint16 count; count * 268 byte XOR-obfuscated index.
    // Port patch (PATCHES.md): path is UTF-8, which a narrow open misreads on Windows.
    explicit LegacyArchive(const std::string& path):file_(std::filesystem::u8path(path),std::ios::binary) {
        if(!file_) throw std::runtime_error("Cannot open archive");
        file_.seekg(0,std::ios::end);
        auto end=file_.tellg();
        if(end<2) throw std::runtime_error("Truncated archive header");
        auto size=static_cast<std::uint64_t>(end);
        file_.seekg(0);
        std::uint8_t header[2]; file_.read(reinterpret_cast<char*>(header),2);
        std::size_t count=header[0]|std::size_t(header[1])<<8;
        std::size_t index_size=count*268;
        if(index_size+2>size) throw std::runtime_error("Truncated archive index");
        std::vector<std::uint8_t> index(index_size);
        if(index_size && !file_.read(reinterpret_cast<char*>(index.data()),index_size)) throw std::runtime_error("Index read failed");
        std::uint8_t key=100,step=100;
        for(auto& b:index) {b^=key; key=std::uint8_t(key+step); step=std::uint8_t(step+77);}
        for(std::size_t i=0;i<count;++i) {
            const auto* p=index.data()+i*268;
            auto nul=std::find(p,p+260,0);
            if(nul==p+260) throw std::runtime_error("Unterminated archive name");
            ArchiveEntry entry{std::string(reinterpret_cast<const char*>(p),nul-p),u32(p+260),u32(p+264)};
            if(entry.offset<index_size+2 || std::uint64_t(entry.offset)+entry.size>size)
                throw std::runtime_error("Archive entry outside payload area");
            entries_.push_back(std::move(entry));
        }
    }
    const std::vector<ArchiveEntry>& entries() const {return entries_;}
    // 0x663030: payload XOR byte depends on absolute entry offset, not read position.
    // Reads are bounded and do not reproduce the original unchecked ReadFile behavior.
    std::vector<std::uint8_t> read(std::size_t entry_index,std::uint32_t relative,std::size_t requested) {
        const auto& e=entries_.at(entry_index);
        if(relative>e.size) throw std::out_of_range("Read starts beyond entry");
        std::size_t n=std::min(requested,std::size_t(e.size-relative));
        std::vector<std::uint8_t> bytes(n);
        file_.clear(); file_.seekg(std::uint64_t(e.offset)+relative);
        if(!file_ || (n && !file_.read(reinterpret_cast<char*>(bytes.data()),n))) throw std::runtime_error("Payload read failed");
        auto key=std::uint8_t((e.offset>>1)|8);
        for(auto& b:bytes) b^=key;
        return bytes;
    }
};
}
