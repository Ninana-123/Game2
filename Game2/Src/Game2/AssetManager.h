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
#include "texture.h"
#include "EngineTypes.h"

namespace Engine {
    class AssetManager {
    private:
        std::unordered_map<int , std::shared_ptr<Texture>> textures;

    public:
        std::shared_ptr<Texture> loadTexture(const int texid, const std::string& filePath);
        std::shared_ptr<Texture> getTexture(const int texid) const;
        // Function to update the file path of a texture
        void updateTextureFilePath(int texid, const std::string& newFilePath);
        // Function to reload a texture
        std::shared_ptr<Texture> reloadTexture(int texid);
        inline std::unordered_map<int, std::shared_ptr<Texture>>& GetAllTextures() {
            return textures;
        }

        const std::string& GetTexturePath(int texid) const;
        inline std::vector<int> getAllTextureIDs() const {
            std::vector<int> textureIDs;
            for (const auto& [texid, texture] : textures) {
                textureIDs.push_back(texid);
            }
            return textureIDs;
        }


        std::map<int, std::string> textureFilePaths = {
        {TextureClass::Background, "Resource/Texture/Background.png"},
        {TextureClass::Infanty, "Resource/Texture/InfantryWalking.png"},
        {TextureClass::Tank, "Resource/Texture/TankWalking.png"},
        {TextureClass::Archer, "Resource/Texture/ArcherWalking.png"},
        {TextureClass::Tower, "Resource/Texture/Tower.png"},
        {TextureClass::Castle, "Resource/Texture/Castle.png"},
        {TextureClass::HUD, "Resource/Texture/HUD.png"}
        };
    };
}