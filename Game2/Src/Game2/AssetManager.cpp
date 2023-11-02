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


    std::shared_ptr<Texture> AssetManager::loadTexture(const int mainIndex, const int subIndex /*= 0*/) {
        TextureKey key{ mainIndex, subIndex };

        // Check if the key exists in the map
        auto it = textureFilePaths.find(key);
        if (it == textureFilePaths.end()) {
            std::cerr << "Loading: Texture not found for MainID: " << mainIndex << ", SubIndex: " << subIndex << std::endl;
            return nullptr;
        }

        auto texture = std::make_shared<Texture>(it->second);
        if (!texture) {
            std::cerr << "Failed to load texture at MainID: " << mainIndex << ", SubIndex: " << subIndex << std::endl;
            return nullptr;
        }

        textures[key] = texture;
        return texture;
    }

    std::shared_ptr<Texture> AssetManager::loadTexture(const int mainIndex, const std::string& filePath, const int subIndex /*= 0*/) {
        TextureKey key{ mainIndex, subIndex };
        auto texture = std::make_shared<Texture>(filePath);
        textures[key] = texture;
        return texture;
    }

    std::shared_ptr<Texture> AssetManager::getTexture(int mainIndex, int subIndex /*= 0*/) const {
        TextureKey key{ mainIndex, subIndex };
        auto it = textures.find(key);
        if (it != textures.end()) {
            return it->second;
        }
        std::cerr << "Retrieving: Texture not found for MainID: " << mainIndex << ", SubIndex: " << subIndex << std::endl;
        return nullptr;
    }

    void AssetManager::updateTextureFilePath(int mainIndex, int subIndex ,const std::string& newFilePath) {
        TextureKey key{ mainIndex, subIndex };  // Assuming subIndex is always 0 for textureFilePaths
        auto it = textureFilePaths.find(key);
        if (it != textureFilePaths.end()) {
            it->second = newFilePath;
        }
        else {
            std::cerr << "Texture mainIndex not found: " << mainIndex << std::endl;
        }
    }

    /*
     std::shared_ptr<Texture> AssetManager::reloadTexture(int mainIndex, int subIndex) {
        TextureKey key{ mainIndex, subIndex };  // Assuming subIndex is always 0 for textureFilePaths
        auto it = textureFilePaths.find(key);
        if (it != textureFilePaths.end()) {
            return loadTexture(mainIndex, it->second);
        }
        else {
            std::cerr << "Texture main Index not found: " << mainIndex << std::endl;
            return nullptr;
        }

    }
    */
    
    std::vector<TextureKey> AssetManager::GetAllTextureKeys() const {
        std::vector<TextureKey> keys;
        for (const auto& pair : textures) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    const std::string& AssetManager::GetTexturePath(const TextureKey& textureKey) const {
        auto it = textureFilePaths.find(textureKey);
        if (it != textureFilePaths.end()) {
            return it->second;
        }
        static const std::string emptyString = "";
        std::cerr << "Texture Key not found: {" << textureKey.mainIndex << ", " << textureKey.subIndex << "}\n";
        return emptyString;
    }
}