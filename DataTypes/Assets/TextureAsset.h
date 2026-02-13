#pragma once
#include "stb_image.h"
#include <string>
#include <GL/glew.h>
#include "iostream"

class TextureAsset {
public:
    std::string Path;
    unsigned int ID = 0;
    int Width = 0, Height = 0, Channels = 0;

    TextureAsset(const std::string& path)
        : Path(path)
    {
        Load();
    }

    void Load() {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(Path.c_str(), &Width, &Height, &Channels, 0);
        if (!data) {
            std::cerr << "Failed to load texture: " << Path << std::endl;
            return;
        }

        GLenum format = GL_RGB;
        if (Channels == 1) format = GL_RED;
        else if (Channels == 3) format = GL_RGB;
        else if (Channels == 4) format = GL_RGBA;

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, Width, Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }

    void Bind(int slot = 0) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, ID);
    }
};
