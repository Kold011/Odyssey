#include "Input.h"
#include "Logger.h"
#include "Window.h"

namespace Odyssey
{
    void Input::Initialize()
    {
        keyInput[KeyState::Up].reset();
        keyInput[KeyState::Press].reset();
    }

    bool Input::GetKeyPress(KeyCode keyCode)
    {
        return keyInput[KeyState::Press][keyCode];
    }

    bool Input::GetKeyDown(KeyCode keyCode)
    {
        return keyInput[KeyState::Down][keyCode];
    }

    bool Input::GetKeyUp(KeyCode keyCode)
    {
        return keyInput[KeyState::Up][keyCode];
    }

    bool Input::GetMouseButtonDown(MouseButton button)
    {
        return mouseInput[button];
    }

    glm::vec2 Input::GetScreenSpaceMousePosition()
    {
        return Window::GetWindowPos() + glm::vec2(mouseX, mouseY);
    }

    void Input::Update()
    {
        prevMouseX = mouseX;
        prevMouseY = mouseY;

        mouseAxisH = (mouseX - prevMouseX);
        mouseAxisV = (mouseY - prevMouseY);
    }

    void Input::RegisterKeyPress(int key, int scanCode)
    {
        // Flag as key press and down
        keyInput[KeyState::Press][key] = true;
        keyInput[KeyState::Down][key] = true;

        // Clear key up
        keyInput[KeyState::Up][key] = false;
    }

    void Input::RegisterKeyDown(int key, int scanCode)
    {
        // Flag as key down
        keyInput[KeyState::Down][key] = true;

        // Clear key press and up
        keyInput[KeyState::Press][key] = false;
        keyInput[KeyState::Up][key] = false;
    }

    void Input::RegisterKeyUp(int key, int scanCode)
    {
        // Flag as key up
        keyInput[KeyState::Up][key] = true;

        // Clear key press and down
        keyInput[KeyState::Press][key] = false;
        keyInput[KeyState::Down][key] = false;
    }

    void Input::RegisterMouseMove(double x, double y)
    {
        prevMouseX = mouseX;
        prevMouseY = mouseY;

        mouseX = x;
        mouseY = y;

        mouseAxisH = (mouseX - prevMouseX);
        mouseAxisV = (mouseY - prevMouseY);
    }

    void Input::RegisterMousePosition(double x, double y, bool entered)
    {
        if (entered)
        {
            mouseX = prevMouseX = x;
            mouseY = prevMouseY = y;
        }
        else
        {
            mouseX = mouseY = prevMouseX = prevMouseY = 0.0;
        }
    }

    void Input::RegisterMouseClick(MouseButton button, bool pressed)
    {
        mouseInput[button] = pressed;
    }
}