#pragma once
#include "Asset.h"
#include "GL/glew.h"
#include "stb_image.h"
#include "vector"

class TextureAsset : public Asset{
public:

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

    

    void UploadToGPU() {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        pixels.clear(); 
    }

    GLuint ID = 0;
    int width = 0, height = 0;
    std::vector<unsigned char> pixels;
};
