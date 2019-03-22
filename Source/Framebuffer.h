#pragma once

#include "OpenGL.h"
#include "Texture.h"

#include <vector>

class Framebuffer
{
public:
    Framebuffer() :
        _handle(0),
        colorTexture(MAX_COLOR_ATTACHMENTS)
    {

    }

    void create();
    void destroy();

    void bind() const;
    void release() const;

    void addColorTexture(unsigned int colorAttachment, Texture2D texture);
    void addDepthTexture(Texture2D texture);
    void addDepthStencilTexture(Texture2D texture);
    void setDrawBufferCount(unsigned int drawBufferCount);

    void validate() const;

private:
    const unsigned int MAX_COLOR_ATTACHMENTS = 8;

    GLuint _handle;

    std::vector<Texture2D> colorTexture;

    Texture2D _depthTexture;
};
