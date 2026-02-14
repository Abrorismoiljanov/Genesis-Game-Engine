#pragma once
#include "cstdint"
#include "string"

enum class AssetType : uint16_t
{
    None = 0,
    Texture,
    Mesh,
    Shader,
    Material,
    Model
};
 
using AssetHandle = uint64_t;
static constexpr AssetHandle INVALID_ASSET = 0;

class Asset{    
public:
 
    AssetHandle Handle = INVALID_ASSET;
    AssetType Type  = AssetType::None;

    std::string Path;
    virtual ~Asset() = default;
};
