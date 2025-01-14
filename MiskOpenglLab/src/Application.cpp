#include "mkpch.h"
#include "Application.h"
#include "Core/Input.h"
#include <glad/glad.h>


void CheckOpenGLVersion()
{
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	std::cout << "OpenGL Version: " << version << std::endl;
	std::cout << "GLSL Version: " << glslVersion << std::endl;

	GLint major = 0, minor = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	std::cout << "OpenGL Version (Parsed): " << major << "." << minor << std::endl;

	GLint profileMask;
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profileMask);

	if (profileMask & GL_CONTEXT_CORE_PROFILE_BIT)
	{
		std::cout << "Core Profile is active." << std::endl;
	}
	else if (profileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
	{
		std::cout << "Compatibility Profile is active." << std::endl;
	}
	else
	{
		std::cout << "Unknown Profile." << std::endl;
	}
}

namespace Misk {


	Application* Application::m_Instanc = nullptr;

	Application::Application()
	{
		MK_CORE_ASSERT(!m_Instanc, "there is already an insttance of the application");
		MK_CORE_TRACE("the super constructure is called!");
		m_Instanc = this;
		m_Window = std::unique_ptr<Misk::WindowWindows>(Misk::WindowWindows::Create());
		m_Window->SetEventCallBack(MK_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);
		m_ImguiLayer = new ImguiLayer();
		PushOverlay(m_ImguiLayer);

	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		glEnable(GL_DEPTH_TEST); // Add this in your setup if depth is not needed.
		CheckOpenGLVersion();

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Misk::Timestep timestep = time - m_LastTime;
			m_LastTime = time;

			OnMouseChange();
			if (Misk::Input::IsKeyPressed(MK_KEY_ESCAPE))
				m_Running = false;
			//Set clear color 
			//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			// Clear both color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer

			m_ImguiLayer->Begin();
			for (Misk::Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImguiRender();
			}
			m_ImguiLayer->End();



			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Misk::Event& e)
	{
		Misk::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Misk::WindowCloseEvent>(MK_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(Misk::WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}


	void Application::PushLayer(Misk::Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Misk::Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}


	float Application::GetYChange()
	{
		float theChange = m_MouseProp.yChange;
		m_MouseProp.yChange = 0.0f;
		return theChange;
	}

	float Application::GetXChange()
	{
		float theChange = m_MouseProp.xChange;
		m_MouseProp.xChange = 0.0f;
		return theChange;
	}


	void Application::OnMouseChange()
	{
		auto window = static_cast<GLFWwindow*>(this->GetWindow().GetNativeWindow());
		auto [x, y] = Misk::Input::GetMousePosition();
		if (m_MouseProp.firstMove)
		{
			m_MouseProp.lastX = x;
			m_MouseProp.lastY = y;
			m_MouseProp.firstMove = false;
		}

		m_MouseProp.xChange = x - m_MouseProp.lastX;
		m_MouseProp.yChange = m_MouseProp.lastY - y;

		m_MouseProp.lastX = x;
		m_MouseProp.lastY = y;
	}
}