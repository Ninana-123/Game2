/******************************************************************************/
/*!
\file		AssetManager.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		This file contains the implementation of the Asset Manager which 
			handles the assets used by the engine.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "AssetManager.h"
#include "TextureComponent.h"
#include "logger.h"


namespace Engine {


        std::shared_ptr<Texture> AssetManager::loadTexture(const int texid, const std::string& filePath) {
            auto texture = std::make_shared<Texture>(filePath);
            textures[texid] = texture;
            textureFilePaths[texid] = filePath;
            return texture;
        }

        std::shared_ptr<Texture> AssetManager::getTexture(const int texid) const {
            auto it = textures.find(texid);
            if (it != textures.end()) {
                return it->second;
            }
            std::cerr << "Texture ID not found: " << texid << std::endl;
            return nullptr;
        }

        void AssetManager::updateTextureFilePath(int texid, const std::string& newFilePath) {
            auto it = textureFilePaths.find(texid);
            if (it != textureFilePaths.end()) {
                it->second = newFilePath;
            }
            else {
                std::cerr << "Texture ID not found: " << texid << std::endl;
            }
        }

        std::shared_ptr<Texture> AssetManager::reloadTexture(int texid) {
            auto it = textureFilePaths.find(texid);
            if (it != textureFilePaths.end()) {
                return loadTexture(texid, it->second);
            }
            else {
                std::cerr << "Texture ID not found: " << texid << std::endl;
                return nullptr;
            }
        }

        const std::string& AssetManager::GetTexturePath(int texid) const {
            auto it = textureFilePaths.find(texid);
            if (it != textureFilePaths.end()) {
                return it->second;
            }
            static const std::string emptyString = "";
            std::cerr << "Texture ID not found: " << texid << std::endl;
            return emptyString;
        }


}