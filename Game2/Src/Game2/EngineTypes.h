#pragma once

typedef unsigned int EntityID;
typedef unsigned int PrefabID;
constexpr EntityID EMPTY_ID = 0;
const int MAX_SUBINDEX = 2;

typedef unsigned int ComponentID;

enum class ComponentType { Collision, Transform, Texture, Physics, Sprite, Unknown };

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
    TextureClassCount
};

enum anim_mode
{
    loop, one_time
};

struct TextureKey {
    int mainIndex;
    int subIndex;

    // Constructors and other members...

    // Equality operator
    bool operator==(const TextureKey& other) const {
        return mainIndex == other.mainIndex && subIndex == other.subIndex;
    }

    // Inequality operator
    bool operator!=(const TextureKey& other) const {
        return !(*this == other);
    }

    bool operator<(const TextureKey& right) const {
        // Compare based on mainIndex and subIndex, or any other desired criteria
        if (mainIndex == right.mainIndex) {
            return subIndex < right.subIndex;
        }
        return mainIndex < right.mainIndex;
    }

    static std::size_t hashFunction(const TextureKey& key) {
        // Combine the hashes of mainIndex and subIndex
        return std::hash<int>()(key.mainIndex) ^ std::hash<int>()(key.subIndex);
    }
};

// Specialization of std::hash for TextureKey
template <>
struct std::hash<TextureKey> {
    std::size_t operator()(const TextureKey& key) const {
        return TextureKey::hashFunction(key);
    }
};