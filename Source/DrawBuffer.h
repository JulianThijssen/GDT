#pragma once

#include "OpenGL.h"

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    class DrawBuffer
    {
    public:
        virtual void clear(int location) = 0;
    private:

    };

    class FloatBuffer : public DrawBuffer
    {
    public:
        virtual void clear(int location) override
        {
            glClearBufferfv(GL_COLOR, location, clearColor);
        }
    private:
        float clearColor[4];
    };
#ifdef GDT_NAMESPACE
}
#endif
