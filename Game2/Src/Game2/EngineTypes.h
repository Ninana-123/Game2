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
const int MAX_SUBINDEX = 3;

typedef unsigned int ComponentID;
enum class ComponentType { Collision, Transform, Texture, Physics, Sprite, Pathfinding, Unknown };

enum c_state { Static, Walking, Attack, Idle };
std::string c_stateToString(c_state state);

enum class Layer { World, Interactive, Editable, inGameGUI, BeforeSpawn, Tower };

enum TextureClass
{
    Background,
    Infanty,
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
    pausePressed,
    playPressed,
    settingsPressed,
    mainMenuBG,
    mainMenuPlay,
    mainMenuGameInfo,
    mainMenuCredits,
    Logo,
    TextureClassCount
};

struct TextureKey 
{
    int mainIndex;
    int subIndex;

    // Equality operator
    bool operator==(const TextureKey& other) const 
    {
        return mainIndex == other.mainIndex && subIndex == other.subIndex;
    }

    // Inequality operator
    bool operator!=(const TextureKey& other) const 
    {
        return !(*this == other);
    }

    bool operator<(const TextureKey& right) const 
    {
        if (mainIndex == right.mainIndex) 
        {
            return subIndex < right.subIndex;
        }
        return mainIndex < right.mainIndex;
    }

    static std::size_t hashFunction(const TextureKey& key) 
    {
        // Combine the hashes of mainIndex and subIndex
        return std::hash<int>()(key.mainIndex) ^ std::hash<int>()(key.subIndex);
    }
};

// specialization of std::hash for TextureKey to be used in maps
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