#pragma once

#include "Input.h"

#include <vector>
#include <string>
#include <exception>

typedef unsigned int uint;

struct GLFWwindow;

#ifdef GDT_NAMESPACE
namespace GDT
{
#endif
    class ResizeListener
    {
    public:
        virtual void onWindowResized(int width, int height) = 0;
    };

    class WindowCreationException : public std::exception
    {
    public:
        WindowCreationException(std::string errorMessage)
            : errorMessage(errorMessage)
        { }

        const char *what() const noexcept override
        {
            return errorMessage.c_str();
        }

    private:
        std::string errorMessage;
    };

    struct GlSettings
    {
        uint majorVersion;
        uint minorVersion;
        bool coreProfile;
    };

    class Window
    {
    public:
        uint getWidth() const;
        uint getHeight() const;

        void create(std::string title, uint width, uint height);
        void pollEvents();
        void swapBuffers();
        void update();
        bool shouldClose();
        void close();
        void destroy();

        void setGlVersion(uint majorVersion, uint minorVersion, bool coreProfile);
        void setResizable(bool resizable);
        void lockCursor(bool lock);
        void enableVSync(bool enable);

        void addResizeListener(ResizeListener* resizeListener);
        void addKeyListener(KeyListener* keyListener);
        void addMouseMoveListener(MouseMoveListener* mouseMoveListener);
        void addMouseClickListener(MouseClickListener* mouseClickListener);
        void addMouseScrollListener(MouseScrollListener* mouseScrollListener);

        void onResize(int width, int height);
        void onKeyInput(int key, int action, int mods);
        void onMouseMove(float x, float y);
        void onMouseButton(int button, int action, int mods);
        void onMouseScroll(float xOffset, float yOffset);

    private:
        GLFWwindow* window;

        uint _width, _height;
        int _fbWidth, _fbHeight;

        // Window properties
        GlSettings _glSettings = { 3, 3, true };
        bool _resizable;

        // Non-owning lists of input listener pointer references
        std::vector<ResizeListener*> resizeListeners;
        std::vector<KeyListener*> keyListeners;
        std::vector<MouseMoveListener*> mouseMoveListeners;
        std::vector<MouseClickListener*> mouseClickListeners;
        std::vector<MouseScrollListener*> mouseScrollListeners;
    };
#ifdef GDT_NAMESPACE
}
#endif
