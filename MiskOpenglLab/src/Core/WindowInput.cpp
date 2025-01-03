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
