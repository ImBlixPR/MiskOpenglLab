#include "mkpch.h"

#include <GLFW/glfw3.h>
#include "../Application.h"
#include "Core/Input.h"


namespace Misk {

    Input* Input::m_Instance = new Input();

    bool Input::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return (state == GLFW_PRESS)|| (state == GLFW_REPEAT);
    }

bool Input::IsKeyPressedOnceImpl(int keycode) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);

    // Check if the key is pressed and hasn't been processed yet
    if (state == GLFW_PRESS) {
        if (keysBool[keycode]) {
            return false; // Key has already been processed
        } else {
            keysBool[keycode] = true; // Mark the key as processed
            return true; // First time pressing the key
        }
    } else {
        // Reset the key's processed state when it is released
        keysBool[keycode] = false;
        return false;
    }
}

    bool Input::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return (state == GLFW_PRESS);
    }

    std::pair<float, float> Input::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double ypos, xpos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float Input::GetMouseXImpl()
    {
        auto [x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseYImpl()
    {
        auto [x, y] = GetMousePosition();
        return y;
    }

}
