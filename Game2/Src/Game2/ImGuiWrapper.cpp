/******************************************************************************/
/*!
\file		ImGuiWrapper.cpp
\author 	Liu Xujie
\co			Tristan Tham Rui Hong

\email		l.xujie@digipen.edu
			t.tham@digipen.edu

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
#include "Matrix3x3Lib.h"
#include "Input.h"
#include "SystemsManager.h"

namespace Engine {
#ifdef NDEBUG // Check if we are in release mode
	bool renderImGuiGUI = false;
#else
	bool renderImGuiGUI = true; // Debug mode
#endif

	EntityID firstEntity, secondEntity;
	Entity* targettedEntity;
	char cloneCountInput[10] = "";  // Buffer to store the input text
	char createCountInput[10] = "";  // Buffer to store the input text
	Input InputHandlerImGui;

	/*!**********************************************************************
	\brief
	Constructor for ImGuiWrapper class.
	*************************************************************************/
	ImGuiWrapper::ImGuiWrapper() : entityManager(), prefabManager()
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
		if (InputHandlerImGui.IsKeyTriggered(KEY_F1) == true) {
			renderImGuiGUI = !renderImGuiGUI;
		}
		if (renderImGuiGUI == true) {
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
			DisplaySystemTimes();
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
					if (entity.first == 0) {
						entityNames.push_back("Background");
					}
					else {
						entityNames.push_back("Entity " + std::to_string(entity.first));
					}
				}

				if (selectedEntityIndex >= entityNames.size()) {
					selectedEntityIndex = static_cast<int>(entityNames.size() - 1);
				}

				if (!entityNames.empty() && selectedEntityIndex >= 0)
				{
					if (ImGui::BeginCombo("Entities", entityNames[selectedEntityIndex].c_str())) {
						for (int i = 0; i < entityNames.size(); ++i) {
							const bool isSelected = (selectedEntityIndex == i);
							if (ImGui::Selectable(entityNames[i].c_str(), isSelected)) {
								selectedEntityIndex = i;
								targetEntity = entityManager->GetEntity(selectedEntityIndex);
							}
							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					// Clone Entity button
					if (ImGui::Button("Clone Entity"))
					{
						if (selectedEntityIndex)
						{
							entityManager->CloneEntity(selectedEntityIndex);							
						}
					}
				}
				else
				{
					ImGui::Text("No entities available"); // or handle as appropriate
				}
				
				ImGui::Text("Clone Multiple Entities");
				ImGui::InputText("Clone Count", cloneCountInput, 10);
				// Clone Multiple Entity button
				if (ImGui::Button("Clone Multiple Entities"))
				{
					// Parse the clone count from the input text
					int cloneCount = atoi(cloneCountInput);

					// Ensure clone count is valid and non-negative
					if (cloneCount > 0 && targetEntity)
					{
						// Clone the selected entity 'cloneCount' times
						for (int i = 0; i < cloneCount; ++i)
						{
							entityManager->CloneEntity(targetEntity->GetID());
						}
					}
				}

				if (ImGui::Button("Delete selected entity"))
				{
					if (!entityNames.empty())
					{
						entityManager->DestroyEntity(selectedEntityIndex);
						entityNames.erase(entityNames.begin() + selectedEntityIndex);

						// Update other relevant data structures

						// Resize the vector if necessary
						if (entityNames.empty())
						{
							selectedEntityIndex = -1; // No entities left, set index to an invalid value
							targetEntity = nullptr;   // No entity to select
						}
						else if (selectedEntityIndex >= entityNames.size())
						{
							selectedEntityIndex = static_cast<int>(entityNames.size() - 1); // Adjust the selected index
							entityManager->nextEntityID--;
							prefabManager->nextPrefabID--;
							targetEntity = entityManager->GetEntity(selectedEntityIndex); // Update current entity
							
						}
						else if (selectedEntityIndex < entityNames.size())
						{
							entityManager->nextEntityID--;
							prefabManager->nextPrefabID--;
							targetEntity = entityManager->GetEntity(selectedEntityIndex); // Update current entity
						}
						else
						{
							targetEntity = entityManager->GetEntity(selectedEntityIndex); // Update current entity
						}
					}
				}
			}

			ImGui::Begin("Entity Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

			if (entityManager && targetEntity) {
				std::unordered_map<ComponentType, Component*> components = targetEntity->GetComponents();
				// Get the properties of the selected entity (you will need to replace these with your actual entity property retrieval code)
				std::string entityName = "Entity " + std::to_string(targetEntity->GetID());
				TransformComponent* transform = nullptr;
				CollisionComponent* collision = nullptr;

				if (targetEntity->GetComponent(ComponentType::Transform) != nullptr) {
					transform = dynamic_cast<TransformComponent*>(targetEntity->GetComponent(ComponentType::Transform));
				}
				if (targetEntity->GetComponent(ComponentType::Collision) != nullptr) {
					collision = dynamic_cast<CollisionComponent*>(targetEntity->GetComponent(ComponentType::Collision));
				}

				// Display the properties
				ImGui::Text("Entity Name: %s", entityName.c_str());

				if (transform != nullptr) {
					float posX = transform->position.x;
					float posY = transform->position.y;
					float scaleX = transform->scaleX;
					float scaleY = transform->scaleY;
					float rot = transform->rot;
					float rotDeg = static_cast<float>(rot * (180.f / M_PI));
					rotDeg = fmod(rotDeg, 360.0f); // Ensure rotDeg stays within the 0-360 range

					// Input boxes for editing position, scale, and rotation with specified widths
					if (ImGui::InputFloat("Pos X", &posX, 1.0f, 2.0f, "%.2f")) {
						// Handle position X change here
						transform->position.x = posX;
					}

					if (ImGui::InputFloat("Pos Y", &posY, 1.0f, 2.0f, "%.2f")) {
						// Handle position Y change here
						transform->position.y = posY;
					}

					if (ImGui::InputFloat("Scale X", &scaleX, 0.1f, 1.0f, "%.2f")) {
						// Handle scale X change here
						transform->scaleX = scaleX;
					}

					if (ImGui::InputFloat("Scale Y", &scaleY, 0.1f, 1.0f, "%.2f")) {
						// Handle scale Y change here
						transform->scaleY = scaleY;
					}

					if (ImGui::InputFloat("Rotation (Deg)", &rotDeg, 1.0f, 10.0f, "%.1f")) {
						// Handle rotation change here
						rot = static_cast<float>(rotDeg * (M_PI / 180.f));
						transform->rot = rot;
					}
				}
				if (collision != nullptr) {
					if (collision->isColliding == true)
						ImGui::Text("Collision with another entity detected.");
					else if(collision->isColliding == false)
						ImGui::Text("No collision detected.");
				}
				// Add more properties as needed
				if (ImGui::CollapsingHeader("Component List")) {
					for (const auto& pair : components) {
						ComponentType type = pair.first;
						// Display component-specific properties here
						if (type == ComponentType::Transform) {
							ImGui::Text("Entity has Transform component.");
						}
						if (type == ComponentType::Texture) {
							ImGui::Text("Entity has Texture component.");
						}
						if (type == ComponentType::Physics) {
							ImGui::Text("Entity has Physics component.");
						}
						if (type == ComponentType::Collision) {
							ImGui::Text("Entity has Collision component.");
						}
					}
				}
			}
			else {
				ImGui::Text("No entity selected.");
			}

			//Prefab Tool
			ImGui::Begin("Prefab Tool", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
			if (prefabManager)
			{
				// Display a combo box to select the current prefab
				const auto prefabs = prefabManager->GetPrefabs();
				static int selectedPrefabIndex = 0;

				std::vector<std::string> prefabNames;
				for (const auto& pair : *prefabs) 
				{
					prefabNames.push_back(pair.second->GetName());
				}

				if (selectedPrefabIndex >= prefabNames.size()) {
					selectedPrefabIndex = static_cast<int>(prefabNames.size() - 1);
				}

				if (!prefabNames.empty() && selectedPrefabIndex >= 0)
				{
					if (ImGui::BeginCombo("Select Prefab", prefabNames[selectedPrefabIndex].c_str()))
					{
						for (int i = 0; i < prefabNames.size(); ++i)
						{
							const bool isSelected = (selectedPrefabIndex == i);
							if (ImGui::Selectable(prefabNames[i].c_str(), isSelected))
							{
								selectedPrefabIndex = i;
								targetPrefab = prefabManager->GetPrefab(selectedPrefabIndex);
							}
							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}
				}
				
				//Prefab Property editor
				if (selectedPrefabIndex >= 0 && selectedPrefabIndex < prefabNames.size()) 
				{
					Prefab* selectedPrefab = prefabManager->GetPrefab(prefabNames[selectedPrefabIndex]);

					ImGui::Text("Prefab Properties:");
					static bool showComponentExistsWarning = false;
					char newNameBuffer[128];//buffer to hold input name changes
					strncpy_s(newNameBuffer, selectedPrefab->GetName().c_str(), sizeof(newNameBuffer));

					if (ImGui::InputText("Prefab Name", newNameBuffer, sizeof(newNameBuffer))) 
					{					
						selectedPrefab->name = newNameBuffer; //Update name buffer 
					}

					// display components of the selected prefab
					ImGui::Text("Components");
					ImGui::SameLine();
					ImGui::Spacing();
					// Dropdown list for adding components					
					const char* componentTypes[] = {"", "Transform", "Collision", "Physics", "Texture"}; //add texture when working
					static int selectedComponentType = 0; // Index of the selected component 
					if (ImGui::Combo("Add New Component", &selectedComponentType, componentTypes, IM_ARRAYSIZE(componentTypes)))
					{
						if (selectedComponentType > 0)
						{
							// check if component already exists in buffer
							ComponentType typeToAdd = ComponentFactory::StringToComponentType(componentTypes[selectedComponentType]);
							if (!selectedPrefab->HasComponent(typeToAdd))
							{
								// Add the selected component type to the selected prefab
								selectedPrefab->AddNewComponent(typeToAdd);
								selectedComponentType = 0; // reset the index
							}
							else
							{
								// Set the flag to show the warning message
								showComponentExistsWarning = true;
								selectedComponentType = 0;
							}							
						}					
					}
					ImGui::Spacing();
					ImGui::Spacing();
					if (showComponentExistsWarning)
					{
						ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Prefab already has a %s component!", componentTypes[selectedComponentType]);
						ImGui::SameLine();
						
						if (ImGui::Button("Dismiss")) //confirmation button
						{
							showComponentExistsWarning = false;
						}
					}
													
					const auto components = selectedPrefab->GetComponents();
					for (const auto& pair : components)
					{
						ComponentType component = pair.first;
						if (ImGui::CollapsingHeader(ComponentFactory::ComponentTypeToString(component).c_str()))
						{
							ImGui::Indent();

							switch (component)
							{
							case ComponentType::Transform:
							{
								TransformComponent* transform = dynamic_cast<TransformComponent*>(pair.second);

								float posX = transform->position.x;
								float posY = transform->position.y;
								float scaleX = transform->scaleX;
								float scaleY = transform->scaleY;
								float rotDeg = static_cast<float>(transform->rot * (180.f / M_PI));
								rotDeg = fmod(rotDeg, 360.0f);

								// Input boxes for editing TransformComponent properties
								if (ImGui::InputFloat("Pos X", &posX, 1.0f, 2.0f, "%.2f"))
								{
									transform->position.x = posX;
								}

								if (ImGui::InputFloat("Pos Y", &posY, 1.0f, 2.0f, "%.2f"))
								{
									transform->position.y = posY;
								}

								if (ImGui::InputFloat("Scale X", &scaleX, 0.1f, 1.0f, "%.2f"))
								{
									transform->scaleX = scaleX;
								}

								if (ImGui::InputFloat("Scale Y", &scaleY, 0.1f, 1.0f, "%.2f"))
								{
									transform->scaleY = scaleY;
								}

								if (ImGui::InputFloat("Rotation (Deg)", &rotDeg, 1.0f, 10.0f, "%.1f"))
								{
									transform->rot = static_cast<float>(rotDeg * (M_PI / 180.f));
								}
								break;
							}

							case ComponentType::Collision:
							{
								CollisionComponent* collision = dynamic_cast<CollisionComponent*>(pair.second);

								float width = collision->c_Width;
								float height = collision->c_Height;
								bool isColliding = collision->isColliding;

								// Input boxes for editing CollisionComponent properties
								if (ImGui::InputFloat("Width", &width, 1.0f, 5.0f, "%.2f"))
								{
									collision->c_Width = width;
								}

								if (ImGui::InputFloat("Height", &height, 1.0f, 5.0f, "%.2f"))
								{
									collision->c_Height = height;
								}

								if (ImGui::Checkbox("Is Colliding", &isColliding))
								{
									collision->isColliding = isColliding;
								}
								break;
							}
							case ComponentType::Physics:
							{
								PhysicsComponent* physics = dynamic_cast<PhysicsComponent*>(pair.second);
								float velocity_x = physics->velocity.x;
								float velocity_y = physics->velocity.y;

								if (ImGui::InputFloat("X velocity", &velocity_x, 1.0f, 5.0f, "%.2f"))
								{
									physics->velocity.x = velocity_x;
								}

								if (ImGui::InputFloat("Y velocity", &velocity_y, 1.0f, 5.0f, "%.2f"))
								{
									physics->velocity.y = velocity_y;
								}

								break;
							}
							case ComponentType::Texture:
							{
								TextureComponent* texture = dynamic_cast<TextureComponent*>(pair.second);
								int textureIndex = static_cast<int>(texture->textureClass);
								if (ImGui::InputInt("Texture Type", &textureIndex, 1, 3))
								{
									texture->textureClass = static_cast<TextureClass>(textureIndex);
								}
							
							}

							default:
								break;
							}

							ImGui::SameLine();
							if (ImGui::Button("Remove")) //Delete component
							{
								selectedPrefab->components.erase(component);
							}
						
							ImGui::Unindent();
							ImGui::Spacing();
						}
						
					}
					ImGui::Spacing();
							
					if (ImGui::Button("Spawn"))
					{
						if (selectedPrefab)
						{
							//Spawn Entity from Prefab
							entityManager->CreateEntityFromPrefab(*selectedPrefab);
						}
					}

					ImGui::SameLine();

					if (ImGui::Button("Delete Prefab")) 
					{
						if (selectedPrefab)
						{
							prefabManager->DestroyPrefab(selectedPrefab->GetID());
						}
					}

					/*
					ImGui::SameLine();

					if (ImGui::Button("Save Changes"))
					{
						loader->SavePrefabs("Resource/Prefabs.txt");
					}
					*/
					

					ImGui::Separator();

					if (ImGui::CollapsingHeader("Prefab Creator"))
					{
						static bool ComponentExistsWarning = false;
						static char newPrefabName[64] = "New Prefab"; // input prefab name
						ImGui::InputText("New Prefab Name", newPrefabName, sizeof(newPrefabName));

						static Prefab bufferPrefab(0); // buffer prefab to hold changes

						// Dropdown list for adding components
						const char* creatorComponentTypes[] = {"", "Transform", "Collision", "Physics", "Texture"};
						static int selectedComponent = 0; // index for component types array

						if (ImGui::Combo("Add Component", &selectedComponent, creatorComponentTypes, IM_ARRAYSIZE(creatorComponentTypes)))
						{
							if (selectedComponent > 0)
							{
								// Check if a component of the selected type already exists in the prefab
								ComponentType typeToAdd = ComponentFactory::StringToComponentType(creatorComponentTypes[selectedComponent]);
								if (!bufferPrefab.HasComponent(typeToAdd))
								{
									// Add the selected component type to the selected prefab
									bufferPrefab.AddNewComponent(typeToAdd);
									selectedComponent = 0; // Reset the selected component index
								}
								else
								{
									// Set the flag to show the warning message
									ComponentExistsWarning = true;
									selectedComponent = 0;
								}								
							}						
						}

						if (ComponentExistsWarning)
						{
							ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Prefab already has a %s component!", creatorComponentTypes[selectedComponent]);
							ImGui::SameLine();
							// Optionally, you can add a button to dismiss the warning
							if (ImGui::Button("Dismiss"))
							{
								ComponentExistsWarning = false;
							}
						}

						// iterate through the components in the buffer prefab and display as collapsing headers
						const auto& bufferComponents = bufferPrefab.GetComponents();
						for (const auto& pair : bufferComponents)
						{
							ComponentType componentType = pair.first;
							ImGui::PushID(static_cast<int>(componentType));

							if (ImGui::CollapsingHeader(ComponentFactory::ComponentTypeToString(componentType).c_str()))
							{
								ImGui::Indent();

								switch (componentType)
								{
								case ComponentType::Transform:
								{
									TransformComponent* transform = dynamic_cast<TransformComponent*>(pair.second);

									float posX = transform->position.x;
									float posY = transform->position.y;
									float scaleX = transform->scaleX;
									float scaleY = transform->scaleY;
									float rotDeg = static_cast<float>(transform->rot * (180.f / M_PI));
									rotDeg = fmod(rotDeg, 360.0f);

									// Input boxes for editing TransformComponent properties
									if (ImGui::InputFloat("Pos X", &posX, 1.0f, 2.0f, "%.2f"))
									{
										transform->position.x = posX;
									}

									if (ImGui::InputFloat("Pos Y", &posY, 1.0f, 2.0f, "%.2f"))
									{
										transform->position.y = posY;
									}

									if (ImGui::InputFloat("Scale X", &scaleX, 0.1f, 1.0f, "%.2f"))
									{
										transform->scaleX = scaleX;
									}

									if (ImGui::InputFloat("Scale Y", &scaleY, 0.1f, 1.0f, "%.2f"))
									{
										transform->scaleY = scaleY;
									}

									if (ImGui::InputFloat("Rotation (Deg)", &rotDeg, 1.0f, 10.0f, "%.1f"))
									{
										transform->rot = static_cast<float>(rotDeg * (M_PI / 180.f));
									}
									break;
								}

								case ComponentType::Collision:
								{
									CollisionComponent* collision = dynamic_cast<CollisionComponent*>(pair.second);

									float width = collision->c_Width;
									float height = collision->c_Height;
									bool isColliding = collision->isColliding;

									// Input boxes for editing CollisionComponent properties
									if (ImGui::InputFloat("Hitbox Width", &width, 1.0f, 5.0f, "%.2f"))
									{
										collision->c_Width = width;
									}

									if (ImGui::InputFloat("Hitbox Height", &height, 1.0f, 5.0f, "%.2f"))
									{
										collision->c_Height = height;
									}

									if (ImGui::Checkbox("Is Colliding", &isColliding))
									{
										collision->isColliding = isColliding;
									}
									break;
								}

								case ComponentType::Physics:
								{
									PhysicsComponent* physics = dynamic_cast<PhysicsComponent*>(pair.second);
									float velocity_x = physics->velocity.x;
									float velocity_y = physics->velocity.y;

									if (ImGui::InputFloat("X velocity", &velocity_x, 1.0f, 5.0f, "%.2f"))
									{
										physics->velocity.x = velocity_x;
									}

									if (ImGui::InputFloat("Y velocity", &velocity_y, 1.0f, 5.0f, "%.2f"))
									{
										physics->velocity.y = velocity_y;
									}

									break;
								}

								case ComponentType::Texture:
								{
									TextureComponent* texture = dynamic_cast<TextureComponent*>(pair.second);
									int textureIndex = static_cast<int>(texture->textureClass);
									if (ImGui::InputInt("Texture Type", &textureIndex, 1, 3))
									{
										texture->textureClass = static_cast<TextureClass>(textureIndex);
									}
									else
									{
										texture->textureClass = TextureClass::Warrior;
									}
								}
								

								default:
									break;
								}

								ImGui::SameLine();
								if (ImGui::Button("Remove"))
								{
									bufferPrefab.components.erase(componentType);
								}

								ImGui::Unindent();
							}

							ImGui::PopID();
						}

						if (ImGui::Button("Create New Prefab"))
						{
							PrefabID newPrefabID = prefabManager->CreatePrefab();
							Prefab* newPrefab = prefabManager->GetPrefab(newPrefabID);
							newPrefab->name = newPrefabName;

							// Add each component to the new prefab
							for (const auto& pair : bufferComponents)
							{
								Component* clonedComponent = pair.second->Clone();
								newPrefab->components.emplace(pair.first, std::unique_ptr<Component>(clonedComponent));
							}
						}
					}												
				}
			}
			ImGui::End(); // End Prefab Tool
			
			ImGui::End(); // End the selected entity properties window

			ImGui::End();

			// End the ImGui window
			ImGui::End();

			// Render ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
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

	void ImGuiWrapper::DisplaySystemTimes() {
		SystemsManager& systemsManager = SystemsManager::GetInstance();
		auto systemTimes = systemsManager.DisplaySystemTimes(loopTime);

		if (ImGui::CollapsingHeader("System Times")) {
			for (const auto& [systemName, percentage] : systemTimes) {
				ImGui::Text("%s: %.2f%% of the total game loop time", systemName.c_str(), percentage);
			}
		}
	}

}