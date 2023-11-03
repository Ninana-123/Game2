/******************************************************************************/
/*!
\file		AssetManager.cpp
\author 	Liu Xujie 
\co         Tristan Tham Rui Hong (50%)
\par    	email: l.xujie@digipen.edu
\date   	29/09/2023
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

    /*!*********************************************************************
        \brief
        Loads a texture based on main and sub indices.

        \param mainIndex
        The main index used to look up the texture in the map.

        \param subIndex
        The sub index used to look up the texture in the map, default is 0.

        \return
        A shared pointer to the loaded Texture, or nullptr if the texture
        could not be loaded.
    *************************************************************************/
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
    /*!*********************************************************************
    \brief
    Loads a texture from the specified file path and associates it with main and sub indices.

    \param mainIndex
    The main index for the texture which is part of the key used for storing the texture.
    
    \param filePath
    The file path of the texture to be loaded.

    \param subIndex
    The sub index for the texture which is part of the key used for storing the texture, default is 0.

    \return
    A shared pointer to the newly loaded Texture.
    *************************************************************************/
    std::shared_ptr<Texture> AssetManager::loadTexture(const int mainIndex, const std::string& filePath, const int subIndex /*= 0*/) {
        TextureKey key{ mainIndex, subIndex };
        auto texture = std::make_shared<Texture>(filePath);
        textures[key] = texture;
        textureFilePaths[key] = filePath;
        return texture;
    }
    /*!*********************************************************************
    \brief
    Updates an existing texture or loads a new one if it doesn't exist.

    \param mainIndex
    The main index for the texture which is part of the key used for 
    identifying the texture to update.

    \param filePath
    The new file path of the texture to be used for updating or loading 
    the texture.

    \param subIndex
    The sub index for the texture which is part of the key used for 
    identifying the texture to update, default is 0.
    *************************************************************************/
    void AssetManager::UpdateTexture(int mainIndex, const std::string& filePath, int subIndex)
    {
        TextureKey textureKey{ mainIndex, subIndex };
        auto textureIter = textures.find(textureKey);

        if (textureIter != textures.end()) {
            // The texture already exists, update its filepath
            updateTextureFilePath(mainIndex, subIndex, filePath);
            std::shared_ptr<Texture> texture = textureIter->second;
            texture->SetFilePath(filePath);
            texture->Load();
            texture->UpdateBufferData();
        }
        else {
            // The texture doesn't exist, create a new one
            loadTexture(mainIndex, filePath, subIndex);
        }
    }
    /*!*********************************************************************
        \brief
        Retrieves a shared pointer to a Texture object if it exists.

    
        \param mainIndex
        The main index for the texture which is part of the key used for
        identifying the texture to retrieve.

        \param subIndex
        The sub index for the texture which is part of the key used for 
        identifying the texture to retrieve, default is 0.

        \return
        A shared pointer to the Texture if found; otherwise, nullptr.

    **************************************************************************/
    std::shared_ptr<Texture> AssetManager::getTexture(int mainIndex, int subIndex /*= 0*/) const {
        TextureKey key{ mainIndex, subIndex };
        auto it = textures.find(key);
        if (it != textures.end()) {
            return it->second;
        }
        std::cerr << "Retrieving: Texture not found for MainID: " << mainIndex << ", SubIndex: " << subIndex << std::endl;
        return nullptr;
    }
    /*!*********************************************************************
        \brief
        Updates the file path of an existing texture in the asset manager.


        \param mainIndex
        The main index for the texture, used as part of the key to 
        locate the texture in the map.

        \param subIndex
        The sub index for the texture, used as part of the key to 
        locate the texture in the map.

        \param newFilePath
        The new file path to associate with the texture.

    **************************************************************************/
    void AssetManager::updateTextureFilePath(int mainIndex, int subIndex ,const std::string& newFilePath) {
        TextureKey key{ mainIndex, subIndex }; 
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
    /*!*********************************************************************
        \brief
        Retrieves all texture keys from the asset manager.


        \return
        A std::vector containing all the texture keys present in the asset manager.

    **************************************************************************/
    std::vector<TextureKey> AssetManager::GetAllTextureKeys() const {
        std::vector<TextureKey> keys;
        for (const auto& pair : textures) {
            keys.push_back(pair.first);
        }
        return keys;
    }
    /*!*********************************************************************
        \brief
        Gets the file path of a texture associated with a specific texture key.


       \param textureKey
        The TextureKey structure that contains the main index and sub index identifying the texture.

        \return
        A constant reference to the file path string associated with the texture key, or an empty string if the key is not found.

    **************************************************************************/
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