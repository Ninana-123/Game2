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

// Entity and Prefab IDs
typedef unsigned int EntityID; 
typedef unsigned int PrefabID;
constexpr EntityID EMPTY_ID = 0; 
const int MAX_SUBINDEX = 4; 

typedef unsigned int ComponentID;
enum class ComponentType { Collision, Transform, Texture, Physics, Sprite, Pathfinding, Shooting, Unknown };

// Character State Enumeration
enum c_state { Static, Walking, Attack, Death, Idle }; 

/*!
\brief
Converts a character state to a string.

\param state
The character state to convert.

\return
A string representation of the character state.
*/
std::string c_stateToString(c_state state);

// Layer Enumeration
enum class Layer { World, Interactive, Editable, inGameGUI, BeforeSpawn, Tower, Castle }; //!< Enumeration for different layers in the game.

// Texture Class Enumeration
enum TextureClass //!< Enumeration for different texture classes.
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
    Arrow,
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

// Texture Key Structure
struct TextureKey
{
    int mainIndex; //!< Main index of the texture.
    int subIndex;  //!< Subindex of the texture.

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

    // Less than operator
    bool operator<(const TextureKey& right) const
    {
        if (mainIndex == right.mainIndex)
        {
            return subIndex < right.subIndex;
        }
        return mainIndex < right.mainIndex;
    }

    // Hash function for TextureKey
    static std::size_t hashFunction(const TextureKey& key)
    {
        // Combine the hashes of mainIndex and subIndex
        return std::hash<int>()(key.mainIndex) ^ std::hash<int>()(key.subIndex);
    }
};

// Specialization of std::hash for TextureKey to be used in maps
template <>
struct std::hash<TextureKey> {
    std::size_t operator()(const TextureKey& key) const {
        return TextureKey::hashFunction(key);
    }
};

// Animation Mode Enumeration
enum anim_mode 
{
    loop, one_time
};