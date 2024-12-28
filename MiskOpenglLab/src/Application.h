#pragma once
#include "Event/Event.h"
#include "Core/WindowWindows.h"

class Application {

public:
	Application();
	~Application();

	void run();
	void OnEvent(Misk::Event& e);

	inline static Application& Get() { return *m_Instanc; }
	inline Misk::WindowWindows& GetWindow() { return *m_Window; }
	bool OnWindowClose(Misk::WindowCloseEvent& e);

private:
	std::unique_ptr<Misk::WindowWindows> m_Window;

	bool m_Running = true;

	static Application* m_Instanc;
};
