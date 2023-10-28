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


namespace Engine {

        std::shared_ptr<Texture> AssetManager::loadTexture(const std::string& name, const std::string& filePath) {
            auto texture = std::make_shared<Texture>(filePath);
            textures[name] = texture;
            return texture;
        }

        std::shared_ptr<Texture> AssetManager::getTexture(const std::string& name) const {
            auto it = textures.find(name);
            if (it != textures.end()) {
                return it->second;
            }
            std::cerr << "Texture not found: " << name << std::endl;
            return nullptr;
        }
}