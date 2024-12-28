#include "mkpch.h"
#include "Application.h"
#include "Core/Input.h"
#include <glad/glad.h>

Application* Application::m_Instanc = nullptr;

Application::Application()
{
	MK_CORE_ASSERT(!m_Instanc, "there is already an insttance of the application");
	m_Instanc = this;
	m_Window = std::unique_ptr<Misk::WindowWindows>(Misk::WindowWindows::Create());
	m_Window->SetEventCallBack(MK_BIND_EVENT_FN(Application::OnEvent));
	m_Window->SetVSync(false);
}

Application::~Application()
{
}

void Application::run()
{

	while (m_Running) {
		if (Misk::Input::IsKeyPressed(MK_KEY_ESCAPE))
			m_Running = false;
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// Clear both color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Added clearing depth buffer
		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Misk::Event& e)
{
	Misk::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Misk::WindowCloseEvent>(MK_BIND_EVENT_FN(Application::OnWindowClose));
}

bool Application::OnWindowClose(Misk::WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}
