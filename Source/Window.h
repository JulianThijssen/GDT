#pragma once

#include <exception>
#include <string>

typedef unsigned int uint;

class WindowCreationException : public std::exception
{
public:
    WindowCreationException(std::string errorMessage)
        : errorMessage(errorMessage)
    { }

    virtual const char* what() const throw()
    {
        return errorMessage.c_str();
    }

private:
    std::string errorMessage;
};

struct GLFWwindow;

class Window
{
public:
    uint getWidth() const;
    uint getHeight() const;

    void create(std::string title, uint width, uint height);
    void update();
    bool shouldClose();
    void close();
    void destroy();

private:
    GLFWwindow* window;

    uint _width, _height;
};
