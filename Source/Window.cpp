#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void onError(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
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
