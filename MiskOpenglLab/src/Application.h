#pragma once
#include "Event/Event.h"
#include "Core/WindowWindows.h"
#include "Core/LayerStack.h"
#include "Imgui/ImguiLayer.h"

namespace Misk {


	class Application {

	public:
		Application();
		~Application();

		void run();
		void OnEvent(Misk::Event& e);

		inline static Application& Get() { return *m_Instanc; }
		inline Misk::WindowWindows& GetWindow() { return *m_Window; }

		void PushLayer(Misk::Layer* layer);
		void PushOverlay(Misk::Layer* overlay);


		float GetYChange();
		float GetXChange();
	private:
		bool OnWindowClose(Misk::WindowCloseEvent& e);
		void OnMouseChange();
	private:
		std::unique_ptr<Misk::WindowWindows> m_Window;

		ImguiLayer* m_ImguiLayer;

		Misk::LayerStack m_LayerStack;
		bool m_Running = true;

		float m_LastTime;

		//Mouse property
		struct MouseProp {
			float lastX;
			float lastY;
			float xChange;
			float yChange;
			bool firstMove = true;
		};

		MouseProp m_MouseProp;

		static Application* m_Instanc;
	};
}
