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

namespace Engine {
    class AssetManager {
    private:
        std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

    public:
        std::shared_ptr<Texture> loadTexture(const std::string& name, const std::string& filePath);
        std::shared_ptr<Texture> getTexture(const std::string& name) const;
    };
}