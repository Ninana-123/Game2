/******************************************************************************/
/*!
\file		EngineTypes.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Declaration of types to be used in the custom engine
 */
 /******************************************************************************/
#ifndef ENGINE_ENGINETYPES_H
#define ENGINE_ENGINETYPES_H

// Entity and Prefab IDs
typedef unsigned int EntityID; 
typedef unsigned int PrefabID;
constexpr EntityID EMPTY_ID = 0; 
const int MAX_SUBINDEX = 6; 

// Component IDs and Types
typedef unsigned int ComponentID;
enum class ComponentType { Collision, Transform, Texture, Physics, Sprite, Pathfinding, Logic, Stats, Shooting, Unknown };

// Character State Enumeration
enum c_state { Static, Walking, Attack, Death, TowerDestroyed, CastleDestroyed, Idle };

// Unit Type Enum
enum unit_type { none, infantry, tank, archer, tower, base };

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
enum class Layer { World, Interactive, Editable, inGameGUI, BeforeSpawn, Tower, Castle, Arrow }; //!< Enumeration for different layers in the game.

// Texture Class Enumeration
enum TextureClass //!< Enumeration for different texture classes.
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
    pausePressed,
    playPressed,
    settingsPressed,
    mainMenuBG,
    mainMenuPlay,
    mainMenuGameInfo,
    mainMenuCredits,
    Logo,
    victoryScreen,
    catHPEmpty,
    catHP1,
    catHP2,
    catHP3,
    catHP4,
    catHP5,
    catHP6,
    catHP7,
    catHP8,
    catHP9,
    towerHPEmpty,
    towerHP1,
    towerHP2,
    towerHP3,
    towerHP4,
    towerHP5,
    towerHP6,
    towerHP7,
    towerHP8,
    towerHP9,
    Arrow,

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

struct AudioKey {
    std::string filename;

    AudioKey(const std::string& file) : filename(file) {}

    bool operator==(const AudioKey& other) const {
        return filename == other.filename;
    }


    bool operator<(const AudioKey& other) const {
        return filename < other.filename;
    }


    friend struct std::hash<AudioKey>;
};

namespace std {
    template <>
    struct hash<AudioKey> {
        std::size_t operator()(const AudioKey& key) const {
            return std::hash<std::string>()(key.filename);
        }
    };
}

// Animation Mode Enumeration
enum anim_mode
{
    loop, one_time
};
#endif ENGINE_ENGINETYPES_H