#include "Texture.h"

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    Texture::Texture(GLenum target)
        : target(target)
    {

    }

    void Texture::create()
    {
        glGenTextures(1, &handle);

        created = true;
    }

    void Texture::bind(TextureUnit textureUnit) const
    {
        if (!isCreated()) return; // TODO Handle

        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(target, handle);
    }

    void Texture::release()
    {
        glBindTexture(target, 0);
    }

    void Texture::setSampling(Sampling minFilter, Sampling magFilter, Sampling mipFilter)
    {
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter == NEAREST ? GL_NEAREST : GL_LINEAR);

        switch (mipFilter)
        {
        case NONE:    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter == NEAREST ? GL_NEAREST : GL_LINEAR); break;
        case NEAREST: glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter == NEAREST ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_NEAREST); break;
        case LINEAR:  glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter == NEAREST ? GL_NEAREST_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_LINEAR); break;
        }
    }

    void Texture::destroy()
    {
        if (!created) return;

        glDeleteTextures(1, &handle);

        created = false;
    }

    bool Texture::isCreated() const
    {
        return created;
    }

    GLuint Texture::getHandle() const
    {
        return handle;
    }

    Texture2D::Texture2D()
        : Texture(GL_TEXTURE_2D)
    {

    }

    uint Texture2D::getWidth() const
    {
        return width;
    }

    uint Texture2D::getHeight() const
    {
        return height;
    }

    void Texture2D::setData(uint width, uint height, GLint internalFormat, GLenum format, GLenum type, const void* data)
    {
        if (!isCreated()) return;

        this->width = width;
        this->height = height;

        glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
    }

    void Texture2D::setWrapping(Wrapping sWrapping, Wrapping tWrapping)
    {
        glTexParameteri(target, GL_TEXTURE_WRAP_S, sWrapping);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, tWrapping);
    }
#ifdef GDT_NAMESPACE
}
#endif
