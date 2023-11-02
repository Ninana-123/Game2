/******************************************************************************/
/*!
\file		AssetManager.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		This file contains the declaration of the main Assets Manager

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "pch.h"
#include "Texture.h"
#include "EngineTypes.h"

namespace Engine {

    class AssetManager {
    private:
        // Change the key type to TextureKey and use the hash function
        std::unordered_map<TextureKey, std::shared_ptr<Texture>> textures;

    public:
        // Update the function signature
        std::shared_ptr<Texture> loadTexture(const int mainIndex, const int subIndex = 0);
        std::shared_ptr<Texture> loadTexture(const int mainIndex, const std::string& filePath, const int subIndex = 0); //Overload that takes in custom filepath

        // Update the function signature
        std::shared_ptr<Texture> getTexture(int mainIndex, int subIndex = 0) const;

        // Update the function signature
        void updateTextureFilePath(int mainIndex, int subIndex, const std::string& newFilePath);

        // Update the function signature
        std::shared_ptr<Texture> reloadAllTexture();

        // Use a vector of TextureKey instead of int for the function signature
        std::vector<TextureKey> GetAllTextureKeys() const;

        const std::string& GetTexturePath(const TextureKey& textureKey) const;

        // Update the function signature
        inline std::unordered_map<TextureKey, std::shared_ptr<Texture>>& GetAllTextures() {
            return textures;
        }

        const std::map<TextureKey, std::string>& GetTextureFilePaths() const {
            return textureFilePaths;
        }

    private:
        // Use the TextureKey structure instead of int for the map
        std::map<TextureKey, std::string> textureFilePaths = {
            { {TextureClass::Background, 0}, "Resource/Texture/Background.png" },
            { {TextureClass::Infanty, 0}, "Resource/Texture/Warrior.png" },
            { {TextureClass::Infanty, 1}, "Resource/Texture/WarriorWalking.png" },
            { {TextureClass::Tank, 0}, "Resource/Texture/Tank.png" },
            { {TextureClass::Tank, 1}, "Resource/Texture/TankWalking.png" },
            { {TextureClass::Archer, 0}, "Resource/Texture/Archer.png" },
            { {TextureClass::Archer, 1}, "Resource/Texture/ArcherWalking.png" },
            { {TextureClass::Tower, 0}, "Resource/Texture/Tower.png" },
            { {TextureClass::Castle, 0}, "Resource/Texture/Castle.png" },
            { {TextureClass::HUD, 0}, "Resource/Texture/HUD.png" },
            { {TextureClass::HUDInfantry, 0}, "Resource/Texture/HUDInfantry.png"},
            { {TextureClass::HUDArcher, 0}, "Resource/Texture/HUDArcher.png"},
            { {TextureClass::HUDTank, 0}, "Resource/Texture/HUDTank.png"},
            { {TextureClass::pauseButton, 0}, "Resource/Texture/pausebutton.png"},
            { {TextureClass::playButton, 0}, "Resource/Texture/playbutton.png"},
            { {TextureClass::settingsButton, 0}, "Resource/Texture/settingsbutton.png"},
        };
    };
}