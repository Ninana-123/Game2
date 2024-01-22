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
#ifndef ENGINE_IMGUIFILE_H
#define ENGINE_IMGUIFILE_H

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
        /*!
         * \brief Displays the file browser window.
         *
         * This function creates and displays the file browser window using ImGui. It allows users
         * to browse files and directories, select files, and perform actions such as opening and deleting files.
         */
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
                    Engine::SystemsManager& systemsManager = Engine::SystemsManager::GetInstance();
                    Engine::GraphicsSystem* graphicsSystem = systemsManager.GetSystem<Engine::GraphicsSystem>();
                    graphicsSystem->UpdateTexture(t_mainIndex, t_subIndex, selectedFile);
                    //am->UpdateTexture(t_mainIndex, selectedFile, t_subIndex);//Update buffer                 
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

        /*!
         * \brief Opens the file browser window in the specified directory.
         *
         * This function opens the file browser window and populates it with files and directories
         * from the specified directory.
         *
         * \param directory The directory to open in the file browser.
         */
        void Open(const std::string& directory) {         
            currentDirectory = directory;
            files = GetFilesInDirectory(directory);
            isOpen = true;
        }

        /*!
        * \brief Opens the file browser window in the specified directory and associates it with a texture index.
        *
        * This function opens the file browser window and populates it with files and directories
        * from the specified directory. It also associates the file browser with a texture index for updating textures.
        *
        * \param directory The directory to open in the file browser.
        * \param mainIndex The main texture index.
        * \param subIndex The subtexture index.
        */
        void Open(const std::string& directory, int mainIndex, int subIndex) {
            t_mainIndex = mainIndex;
            t_subIndex = subIndex;
            currentDirectory = directory;
            files = GetFilesInDirectory(directory);
            isOpen = true;
        }

        /*!
         * \brief Retrieves a list of files in the specified directory.
         *
         * This function retrieves a list of files in the specified directory, including both regular files
         * and subdirectories. It populates the files vector with the paths of the files.
         *
         * \param directory The directory to retrieve files from.
         * \return A vector of strings representing the files in the directory.
         */
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

        /*!
         * \brief Sets a pointer to the AssetManager for texture updates.
         *
         * This function sets a pointer to the AssetManager, which is used for updating textures.
         *
         * \param assetsManager A shared pointer to the AssetManager.
         */
        inline void setAssetManagerPtr(std::shared_ptr<Engine::AssetManager> assetsManager) {
            am = assetsManager;
        }

        /*!
         * \brief Sets a pointer to the EntityManager.
         *
         * This function sets a pointer to the EntityManager, which is used for managing entities.
         *
         * \param entityManager A shared pointer to the EntityManager.
         */
        inline void setEntityManagerPtr(std::shared_ptr<Engine::EntityManager> entityManager) {
            em = entityManager;
        }

        /*!
         * \brief Sets a pointer to the PrefabManager.
         *
         * This function sets a pointer to the PrefabManager, which is used for managing prefabs.
         *
         * \param prefabManager A pointer to the PrefabManager.
         */
        inline void setPrefabManagerPtr(PrefabManager* prefabManager) {
            pm = prefabManager;
        }

        /*!
         * \brief Sets a reference to the selected entity index.
         *
         * This function sets a reference to the selected entity index, which is used for updating selected entities.
         *
         * \param index A reference to the selected entity index.
         */
        inline void setSelectedEntityIndexReference(int& index) {
            selectedEntityIndex = index;
        }

        /*!
         * \brief Sets a pointer to the target entity for texture updates.
         *
         * This function sets a pointer to the target entity, which is used for updating textures.
         *
         * \param target A pointer to the target entity.
         */
        inline void setTargetEntityPtr(Entity* target) {
            targetEntity = target;
        }

        /*!
         * \brief Sets a pointer to the Loader for deserialization.
         *
         * This function sets a pointer to the Loader, which is used for deserializing scene files.
         *
         * \param Deserializer A shared pointer to the Loader.
         */
        inline void setLoader(std::shared_ptr<Engine::Loader> Deserializer) {
            loader = Deserializer;
        }

        /*!
         * \brief Deletes the currently selected file.
         *
         * This function deletes the currently selected file, updating the file list and resetting the selection.
         */
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

        /*!
         * \brief Closes the file browser window.
         *
         * This function closes the file browser window, clearing the file list and resetting the selection.
         */
        void CloseBrowser() {
            isOpen = false;
            files.clear(); // Clear the files vector
            selectedFile.clear(); // Clear the selected file
            selectedIndex = -1; // Reset the selected index
        }
    };
}
#endif ENGINE_IMGUIIFLE_H