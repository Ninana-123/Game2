/******************************************************************************/
/*!
\file		ImGuiWrapper.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		This file contains the implementation of the ImGuiWrapper class,
			which encapsulates ImGui functionality for UI rendering and 
			interaction.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "ImGuiWrapper.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "GL/glew.h"
#include "KeyCodes.h"
#include <GLFW/glfw3.h>
#include "Application.h"
#include <windows.h>


namespace Engine {

	EntityID firstEntity, secondEntity;
	Entity* targettedEntity;
	char cloneCountInput[10] = "";  // Buffer to store the input text
	char createCountInput[10] = "";  // Buffer to store the input text

	/*!**********************************************************************
	\brief
	Constructor for ImGuiWrapper class.
	*************************************************************************/
	ImGuiWrapper::ImGuiWrapper() : entityManager()
	{

	}
	/*!**********************************************************************
	\brief
	Destructor for ImGuiWrapper class.
	*************************************************************************/
	ImGuiWrapper::~ImGuiWrapper()
	{
	}
	/*!**********************************************************************
	\brief
	Sets the text to the system clipboard using GLFW.
	\param[in] user_data
	A pointer to user-defined data.
	\param[in] text
	The text to set in the clipboard.
	*************************************************************************/
	static void SetClipboardText(void* user_data, const char* text)
	{
		glfwSetClipboardString((GLFWwindow*)user_data, text);
	}
	/*!**********************************************************************
	\brief
	Gets the text from the system clipboard using GLFW
	\param[in] user_data
	A pointer to user-defined data.
	*************************************************************************/
	static const char* GetClipboardText(void* user_data)
	{
		return glfwGetClipboardString((GLFWwindow*)user_data);
	}
	/*!**********************************************************************
	\brief
	Gets the GPU vendor using OpenGL and GLEW.
	\return
	A pointer to a string representing the GPU vendor.
	*************************************************************************/
	const char* GetGPUVendor() {
		// Ensure GLEW is initialized
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
			return "N/A";
		}

		// Get the version string
		const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		return vendor ? vendor : "N/A";
	}
	/*!**********************************************************************
	\brief
	Gets the renderer using OpenGL and GLEW.
	\return
	A pointer to a string representing the rendereer.
	*************************************************************************/
	const char* GetGraphicsCardInfo() {
		// Ensure GLEW is initialized
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
			return "N/A";
		}

		// Get the renderer string
		const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		return renderer ? renderer : "N/A";
	}

	/*!**********************************************************************
	\brief
	Gets the OpenGL version using OpenGL and GLEW.
	\return
	A pointer to a string representing the OpenGL version.
	*************************************************************************/
	const char* GetOpenGLVersion() {
		// Ensure GLEW is initialized
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
			return "N/A";
		}

		// Get the OpenGL version string
		const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		return version ? version : "N/A";
	}
	/*!**********************************************************************
	\brief
	Prints the GPU and graphics-related specifications using ImGui
	*************************************************************************/
	void print_specs() {
		//get string
		GLubyte const* str_ven = glGetString(GL_VENDOR);
		GLubyte const* str_ren = glGetString(GL_RENDERER);
		GLubyte const* str_ver = glGetString(GL_VERSION);
		GLubyte const* str_sha = glGetString(GL_SHADING_LANGUAGE_VERSION);

		GLint major_ver, minor_ver, framebuffer, tex_size, vertex_count, indices_count, viewportwidth, viewportheight, max_vtx_attribs, vtx_buf_binds;
		//get integer
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &tex_size);
		glGetIntegerv(GL_MAJOR_VERSION, &major_ver);
		glGetIntegerv(GL_MINOR_VERSION, &minor_ver);
		glGetIntegerv(GL_DOUBLEBUFFER, &framebuffer);
		glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &vertex_count);
		glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &indices_count);
		glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &viewportwidth);
		glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &viewportheight);
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vtx_attribs);
		glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &vtx_buf_binds);

		ImGui::Text("GPU Vendor: %s", str_ven);
		ImGui::Text("GL Renderer: %s", str_ren);
		ImGui::Text("GL Version: %s", str_ver);
		ImGui::Text("GL Shader Version: %s", str_sha);
		ImGui::Text("GL Major Version: %d", major_ver);
		ImGui::Text("GL Minor Version: %d", minor_ver);
		if (framebuffer)
			ImGui::Text("Current OpenGL Context is double buffered");
		else
			ImGui::Text("Current OpenGL Context is not double buffered");
		ImGui::Text("Maximum Vertex Count: %d", vertex_count);
		ImGui::Text("Maximum Indices Count : % d", indices_count);
		ImGui::Text("GL Maximum texture size: %d", tex_size);
		ImGui::Text("Maximum Viewport Dimensions: %d x %d", viewportwidth, viewportheight);
		ImGui::Text("Maximum generic vertex attributes: %d", max_vtx_attribs);
		ImGui::Text("Maximum vertex buffer bindings: %d", vtx_buf_binds);
	}
	/*!**********************************************************************
	\brief
	Get the total available physical memory in megabytes
	\return
	Total available physical memory in megabytes
	*************************************************************************/
	float GetTotalMemoryInMB() {
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		return static_cast<float>(status.ullTotalPhys) / (1024 * 1024);
	}

	/*!**********************************************************************
	\brief
	Get the available physical memory in megabytes
	\return
	Available physical memory in megabytes
	*************************************************************************/
	float GetAvailableMemoryInMB() {
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		return static_cast<float>(status.ullAvailPhys) / (1024 * 1024);
	}

	/*!**********************************************************************
	\brief
	Get the memory usage percentage
	\return
	Memory usage percentage.
	*************************************************************************/
	float GetMemoryUsagePercentage() {
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);

		// Calculate memory usage percentage
		float memoryUsagePercentage = static_cast<float>(status.dwMemoryLoad);
		return memoryUsagePercentage;
	}
	/*!**********************************************************************
	\brief
	Called when attaching ImGui
	Initializes ImGui context, style, and key mappings
	*************************************************************************/
	void ImGuiWrapper::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = KEY_HOME;
		io.KeyMap[ImGuiKey_End] = KEY_END;
		io.KeyMap[ImGuiKey_Insert] = KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = KEY_A;
		io.KeyMap[ImGuiKey_C] = KEY_C;
		io.KeyMap[ImGuiKey_V] = KEY_V;
		io.KeyMap[ImGuiKey_X] = KEY_X;
		io.KeyMap[ImGuiKey_Y] = KEY_Y;
		io.KeyMap[ImGuiKey_Z] = KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");

		io.SetClipboardTextFn = SetClipboardText;
		io.GetClipboardTextFn = GetClipboardText;
		io.ClipboardUserData = glfwGetCurrentContext();
		if (entityManager) {
			firstEntity = 1;
			targettedEntity = entityManager->GetEntity(1);

		}
	}

	/*!**********************************************************************
	\brief
	Called when detaching ImGui.
    Currently empty as there are no specific detach actions needed.
	*************************************************************************/
	void ImGuiWrapper::OnDetach()
	{
	}
	/*!**********************************************************************
	\brief
	Update ImGui for the current frame.
	This function is responsible for updating ImGui and rendering ImGui 
	content for the current frame.
	*************************************************************************/
	void ImGuiWrapper::OnUpdate()
	{
		int displayWidth, displayHeight;
		glfwGetFramebufferSize(glfwGetCurrentContext(), &displayWidth, &displayHeight);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(displayWidth);
		io.DisplaySize.y = static_cast<float>(displayHeight);

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// Start a new ImGui window for debugging info
		ImGui::Begin("Debug Information", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		// Display FPS
		ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);

		// Display frame time
		ImGui::Text("Frame Time: %.4f ms", 1000.0f / ImGui::GetIO().Framerate);

		// Memory Usage dropdown
		if (ImGui::CollapsingHeader("Memory Usage")) {
			ImGui::Text("Total Memory: %.2f MB", GetTotalMemoryInMB());
			ImGui::Text("Available Memory: %.2f MB", GetAvailableMemoryInMB());
			ImGui::Text("Memory Usage: %.2f%%", GetMemoryUsagePercentage());
		}

		// Graphics Information dropdown
		if (ImGui::CollapsingHeader("Graphics Information")) {
			print_specs();  // Assuming print_specs() provides the necessary graphics info
		}

		// Input dropdown
		if (ImGui::CollapsingHeader("Input")) {
			ImGui::Text("Mouse Position: (%.1f, %.1f)", io.MousePos.x, io.MousePos.y);
			ImGui::Text("Keys Pressed:");

			bool anyKeyPressed = false; // Track if any key is pressed

			for (int key = KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
				auto keyIter = Key::keyMap.find(key);
				if (keyIter != Key::keyMap.end() && glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS) {
					ImGui::Bullet();
					ImGui::SameLine();
					ImGui::Text("%s", keyIter->second.c_str());
					anyKeyPressed = true;  // Set the flag to true if any key is pressed
				}
			}

			if (!anyKeyPressed) {
				ImGui::Text("No Keys Pressed");
			}
		}
		ImGui::Begin("Game Objects", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		if (entityManager)
		{
			if (ImGui::Button("Create Entity"))
			{
				entityManager->CreateEntity();
				std::cout << "Created Entity" << std::endl;
			}
			ImGui::Text("Create Multiple Entities");
			ImGui::InputText("Create Count", createCountInput, 10);
			// Clone Entity button
			if (ImGui::Button("Create Multiple Entities"))
			{
				// Parse the clone count from the input text
				int createCount = atoi(createCountInput);

				// Ensure clone count is valid and non-negative
				if (createCount > 0)
				{
					// Clone the object 'cloneCount' times
					for (int i = 0; i < createCount; ++i)
					{
						entityManager->CreateEntity();
						std::cout << "Created Entity" << std::endl;
					}
				}
			}

			const auto entities = entityManager->GetEntities();
			ImGui::Text("Number of Entities: %d", entities->size());
			ImGui::Separator();
			ImGui::Text("Currently selected entity ID:");

			std::vector<std::string> entityNames;
			for (const auto& entity : *entities) {
				entityNames.push_back("Entity " + std::to_string(entity.first));
			}


			if (ImGui::BeginCombo("Entities", entityNames[selectedEntityIndex].c_str())) {
				for (int i = 1; i < entityNames.size(); ++i) {
					const bool isSelected = (selectedEntityIndex == i);
					if (ImGui::Selectable(entityNames[i].c_str(), isSelected)) {
						selectedEntityIndex = i;
						targetEntity = entityManager->GetEntity(selectedEntityIndex);
						std::cout << targetEntity->GetID();
					}
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			// Clone Entity button
			if (ImGui::Button("Clone Entity"))
			{
				secondEntity = entityManager->CloneEntity(firstEntity);
				targettedEntity = entityManager->GetEntity(secondEntity);
			}
			ImGui::Text("Clone Multiple Entities");
			ImGui::InputText("Clone Count", cloneCountInput, 10);
			// Clone Entity button
			if (ImGui::Button("Clone Multiple Entities"))
			{
				// Parse the clone count from the input text
				int cloneCount = atoi(cloneCountInput);

				// Ensure clone count is valid and non-negative
				if (cloneCount > 0)
				{
					// Clone the object 'cloneCount' times
					for (int i = 0; i < cloneCount; ++i)
					{
						// Clone firstEntity and store its ID
						firstEntity = targetEntity->GetID();
						secondEntity = entityManager->CloneEntity(firstEntity);
						targettedEntity = entityManager->GetEntity(secondEntity);
					}
				}
			}
			/*
			if (ImGui::Button("Delete currently selected entity")) {
				entityManager->DestroyEntity(selectedEntityIndex);
			}
			*/
			
		}

		ImGui::End();

		// End the ImGui window
		ImGui::End();

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	/*!**********************************************************************
	\brief
	Handle events for ImGui interaction.
	This function processes events related to ImGui interaction.
	\param[in] event 
	The event to handle.
	*************************************************************************/
	void ImGuiWrapper::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiWrapper::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiWrapper::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiWrapper::OnMouseMovedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiWrapper::OnMouseScrolledEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiWrapper::OnKeyPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiWrapper::OnKeyReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiWrapper::OnKeyTypedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiWrapper::OnWindowResizeEvent, this, std::placeholders::_1));

	}
	/*!**********************************************************************
	\brief
	Handle mouse button pressed event for ImGui interaction.
	This function sets the appropriate flag in ImGuiIO for a mouse button 
	press event.
	\param[in] e
	The mouse button pressed event.
	\return 
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}
	/*!**********************************************************************
	\brief
	Handle mouse button released event for ImGui interaction.
	This function sets the appropriate flag in ImGuiIO for a mouse button
	released event.
	\param[in] e
	The mouse button released event.
	\return
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}
	/*!**********************************************************************
	\brief
	Handle mouse moved event for ImGui interaction.
	This function sets the appropriate flag in ImGuiIO for a mouse moved event.
	\param[in] e
	The mouse moved event.
	\return
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}
	/*!**********************************************************************
	\brief
	Handle mouse scrolled event for ImGui interaction.
	This function sets the appropriate flag in ImGuiIO for a mouse scrolled
	event.
	\param[in] e
	The mouse scrolled event.
	\return
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}
	/*!**********************************************************************
	\brief
	Handle key pressed event for ImGui interaction.
	This function sets the appropriate flag in ImGuiIO for a key press event.
	\param[in] e
	The key pressed event.
	\return
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[KEY_LEFT_CONTROL] || io.KeysDown[KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[KEY_LEFT_SHIFT] || io.KeysDown[KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[KEY_LEFT_ALT] || io.KeysDown[KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[KEY_LEFT_SUPER] || io.KeysDown[KEY_RIGHT_SUPER];
		return false;
	}
	/*!**********************************************************************
	\brief
	Handle key released event for ImGui interaction.
	This function sets the appropriate flag in ImGuiIO for a key released
	event.
	\param[in] e
	The key released event.
	\return
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnKeyReleased(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}
	/*!**********************************************************************
	\brief
	Handle key typed event for ImGui interaction.
	This function sets the appropriate flag in ImGuiIO for a key typed
	event.
	\param[in] e
	The key typed event.
	\return
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x100000)
			io.AddInputCharacter((unsigned short)keycode);
		return false;
	}
	/*!**********************************************************************
	\brief
	Handle window resize event for ImGui interaction.
	This function updates ImGuiIO with the new display size and 
	framebuffer scale, as well as sets the OpenGL viewport.
	\param[in] e
	The window resize event.
	\return
	False indicating event has been handled.
	*************************************************************************/
	bool ImGuiWrapper::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

}