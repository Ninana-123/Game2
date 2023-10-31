#include "pch.h"
#include "imgui.h"
#include "AssetManager.h"
#include "logger.h"
#include "texture.h"
#include "GraphicsSystem.h"
#include "SystemsManager.h"

namespace Engine {
    class SimpleFileBrowser {
    public:
        void Show() {
            ImGui::Begin("File Browser");

            if (ImGui::BeginListBox("##files")) {
                for (size_t i = 0; i < files.size(); ++i) {
                    const bool isSelected = (i == selectedIndex); // Check if this file is the selected one
                    if (ImGui::Selectable(files[i].c_str(), isSelected)) {
                        selectedIndex = i;
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
                if (!selectedFile.empty()) {
                    Engine::Logger::GetInstance().Log(Engine::LogLevel::Debug, selectedFile);
                    am->loadTexture(2, selectedFile);
                    am->reloadTexture(2);
                    Engine::SystemsManager& systemsManager = Engine::SystemsManager::GetInstance();
                    Engine::GraphicsSystem& graphicsSystem = systemsManager.GetSystem<Engine::GraphicsSystem>();
                    graphicsSystem.InitializeTextures();
                    // Handle the file opening here
                    // e.g., loadTexture(selectedFile);
                }
                CloseBrowser(); // Close the browser and clear the files vector
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                CloseBrowser(); // Close the browser and clear the files vector
            }

            ImGui::End();
        }

        void Open(const std::string& directory) {
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
    private:
        std::vector<std::string> files;
        std::string selectedFile;
        int selectedIndex = -1; // Add an index to track which file is selected
        std::shared_ptr<Engine::AssetManager> am;

        void CloseBrowser() {
            isOpen = false;
            files.clear(); // Clear the files vector
            selectedFile.clear(); // Clear the selected file
            selectedIndex = -1; // Reset the selected index
        }
    };
}