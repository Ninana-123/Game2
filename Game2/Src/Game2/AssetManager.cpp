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
#include "TransformComponent.h"

namespace Engine {

    // Function to load a texture with specified main and sub indices
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
        Logger::GetInstance().Log(LogLevel::Debug, std::to_string(texture->GetWidth()));
        Logger::GetInstance().Log(LogLevel::Debug, std::to_string(texture->GetHeight()));
        return texture;
    }

    // Function to load a texture with specified main index, file path, and sub index
    std::shared_ptr<Texture> AssetManager::loadTexture(const int mainIndex, const std::string& filePath, const int subIndex /*= 0*/) {
        TextureKey key{ mainIndex, subIndex };
        auto texture = std::make_shared<Texture>(filePath);
        textures[key] = texture;
        textureFilePaths[key] = filePath;
        return texture;
    }

    // Function to update the file path of a texture and reload it
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

    std::shared_ptr<Texture> AssetManager::getTexture(int mainIndex, int subIndex /*= 0*/) const {
        TextureKey key{ mainIndex, subIndex };
        auto it = textures.find(key);
        if (it != textures.end()) {
            return it->second;
        }
        std::cerr << "Retrieving: Texture not found for MainID: " << mainIndex << ", SubIndex: " << subIndex << std::endl;
        return nullptr;
    }

    // Function to retrieve a texture based on main and sub indices
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

    // Function to get all texture keys stored in the manager

    std::vector<TextureKey> AssetManager::GetAllTextureKeys() const {
        std::vector<TextureKey> keys;
        for (const auto& pair : textures) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    // Function to get the file path of a texture based on its key
    const std::string& AssetManager::GetTexturePath(const TextureKey& textureKey) const {
        auto it = textureFilePaths.find(textureKey);
        if (it != textureFilePaths.end()) {
            return it->second;
        }
        static const std::string emptyString = "";
        std::cerr << "Texture Key not found: {" << textureKey.mainIndex << ", " << textureKey.subIndex << "}\n";
        return emptyString;
    }

    // Function to load an audio file with the specified key
    std::shared_ptr<SoundInfo> AssetManager::loadAudio(const AudioKey& key) {
        // Assuming audioFilePaths is a member that holds paths to audio files
        auto it = audioFilePaths.find(key);
        if (it != audioFilePaths.end()) {
            // Create a SoundInfo with all the necessary parameters
            auto soundInfo = std::make_shared<SoundInfo>(it->second, key.filename, false, true, 1.0f, 0.0f);       
            // Store the loaded SoundInfo in the audios map
            audios[key] = soundInfo;
            return soundInfo;
        }
        else {
            std::cerr << "Audio file path not found for key: " << key.filename << std::endl;
            return nullptr;
        }
    }

    // Function to unload an audio file based on its key
    void AssetManager::unloadAudio(const AudioKey& key) {
        auto it = audios.find(key);
        if (it != audios.end()) {
            audios.erase(it);
        }
        else {
            std::cerr << "Trying to unload non-existing audio key: " << key.filename << std::endl;
        }
    }

    // Function to retrieve an audio file based on its key
    std::shared_ptr<SoundInfo> AssetManager::getAudio(const AudioKey& key) const {
        auto it = audios.find(key);
        if (it != audios.end()) {
            return it->second;
        }
        std::cerr << "Audio key not found: " << key.filename << std::endl;
        return nullptr;
    }

    // Function to update the file path of an audio file
    void AssetManager::updateAudioFilePath(const AudioKey& key, const std::string& newFilePath) {
        auto it = audioFilePaths.find(key);
        if (it != audioFilePaths.end()) {
            it->second = newFilePath;
        }
        else {
            std::cerr << "Audio key not found for update: " << key.filename << std::endl;
        }
    }

    // Get the file path of an audio file
    const std::string& AssetManager::getAudioPath(const AudioKey& key) const {
        auto it = audioFilePaths.find(key);
        if (it != audioFilePaths.end()) {
            return it->second;
        }
        static const std::string emptyString = "";
        std::cerr << "Audio key not found: " << key.filename << std::endl;
        return emptyString;
    }

    // Function to add an audio file path to the manager
    void AssetManager::AddAudioPath(const AudioKey& key, const std::string& path) {
        audioFilePaths[key] = path;
        std::cout << path<< std::endl;
    }
    
    //void AssetManager::LoadTextureFromJson(const nlohmann::json& jsonData) {
    //    int mainIndex = jsonData["mainIndex"];
    //    int subIndex = jsonData["subIndex"];
    //    std::string filePath = jsonData["filePath"];

    //    // Update or load the texture based on the information from JSON
    //    UpdateTexture(mainIndex, filePath, subIndex);
    //}

    //void AssetManager::SaveTexturePathsToJson(const std::string& filePath) const {
    //    nlohmann::json jsonTexturePaths;

    //    // Iterate through textures and add entries to the JSON object
    //    for (const auto& entry : textures) {
    //        nlohmann::json jsonEntry;
    //        jsonEntry["mainIndex"] = static_cast<int>(entry.first.mainIndex);
    //        jsonEntry["subIndex"] = entry.first.subIndex;
    //        jsonEntry["filePath"] = entry.second->GetFilePath();

    //        jsonTexturePaths.push_back(jsonEntry);
    //    }

    //    // Write the JSON object to a file
    //    std::ofstream file(filePath);
    //    file << jsonTexturePaths.dump(4);
    //}
}