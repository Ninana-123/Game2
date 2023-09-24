#pragma once
#include "Event.h"

namespace Engine {
	class GAME2_API ImGuiWrapper {
	public:
		ImGuiWrapper();
		~ImGuiWrapper();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;

	};
}