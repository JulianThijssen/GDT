#include "Framebuffer.h"

#include "Texture.h"

#include <iostream>

void Framebuffer::create()
{
    glGenFramebuffers(1, &_handle);
}

void Framebuffer::destroy()
{
    glDeleteFramebuffers(1, &_handle);
}

void Framebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _handle);
}

void Framebuffer::bind(BindTarget bindTarget) const
{
    glBindFramebuffer(bindTarget, _handle);
}

void Framebuffer::release() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::addColorTexture(unsigned int colorAttachment, Texture2D texture) {
    if (colorAttachment > MAX_COLOR_ATTACHMENTS) {
        std::cout << "Tried to add color attachment with index greater than 8." << std::endl;
        return;
    }
    colorTexture[colorAttachment] = texture;
    GLenum attachment = GL_COLOR_ATTACHMENT0 + colorAttachment;
    glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture.handle, 0);

    GLenum attachments[1] = { attachment };
    glDrawBuffers((GLsizei) 1, attachments);
}

void Framebuffer::addDepthTexture(Texture2D texture)
{
    _depthTexture = texture;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture.handle, 0);
}

void Framebuffer::addDepthStencilTexture(Texture2D texture)
{
    _depthTexture = texture;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, texture.handle, 0);
}

void Framebuffer::setDrawBufferCount(unsigned int drawBufferCount)
{
    std::vector<GLenum> attachments;
    for (int i = 0; i < drawBufferCount; i++)
    {
        attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
    }
    glDrawBuffers((GLsizei)drawBufferCount, attachments.data());
}

void Framebuffer::validate() const {
    GLuint error = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (error != GL_FRAMEBUFFER_COMPLETE) {
        switch (error) {
        case GL_FRAMEBUFFER_UNDEFINED:
            std::cout << "Target is the default framebuffer, but the default framebuffer does not exist" << std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cout << "Any of the framebuffer attachment points are framebuffer incomplete" << std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cout << "The framebuffer does not have any texture attached to it" << std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cout << "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi" << std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cout << "GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER" << std::endl; break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cout << "The combination of internal formats of the attached textures violates an implementation-dependent set of restrictions." << std::endl; break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            std::cout << "The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers" << std::endl; break;
        default:
            std::cout << "There is a problem with the framebuffer" << std::endl;
        }
    }
}
