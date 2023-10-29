/******************************************************************************/
/*!
\file		ImGuiWrapper.h
\author 	Liu Xujie
\co			Tristan Tham Rui Hong

\par    	email: l.xujie@digipen.edu
				   t.tham@digipen.edu
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
#include "PrefabManager.h"

namespace Engine {

	class GAME2_API ImGuiWrapper {
	public:
		ImGuiWrapper();
		ImGuiWrapper(std::shared_ptr<Engine::EntityManager> em, Engine::PrefabManager* pm) : entityManager(em), prefabManager(pm) {}
		~ImGuiWrapper();
		inline void SetTargetEntity(Entity* entity) { targetEntity = entity; }
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
		inline Entity* TargetEntityGetter() { return targetEntity; }
		void DisplaySystemTimes();
		int selectedEntityIndex = 1;
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
		std::shared_ptr<Engine::EntityManager> entityManager;
		Engine::PrefabManager* prefabManager;

		Entity* targetEntity = nullptr;
		Prefab* targetPrefab = nullptr;

	};
}