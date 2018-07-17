#include "Texture.h"

#include "TextureUnit.h"

Texture::Texture(GLenum target)
    : target(target)
{

}

void Texture::create()
{
    glGenTextures(1, &handle);

    created = true;
}

void Texture::bind(TextureUnit textureUnit)
{
    if (!isCreated()) return; // TODO Handle

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

bool Texture::isCreated()
{
    return created;
}

void Texture::destroy()
{
    if (!created) return;

    glDeleteTextures(1, &handle);

    created = false;
}

Texture2D::Texture2D()
    : Texture(GL_TEXTURE_2D)
{

}

void Texture2D::setData(uint width, uint height, GLint internalFormat, GLenum format, GLenum type, const void* data)
{
    if (!isCreated()) return;

    this->width = width;
    this->height = height;

    glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
}
