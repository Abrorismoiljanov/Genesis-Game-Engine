#pragma once
#include "Asset.h"
#include "memory"
#include "TextureAsset.h"

class MaterialAsset: public Asset{
public:
    std::shared_ptr<TextureAsset> texture; 

    MaterialAsset(const std::shared_ptr<TextureAsset>& tex = nullptr)
        : texture(tex) 
    {
        Type = AssetType::Material; // mark type
    }

    void SetTexture(const std::shared_ptr<TextureAsset>& tex) {
        texture = tex;
    }

    std::shared_ptr<TextureAsset> GetTexture() const {
        return texture;
    }
};
