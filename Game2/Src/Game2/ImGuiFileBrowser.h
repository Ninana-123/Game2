/******************************************************************************/
/*!
\file		ImGuiFileBrowser.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	01/11/2023
\brief		Provides a graphical user interface in a game engine for
            browsing and interacting with the filesystem. It is responsible for
            displaying files and directories, handling user input, and performing
            actions such as opening and deleting files
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "imgui.h"
#include "AssetManager.h"
#include "logger.h"
#include "texture.h"
#include "GraphicsSystem.h"
#include "PrefabManager.h"
#include "SystemsManager.h"
#include "Loader.h"

namespace Engine {
    class FileBrowser {
    public:
        void Show() {
            ImGui::Begin("File Browser", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

            if (ImGui::BeginListBox("##files")) {
                for (size_t i = 0; i < files.size(); ++i) {
                    const bool isSelected = (i == selectedIndex);
                    if (ImGui::Selectable(files[i].c_str(), isSelected)) {
                        selectedIndex = static_cast<int>(i);
                        selectedFile = files[i];

                        if (selectedFile.substr(0, 6) == "[DIR] ") {
                            std::string directoryPath = selectedFile.substr(6);
                            Open(directoryPath);
                            continue;
                        }
                        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                            // Set payload to contain the scene file path
                            ImGui::SetDragDropPayload("SCENE_PATH", files[i].c_str(), (files[i].size() + 1) * sizeof(char));

                            // Display preview (could be text, image, etc.)
                            ImGui::Text("Load %s", files[i].c_str());
                            ImGui::EndDragDropSource();
                        }
                    }

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }

            if (selectedFile.substr(0, 6) == "[DIR] ") {
                selectedIndex = -1;
                selectedFile.clear();
            }

            if (ImGui::Button("Open")) {
                if (!selectedFile.empty() && currentDirectory == "Resource/Scenes") {
                    deleteAllEntity = true;
                    shouldLoadScene = true; // Set flag indicating a scene should be loaded
                    sceneToLoad = selectedFile; // Store the name of the scene to be loaded
                }
                else if (!selectedFile.empty() && currentDirectory == "Resource/Texture") {
                    Engine::Logger::GetInstance().Log(Engine::LogLevel::Debug, selectedFile);
                    am->UpdateTexture(t_mainIndex, selectedFile, t_subIndex);//Update buffer                 
                }
                CloseBrowser(); // Close the browser and clear the files vector
            }

            if (ImGui::Button("Delete")) {
                if (!selectedFile.empty()) {
                    DeleteSelectedFile();
                }
            }

            if (ImGui::Button("Cancel")) {
                CloseBrowser();
            }
                ImGui::End();      
        }

        void Open(const std::string& directory) {         
            currentDirectory = directory;
            files = GetFilesInDirectory(directory);
            isOpen = true;
        }
        void Open(const std::string& directory, int mainIndex, int subIndex) {
            t_mainIndex = mainIndex;
            t_subIndex = subIndex;
            currentDirectory = directory;
            files = GetFilesInDirectory(directory);
            isOpen = true;
        }

        std::vector<std::string> GetFilesInDirectory(const std::string& directory) {
            files.clear(); // Ensure the files vector is cleared before populating
            for (const auto& entry : std::filesystem::directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    files.push_back(entry.path().string());
                }
                else if (entry.is_directory()) {
                    files.push_back("[DIR] " + entry.path().string()); // or any other formatting you prefer
                }
            }
            return files;
        }

        bool isOpen = false;
        inline void setAssetManagerPtr(std::shared_ptr<Engine::AssetManager> assetsManager) {
            am = assetsManager;
        }
        inline void setEntityManagerPtr(std::shared_ptr<Engine::EntityManager> entityManager) {
            em = entityManager;
        }
        inline void setPrefabManagerPtr(PrefabManager* prefabManager) {
            pm = prefabManager;
        }
        inline void setSelectedEntityIndexReference(int& index) {
            selectedEntityIndex = index;
        }
        inline void setTargetEntityPtr(Entity* target) {
            targetEntity = target;
        }
        inline void setLoader(std::shared_ptr<Engine::Loader> Deserializer) {
            loader = Deserializer;
        }

        void DeleteSelectedFile() {
            try {
                std::filesystem::remove(selectedFile);  // Delete the file
                files = GetFilesInDirectory(currentDirectory);  // Refresh the file list
                selectedFile.clear();  // Clear the selected file
                selectedIndex = -1;    // Reset the selected index
            }
            catch (const std::exception& e) {
                // You can log the error or handle it in a way that suits your application
                Engine::Logger::GetInstance().Log(Engine::LogLevel::Error, e.what());
            }
        }
    private:
        std::vector<std::string> files;
        std::string selectedFile;
        std::string currentDirectory;
        int selectedIndex = -1; // Add an index to track which file is selected
        std::shared_ptr<Engine::AssetManager> am;
        std::shared_ptr<Engine::EntityManager> em;
        std::shared_ptr<Engine::Loader> loader;
        PrefabManager* pm = nullptr;
        Entity* targetEntity = nullptr;
        int selectedEntityIndex = -1;
        int t_mainIndex{};
        int t_subIndex{};

        void CloseBrowser() {
            isOpen = false;
            files.clear(); // Clear the files vector
            selectedFile.clear(); // Clear the selected file
            selectedIndex = -1; // Reset the selected index
        }
    };
}