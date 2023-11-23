/******************************************************************************/
/*!
\file		EngineTypes.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Declaration of types to be used in the custom engine

 */
 /******************************************************************************/
#pragma once

typedef unsigned int EntityID;
typedef unsigned int PrefabID;
constexpr EntityID EMPTY_ID = 0;
const int MAX_SUBINDEX = 2;

typedef unsigned int ComponentID;
enum class ComponentType { Collision, Transform, Texture, Physics, Sprite, Pathfinding, Unknown };

enum c_state { Static, Walking, Idle, Attack };
std::string c_stateToString(c_state state);

enum class Layer { World, Interactive, Editable, inGameGUI, BeforeSpawn, Tower };

enum TextureClass
{
    Background,
    Infantry,
    Tank,
    Archer,
    Tower,
    Castle,
    HUD,
    HUDInfantry,
    HUDArcher,
    HUDTank,
    pauseButton,
    playButton,
    settingsButton,
    TextureClassCount
};

struct TextureKey
{
    std::string textureClass; // Updated to use std::string for the "class" field
    int mainIndex;
    int subIndex;

    // Constructor with std::string for the "class" field
    TextureKey(const std::string& textureClass, int mainIndex, int subIndex)
        : textureClass(textureClass), mainIndex(mainIndex), subIndex(subIndex) {}

    // Equality operator
    bool operator==(const TextureKey& other) const
    {
        return textureClass == other.textureClass &&
            mainIndex == other.mainIndex &&
            subIndex == other.subIndex;
    }

    // Inequality operator
    bool operator!=(const TextureKey& other) const
    {
        return !(*this == other);
    }

    // Less than operator for sorting
    bool operator<(const TextureKey& right) const
    {
        if (textureClass == right.textureClass)
        {
            if (mainIndex == right.mainIndex)
            {
                return subIndex < right.subIndex;
            }
            return mainIndex < right.mainIndex;
        }
        return textureClass < right.textureClass;
    }

    // Hash function for std::unordered_map
    static std::size_t hashFunction(const TextureKey& key)
    {
        // Combine the hashes of textureClass, mainIndex, and subIndex
        return std::hash<std::string>()(key.textureClass) ^
            std::hash<int>()(key.mainIndex) ^
            std::hash<int>()(key.subIndex);
    }
};

// specialization of std::hash for TextureKey to be used in std::unordered_map
template <>
struct std::hash<TextureKey> {
    std::size_t operator()(const TextureKey& key) const {
        return TextureKey::hashFunction(key);
    }
};

enum anim_mode
{
    loop, one_time
};