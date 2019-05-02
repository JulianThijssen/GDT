#include "Window.h"

#include "OpenGL.h"
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>

void onError(int error, const char* description)
{
    switch (error) {
    case GLFW_NOT_INITIALIZED:
        std::cerr << "A window function was called while the window was not initialized" << std::endl;
    case GLFW_NO_CURRENT_CONTEXT:
        std::cerr << "A window function was called that depends on OpenGL, but no GL context is set" << std::endl;
    case GLFW_INVALID_ENUM:
        std::cerr << "A window function was called with an invalid argument enum" << std::endl;
    case GLFW_INVALID_VALUE:
        std::cerr << "A window function was called with an invalud argument value" << std::endl;
    case GLFW_OUT_OF_MEMORY:
        std::cerr << "A window function caused a failed memory allocation" << std::endl;
    case GLFW_API_UNAVAILABLE:
        std::cerr << "The window could not find support for the requested API" << std::endl;
    case GLFW_VERSION_UNAVAILABLE:
        std::cerr << "The requested OpenGL version is not available on this machine" << std::endl;
    case GLFW_PLATFORM_ERROR:
        std::cerr << "A window function caused a platform error" << std::endl;
    case GLFW_FORMAT_UNAVAILABLE:
        std::cerr << "The requested pixel format is not supported or the contents of the clipboard could not be converted to the requested format" << std::endl;
    }
}

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    w->onKeyInput(key, action, mods);
}

void onMouseMoveEvent(GLFWwindow* window, double x, double y)
{
    Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    w->onMouseMove(x, y);
}

void onMouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
    Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    w->onMouseButton(button, action, mods);
}

uint Window::getWidth() const
{
    return _width;
}

uint Window::getHeight() const
{
    return _height;
}

void Window::create(std::string title, uint width, uint height)
{
    _width = width;
    _height = height;

    // Attempts to initialize the GLFW library and displays an error message if it fails
    if (!glfwInit())
        throw WindowCreationException("Failed to initialize GLFW");

    glfwSetErrorCallback(onError);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _glSettings.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _glSettings.minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, _glSettings.coreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwSetWindowPos(window, 100, 100);

    // If we failed to create a window, throw an exception
    if (!window)
        throw WindowCreationException("Failed to create GLFW window");

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, onKeyEvent);
    glfwSetCursorPosCallback(window, onMouseMoveEvent);
    glfwSetMouseButtonCallback(window, onMouseButtonEvent);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::update()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::close()
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::destroy()
{
    glfwDestroyWindow(window);

    glfwTerminate();
}

void Window::setGlVersion(uint majorVersion, uint minorVersion, bool coreProfile)
{
    _glSettings = GlSettings{ majorVersion, minorVersion, coreProfile };
}

void Window::setResizable(bool resizable)
{
    glfwWindowHint(GLFW_RESIZABLE, resizable);
}

void Window::lockCursor(bool lock)
{
    if (lock)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::enableVSync(bool enable)
{
    glfwSwapInterval(enable ? 1 : 0);
}

void Window::addKeyListener(KeyListener* keyListener)
{
    keyListeners.push_back(keyListener);
}

void Window::addMouseMoveListener(MouseMoveListener* mouseMoveListener)
{
    mouseMoveListeners.push_back(mouseMoveListener);
}

void Window::addMouseClickListener(MouseClickListener* mouseClickListener)
{
    mouseClickListeners.push_back(mouseClickListener);
}

void Window::onKeyInput(int key, int action, int mods)
{
    //keyListeners.erase(std::remove_if(keyListeners.begin(), keyListeners.end(),
    //    [](KeyListener* listener) { return listener == nullptr; }), keyListeners.end());

    for (KeyListener* listener : keyListeners)
    {
        if (action == GLFW_PRESS)
            listener->onKeyPressed(key, mods);
        else if (action == GLFW_RELEASE)
            listener->onKeyReleased(key, mods);
    }
}

void Window::onMouseMove(float x, float y)
{
    for (MouseMoveListener* listener : mouseMoveListeners)
    {
        listener->onMouseMove(x, y);
    }
}

void Window::onMouseButton(int button, int action, int mods)
{
    for (MouseClickListener* listener : mouseClickListeners)
    {
        if (action == GLFW_PRESS)
            listener->onMouseClicked(button, mods);
        else if (action == GLFW_RELEASE)
            listener->onMouseReleased(button, mods);
    }
}
