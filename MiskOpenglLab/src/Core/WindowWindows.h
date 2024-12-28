#pragma once


#include <GLFW/glfw3.h>
#include <string>

//event header
#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"
//#include "Misk/Platform/OpenGl/OpenglContext.h"




namespace Misk
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(std::string title = "Misk Engine", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{

		}
	};

	class WindowWindows
	{
	public:
		WindowWindows(const WindowProps& props);
		virtual ~WindowWindows();
		using EventCallBackFn = std::function<void(Event&)>;
		void OnUpdate();
		void MouseOn(bool mouseOn);

		inline unsigned int GetWidth() const  { return m_Data.Width; }
		inline unsigned int GetHeight() const  { return m_Data.Height; }
		//window attribute 
		virtual void SetEventCallBack(const EventCallBackFn& callBack)  { m_Data.EventCallBack = callBack; }
		virtual void SetVSync(bool enabled) ;
		virtual bool IsVSync() const ;

		//getter and setter
		inline float GetLastX() { return m_LastX; }
		inline float GetLastY() { return m_LastY; }
		float GetYChange();
		float GetXChange();
		inline void SetLastX(float lastX) { m_LastX = lastX; }
		inline void SetLastY(float lastY) { m_LastY = lastY; }
		inline void SetYChange(float YChange) { m_YChange = YChange; }
		inline void SetXChange(float XChange) { m_XChange = XChange; }

		//my things temp
		inline virtual GLFWwindow* GetNativeWindow() const  { return m_Window; }

		static WindowWindows* Create(const WindowProps& props = WindowProps());
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		float m_LastX;
		float m_LastY;
		float m_XChange;
		float m_YChange;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallBackFn EventCallBack;
		};

		//OpenglContext* context;
		WindowData m_Data;
	};
}
