#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void onError(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, onKeyEvent);
    glfwSetCursorPosCallback(window, onMouseMoveEvent);
    glfwSetMouseButtonCallback(window, onMouseButtonEvent);
    // If we failed to create a window, throw an exception
    if (!window)
        throw WindowCreationException("Failed to create GLFW window");
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
    glfwSetWindowShouldClose(window, true);
}

void Window::destroy()
{
    glfwDestroyWindow(window);

    glfwTerminate();
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
        else
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
        else
            listener->onMouseReleased(button, mods);
    }
}
