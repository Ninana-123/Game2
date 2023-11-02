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
                    const bool isSelected = (i == selectedIndex); // Check if this file is the selected one
                    if (ImGui::Selectable(files[i].c_str(), isSelected)) {
                        selectedIndex = static_cast<int>(i);
                        selectedFile = files[i];
                    }

                    // Set the default selected item
                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndListBox();
            }

            if (ImGui::Button("Open")) {
                if (!selectedFile.empty() && currentDirectory == "Resource/Scenes") {
                    deleteAllEntity = true;
                    shouldLoadScene = true; // Set flag indicating a scene should be loaded
                    sceneToLoad = selectedFile; // Store the name of the scene to be loaded
                }
                else if (!selectedFile.empty() && currentDirectory == "Resource/Texture") {
                    Engine::Logger::GetInstance().Log(Engine::LogLevel::Debug, selectedFile);
                    am->loadTexture(2, selectedFile);
                    Engine::SystemsManager& systemsManager = Engine::SystemsManager::GetInstance();
                    Engine::GraphicsSystem& graphicsSystem = systemsManager.GetSystem<Engine::GraphicsSystem>();
                    graphicsSystem.InitializeTextures();
                }
                CloseBrowser(); // Close the browser and clear the files vector
            }

            if (ImGui::Button("Delete")) {
                if (!selectedFile.empty()) {
                    DeleteSelectedFile();
                }
            }

            if (ImGui::Button("Cancel")) {
                CloseBrowser(); // Close the browser and clear the files vector
            }

            ImGui::End();
        }

        void Open(const std::string& directory) {
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
        int selectedEntityIndex;

        void CloseBrowser() {
            isOpen = false;
            files.clear(); // Clear the files vector
            selectedFile.clear(); // Clear the selected file
            selectedIndex = -1; // Reset the selected index
        }
    };
}