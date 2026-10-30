#pragma once
#include <array>
#include <cstdint>
#include <vector>
#include <stdexcept>
namespace daybreak {
// d3dx9_25.dll 0x4898d5..0x489968: loader's initial face expansion.
// Geometry-independent even for nonplanar or concave polygons.
inline std::vector<std::array<std::uint32_t,3>> expand_x_polygon(const std::vector<std::uint32_t>& indices,std::uint32_t vertex_count){
    if(indices.size()<3)throw std::runtime_error("X polygon needs at least three indices");
    for(auto index:indices)if(index>=vertex_count)throw std::runtime_error("X polygon index out of range");
    std::vector<std::array<std::uint32_t,3>> result;result.reserve(indices.size()-2);
    for(std::size_t i=1;i+1<indices.size();++i)result.push_back({indices[0],indices[i],indices[i+1]});return result;
}
}
