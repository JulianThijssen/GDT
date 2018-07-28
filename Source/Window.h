#pragma once

#include "Input.h"

#include <vector>
#include <string>
#include <exception>

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

    void lockCursor(bool lock);

    void addKeyListener(KeyListener* keyListener);
    void addMouseMoveListener(MouseMoveListener* mouseMoveListener);
    void addMouseClickListener(MouseClickListener* mouseClickListener);

    void onKeyInput(int key, int action, int mods);
    void onMouseMove(float x, float y);
    void onMouseButton(int button, int action, int mods);

private:
    GLFWwindow* window;

    uint _width, _height;

    // Non-owning lists of input listener pointer references
    std::vector<KeyListener*> keyListeners;
    std::vector<MouseMoveListener*> mouseMoveListeners;
    std::vector<MouseClickListener*> mouseClickListeners;
};
