#pragma once
#include "cstdint"

class FrameBuffer{
public:
    void Create(uint32_t w, uint32_t h);
    void Bind();
    void UnBind();
    void Resize(uint32_t w, uint32_t h);

    uint32_t GetColorAttachment() const { return m_ColorAttachment; }
private:    
    uint32_t m_FBO = 0;
    uint32_t m_ColorAttachment = 0;
    uint32_t m_DepthAttachment = 0;

    uint32_t m_Width = 0;
    uint32_t m_Height = 0;

};
