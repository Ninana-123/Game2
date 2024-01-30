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
#ifndef ENGINE_IMGUIWRAPPER_H
#define ENGINE_IMGUIWRAPPER_H

#include "Event.h"
#include "InputEvent.h"
#include "AppEvent.h"
#include "EntityManager.h"
#include "PrefabManager.h"
#include "AssetManager.h"
#include "Loader.h"

extern bool deleteAllEntity;
extern bool shouldLoadScene;
extern std::string sceneToLoad;
extern bool useEditorCamera;
extern bool renderImGuiGUI;
extern float e_editorWidth;
extern float e_editorHeight;

namespace Engine {

	class GAME2_API ImGuiWrapper {
	public:
		/*!
		 * \brief Constructor for the ImGuiWrapper class.
		 *
		 * Initializes ImGui and sets up key mappings.
		 */
		ImGuiWrapper();

		/*!
		 * \brief Constructor for the ImGuiWrapper class with additional parameters.
		 *
		 * Initializes ImGui and sets up key mappings with additional parameters.
		 *
		 * \param em A shared pointer to the EntityManager.
		 * \param pm A pointer to the PrefabManager.
		 * \param am A shared pointer to the AssetManager.
		 * \param loader A shared pointer to the Loader.
		 */
		ImGuiWrapper(std::shared_ptr<Engine::EntityManager> em, Engine::PrefabManager* pm, std::shared_ptr<Engine::AssetManager> am
		, std::shared_ptr<Engine::Loader> loader) : entityManager(em), prefabManager(pm), assetManager(am), deserializer(loader) {}

		/*!
		 * \brief Destructor for the ImGuiWrapper class.
		 */
		~ImGuiWrapper();

		/*!
		 * \brief Sets the target entity for ImGui interactions.
		 *
		 * This function sets the target entity for ImGui interactions.
		 *
		 * \param entity A pointer to the target entity.
		 */
		inline void SetTargetEntity(Entity* entity) { targetEntity = entity; }

		/*!
		 * \brief Begins the ImGui frame.
		 */
		void Begin();

		/*!
		 * \brief Ends the ImGui frame.
		 */
		void End();

		/*!
		 * \brief Initializes ImGui.
		 */
		void Initialize();

		/*!
		 * \brief Called when attaching ImGui.
		 *
		 * Initializes ImGui context, style, and key mappings.
		 */
		void OnAttach();

		/*!
		 * \brief Called when detaching ImGui.
		 *
		 * Currently empty as there are no specific detach actions needed.
		 */
		void OnDetach();

		/*!
		 * \brief Updates ImGui for the current frame.
		 *
		 * This function is responsible for updating ImGui and rendering ImGui
		 * content for the current frame.
		 */
		void OnUpdate();

		/*!
		 * \brief Handles events for ImGui interaction.
		 *
		 * This function processes events related to ImGui interaction.
		 *
		 * \param event The event to handle.
		 */
		void OnEvent(Event& event);

		/*!
		 * \brief Gets the target entity for ImGui interactions.
		 *
		 * This function returns the target entity for ImGui interactions.
		 *
		 * \return A pointer to the target entity.
		 */
		inline Entity* TargetEntityGetter() { return targetEntity; }

		/*!
		 * \brief Displays system times in ImGui.
		 */
		void DisplaySystemTimes();

		/*!
		 * \brief Renders the asset browser in ImGui.
		 */
		void RenderAssetBrowser();

		/*!
		 * \brief Renders the level editor in ImGui.
		 */
		void RenderLevelEditor();

		void RenderAudioBrowser();

		int selectedEntityIndex = 1;

		inline bool IsImGuiHovered() const { return isImGuiHovered; }

	private:

		/*!
		 * \brief Handles mouse button pressed event for ImGui interaction.
		 *
		 * Sets the appropriate flag in ImGuiIO for a mouse button press event.
		 *
		 * \param e The mouse button pressed event.
		 * \return False indicating the event has been handled.
		 */
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);

		/*!
		 * \brief Handles mouse button released event for ImGui interaction.
		 *
		 * Sets the appropriate flag in ImGuiIO for a mouse button released event.
		 *
		 * \param e The mouse button released event.
		 * \return False indicating the event has been handled.
		 */
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

		/*!
		 * \brief Handles mouse moved event for ImGui interaction.
		 *
		 * Sets the appropriate flag in ImGuiIO for a mouse moved event.
		 *
		 * \param e The mouse moved event.
		 * \return False indicating the event has been handled.
		 */
		bool OnMouseMovedEvent(MouseMovedEvent& e);

		/*!
		 * \brief Handles mouse scrolled event for ImGui interaction.
		 *
		 * Sets the appropriate flag in ImGuiIO for a mouse scrolled event.
		 *
		 * \param e The mouse scrolled event.
		 * \return False indicating the event has been handled.
		 */
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		/*!
		 * \brief Handles key pressed event for ImGui interaction.
		 *
		 * Sets the appropriate flag in ImGuiIO for a key press event.
		 *
		 * \param e The key pressed event.
		 * \return False indicating the event has been handled.
		 */
		bool OnKeyPressedEvent(KeyPressedEvent& e);

		/*!
		 * \brief Handles key released event for ImGui interaction.
		 *
		 * Sets the appropriate flag in ImGuiIO for a key released event.
		 *
		 * \param e The key released event.
		 * \return False indicating the event has been handled.
		 */
		bool OnKeyReleased(KeyReleasedEvent& e);

		/*!
		 * \brief Handles key typed event for ImGui interaction.
		 *
		 * Sets the appropriate flag in ImGuiIO for a key typed event.
		 *
		 * \param e The key typed event.
		 * \return False indicating the event has been handled.
		 */
		bool OnKeyTypedEvent(KeyTypedEvent & e);

		/*!
		 * \brief Handles window resize event for ImGui interaction.
		 *
		 * Updates ImGuiIO with the new display size and framebuffer scale, as well
		 * as sets the OpenGL viewport.
		 *
		 * \param e The window resize event.
		 * \return False indicating the event has been handled.
		 */
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		bool renderDockspace = false;
		bool isImGuiHovered = false;
		float m_Time = 0.0f;
		float editorCameraSpeed = 1.5f;
		std::shared_ptr<Engine::EntityManager> entityManager;
		Engine::PrefabManager* prefabManager;
		std::shared_ptr<Engine::AssetManager> assetManager;
		std::shared_ptr<Engine::Loader> deserializer;
		Entity* targetEntity = nullptr;
		Prefab* targetPrefab = nullptr;
		void UpdateImGuiInteractionState();

	};
}
#endif ENGINE_IMGUIWRAPPER_H