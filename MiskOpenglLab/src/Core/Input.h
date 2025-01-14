#pragma once

#include "Core.h"
#include <utility>

#include "KeyCode.h"

namespace Misk {


	class   Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return m_Instance->IsKeyPressedImpl(keycode); }
		static bool IsKeyPressedOnce(int keycode) { return m_Instance->IsKeyPressedOnceImpl(keycode); }
		static bool IsMouseButtonPressed(int button) { return m_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return m_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return m_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return m_Instance->GetMouseYImpl(); }


	protected:
		virtual bool IsKeyPressedImpl(int keycode);
		virtual bool IsKeyPressedOnceImpl(int keycode);
		virtual bool IsMouseButtonPressedImpl(int button);
		virtual std::pair<float, float> GetMousePositionImpl();
		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();

	private:
		static Input* m_Instance;
	};
}


