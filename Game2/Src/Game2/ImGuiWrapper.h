/******************************************************************************/
/*!
\file		ImGuiWrapper.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Contains the declaration of the ImGuiWrapper class.
			This file declares the ImGuiWrapper class, which provides 
			functionalities related to ImGui integration and handles ImGui
			events for the application.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "Event.h"
#include "InputEvent.h"
#include "AppEvent.h"
#include "EntityManager.h"

namespace Engine {
	class GAME2_API ImGuiWrapper {
	public:
		ImGuiWrapper();
		ImGuiWrapper(Engine::EntityManager* em) : entityManager(em) {}
		~ImGuiWrapper();
		inline void SetTargetEntity(Entity* entity) { targetEntity = entity; }
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
		inline Entity* TargetEntityGetter() { return targetEntity; }
		int selectedEntityIndex = 0;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent & e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


	private:
		float m_Time = 0.0f;
		Engine::EntityManager* entityManager;
		Entity* targetEntity = nullptr;

	};
}