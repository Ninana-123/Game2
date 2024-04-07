/******************************************************************************/
/*!
\file		AssetManager.h
\author 	Liu Xujie
\co         Tristan Tham Rui Hong 
\par    	email: l.xujie@digipen.edu
\date   	29/09/2023
\brief		This file contains the declaration of the main Assets Manager

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_ASSETMANAGER_H
#define ENGINE_ASSETMANAGER_H

#include "pch.h"
#include "Texture.h"
#include "EngineTypes.h"
#include "AudioEngine.h"
#include <filesystem>

namespace Engine {

    class AssetManager {
    private:
        // Change the key type to TextureKey and use the hash function
        std::unordered_map<TextureKey, std::shared_ptr<Texture>> textures;
        std::unordered_map<AudioKey, std::shared_ptr<SoundInfo>> audios;

    public:
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
        std::shared_ptr<Texture> loadTexture(const int mainIndex, const int subIndex = 0);

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
        std::shared_ptr<Texture> loadTexture(const int mainIndex, const std::string& filePath, const int subIndex = 0); //Overload that takes in custom filepath
        
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
        void UpdateTexture(int mainIndex, const std::string& filePath, int subIndex);

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
        std::shared_ptr<Texture> getTexture(int mainIndex, int subIndex = 0) const;

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
        void updateTextureFilePath(int mainIndex, int subIndex, const std::string& newFilePath);

        // Update the function signature
        //std::shared_ptr<Texture> reloadAllTexture();

        /*!*********************************************************************
        \brief
        Retrieves all texture keys from the asset manager.


        \return
        A std::vector containing all the texture keys present in the asset manager.

        **************************************************************************/
        std::vector<TextureKey> GetAllTextureKeys() const;

        /*!*********************************************************************
        \brief
        Gets the file path of a texture associated with a specific texture key.


       \param textureKey
        The TextureKey structure that contains the main index and sub index identifying the texture.

        \return
        A constant reference to the file path string associated with the texture key, 
        or an empty string if the key is not found.

        **************************************************************************/
        const std::string& GetTexturePath(const TextureKey& textureKey) const;


        /**
        * @brief Returns a reference to the unordered map containing all loaded textures.
        * @return A reference to the map of textures.
        */
        // Update the function signature
        inline std::unordered_map<TextureKey, std::shared_ptr<Texture>>& GetAllTextures() {
            return textures;
        }


        /**
        * @brief Returns a reference to the map containing file paths for all textures.
        * @return A reference to the map of texture file paths.
        */
        const std::map<TextureKey, std::string>& GetTextureFilePaths() const {
            return textureFilePaths;
        }

        /**
        * @brief Loads an audio file and returns a shared pointer to the associated SoundInfo.
        * @param key The key identifying the audio file.
        * @return A shared pointer to the loaded SoundInfo, or nullptr if the file is not found.
        */
        std::shared_ptr<SoundInfo> loadAudio(const AudioKey& key, bool loop);

        /**
        * @brief Unloads an audio file based on its key.
        * @param key The key identifying the audio file to be unloaded.
        */
        void unloadAudio(const AudioKey& key);

        /**
        * @brief Retrieves a shared pointer to the SoundInfo associated with the specified audio key.
        * @param key The key identifying the audio file.
        * @return A shared pointer to the SoundInfo, or nullptr if the file is not found.
        */
        std::shared_ptr<SoundInfo> getAudio(const AudioKey& key) const;

        /**
        * @brief Updates the file path of an audio file.
        * @param key The key identifying the audio file.
        * @param newFilePath The new file path for the audio file.
        */
        void updateAudioFilePath(const AudioKey& key, const std::string& newFilePath);

        /**
        * @brief Retrieves the file path of an audio file based on its key.
        * @param key The key identifying the audio file.
        * @return The file path of the audio file, or an empty string if the file is not found.
        */
        const std::string& getAudioPath(const AudioKey& key) const;

        /**
        * @brief Adds an audio file path to the manager.
        * @param key The key identifying the audio file.
        * @param path The file path of the audio file.
        */
        void AddAudioPath(const AudioKey& key, const std::string& path);

        /**
        * @brief Returns a vector containing all audio keys currently loaded in the manager.
        * @return A vector of audio keys.
        */
        const std::vector<AudioKey>& GetAllAudioFiles() const {
            
            std::vector<AudioKey> allAudioKeys;
            for (const auto& audioPair : audios) {
                allAudioKeys.push_back(audioPair.first);
            }
            return allAudioKeys;
        }
    private:

        std::map<AudioKey, std::string> audioFilePaths;
        // Use the TextureKey structure instead of int for the map
        std::map<TextureKey, std::string> textureFilePaths = {
            { {TextureClass::Background,        0}, "Resource/Texture/Background.png" },
            { {TextureClass::Infantry,          0}, "Resource/Texture/Warrior.png" },
            { {TextureClass::Infantry,          1}, "Resource/Texture/WarriorWalking.png" },
            { {TextureClass::Infantry,          2}, "Resource/Texture/WarriorAttack.png" },
            { {TextureClass::Tank,              0}, "Resource/Texture/Tank.png" },
            { {TextureClass::Tank,              1}, "Resource/Texture/TankWalking.png" },
            { {TextureClass::Tank,              2}, "Resource/Texture/TankAttack.png" },
            { {TextureClass::Archer,            0}, "Resource/Texture/Archer.png" },
            { {TextureClass::Archer,            1}, "Resource/Texture/ArcherWalking.png" },
            { {TextureClass::Archer,            2}, "Resource/Texture/ArcherAttack.png" },
            { {TextureClass::Archer,            3}, "Resource/Texture/ArcherDeath.png" },
            { {TextureClass::Tower,             0}, "Resource/Texture/Tower.png" },
            { {TextureClass::Tower,             4}, "Resource/Texture/TowerDestroyed.png" },

            { {TextureClass::Castle,            0}, "Resource/Texture/Castle.png" },
            { {TextureClass::Castle,            5}, "Resource/Texture/CastleDestroyed.png" },

            { {TextureClass::HUD,               0}, "Resource/Texture/HUD.png" },
            { {TextureClass::HUDInfantry,       0}, "Resource/Texture/HUDInfantry.png"},
            { {TextureClass::HUDArcher,         0}, "Resource/Texture/HUDArcher.png"},
            { {TextureClass::HUDTank,           0}, "Resource/Texture/HUDTank.png"},
            { {TextureClass::pauseButton,       0}, "Resource/Texture/pausebutton.png"},
            { {TextureClass::playButton,        0}, "Resource/Texture/playbutton.png"},
            { {TextureClass::settingsButton,    0}, "Resource/Texture/settingsbutton.png"},
            { {TextureClass::pausePressed,      0}, "Resource/Texture/pausePressed.png"},
            { {TextureClass::playPressed,       0}, "Resource/Texture/playPressed.png"},
            { {TextureClass::settingsPressed,   0}, "Resource/Texture/settingsPressed.png"},
            { {TextureClass::mainMenuBG,        0}, "Resource/Texture/mainMenuBG.jpg"},
            { {TextureClass::mainMenuPlay,      0}, "Resource/Texture/mmPlay.png"},
            { {TextureClass::mainMenuGameInfo,  0}, "Resource/Texture/mmGameInfo.png"},
            { {TextureClass::mainMenuCredits,   0}, "Resource/Texture/mmCredits.png"},
            { {TextureClass::Logo,              0}, "Resource/Texture/Logo.png"},
            { {TextureClass::victoryScreen,     0}, "Resource/Texture/victory_screen.png"},
            { {TextureClass::catHPEmpty,        0}, "Resource/Texture/hp_empty.PNG" },
            { {TextureClass::catHP1,            0}, "Resource/Texture/cats_hp_1.PNG" },
            { {TextureClass::catHP2,            0}, "Resource/Texture/cats_hp_2.PNG" },
            { {TextureClass::catHP3,            0}, "Resource/Texture/cats_hp_3.PNG" },
            { {TextureClass::catHP4,            0}, "Resource/Texture/cats_hp_4.PNG" },
            { {TextureClass::catHP5,            0}, "Resource/Texture/cats_hp_5.PNG" },
            { {TextureClass::catHP6,            0}, "Resource/Texture/cats_hp_6.PNG" },
            { {TextureClass::catHP7,            0}, "Resource/Texture/cats_hp_7.PNG" },
            { {TextureClass::catHP8,            0}, "Resource/Texture/cats_hp_8.PNG" },
            { {TextureClass::catHP9,            0}, "Resource/Texture/cats_hp_9full.PNG" },
            { {TextureClass::towerHPEmpty,      0}, "Resource/Texture/hp_empty.PNG" },
            { {TextureClass::towerHP1,          0}, "Resource/Texture/Tower_hp_1.PNG" },
            { {TextureClass::towerHP2,          0}, "Resource/Texture/Tower_hp_2.PNG" },
            { {TextureClass::towerHP3,          0}, "Resource/Texture/Tower_hp_3.PNG" },
            { {TextureClass::towerHP4,          0}, "Resource/Texture/Tower_hp_4.PNG" },
            { {TextureClass::towerHP5,          0}, "Resource/Texture/Tower_hp_5.PNG" },
            { {TextureClass::towerHP6,          0}, "Resource/Texture/Tower_hp_6.PNG" },
            { {TextureClass::towerHP7,          0}, "Resource/Texture/Tower_hp_7.PNG" },
            { {TextureClass::towerHP8,          0}, "Resource/Texture/Tower_hp_8.PNG" },
            { {TextureClass::towerHP9,          0}, "Resource/Texture/Tower_hp_9.PNG" },
            { {TextureClass::Arrow,             0}, "Resource/Texture/Arrow.png" },

            { {TextureClass::cutScene1,         0}, "Resource/Texture/cutScene1.PNG" },
            { {TextureClass::cutScene2,         0}, "Resource/Texture/cutScene2.PNG" },
            { {TextureClass::cutScene3,         0}, "Resource/Texture/cutScene3.PNG" },
            { {TextureClass::cutScene4,         0}, "Resource/Texture/cutScene4.PNG" },
            { {TextureClass::cutScene5,         0}, "Resource/Texture/cutScene5.PNG" },
            { {TextureClass::cutScene6,         0}, "Resource/Texture/cutScene6.PNG" },
            { {TextureClass::cutScene7,         0}, "Resource/Texture/cutScene7.PNG" },
            { {TextureClass::cutScene8,         0}, "Resource/Texture/whiteScreen.PNG" },

            { {TextureClass::mainMenuScreen,    0}, "Resource/Texture/mainMenuBG.jpg" },
            { {TextureClass::defeatScreen,      0}, "Resource/Texture/mainmenu_screen.PNG" },
            { {TextureClass::pauseScreen,       0}, "Resource/Texture/mainmenu_screen.PNG" },
            { {TextureClass::startingPoint,       0}, "Resource/Texture/starting point_idle.PNG" },

            { {TextureClass::archerArrow,    0}, "Resource/Texture/archer_arrow.png" },
            { {TextureClass::infantryVFX,      2}, "Resource/Texture/infantry_vfx.png" },
            { {TextureClass::tankVFX,       2}, "Resource/Texture/tank_vfx.png" },
            { {TextureClass::archerVFX,       2}, "Resource/Texture/archer_vfx.png" },
            { {TextureClass::towerVFX,       0}, "Resource/Texture/tower_attack.png" }

        };
    };
}
#endif ENGINE_ASSETMANAGER_H