#pragma once
#include "Asset.h"
#include "GL/glew.h"
#include "DataTypes/outside/stb_image.h"
#include "vector"

class TextureAsset : public Asset{
public:

    int width = 0, height = 0;
    std::vector<unsigned char> pixels;

    int Width = 0;
    int Height = 0;
    
    bool LoadFromFile(const std::string& path) {
        Type = AssetType::Texture;
        this->Path = path;   
        this->Type = AssetType::Texture;
        int w, h, c;
        unsigned char* data = stbi_load(path.c_str(), &w, &h, &c, 4);
        if (!data) return false;
        width = w; height = h;
        Width = width;
        Height = height;
        pixels.assign(data, data + (w * h * 4));
        stbi_image_free(data);
        return true;
    }
};
