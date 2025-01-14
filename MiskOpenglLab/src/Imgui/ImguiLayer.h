#pragma once



#include "Core/Layer.h"
#include "imgui.h"

#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/ApplicationEvent.h "


namespace Misk {


	class   ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDettach() override;
		void OnImguiRender() override;
		inline static ImGuiContext* GetImguiContext() { return m_ctx; }

		void Begin();
		void End();



	private:
		float m_Time = 0.0f;
		ImVec4 clear_color;
		static ImGuiContext* m_ctx;
	};



}
