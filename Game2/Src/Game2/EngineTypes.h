#pragma once

typedef unsigned int EntityID;
typedef unsigned int PrefabID;
constexpr EntityID EMPTY_ID = 0;

typedef unsigned int ComponentID;

enum class ComponentType { Collision, Transform, Texture, Physics, Unknown };

enum TextureClass
{
    Background,
    Warrior,
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
    TextureClassCount,
};