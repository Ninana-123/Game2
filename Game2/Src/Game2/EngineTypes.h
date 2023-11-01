#pragma once

typedef unsigned int EntityID;
typedef unsigned int PrefabID;
constexpr EntityID EMPTY_ID = 0;

typedef unsigned int ComponentID;

enum class ComponentType { Collision, Transform, Texture, Physics, Animation, Unknown };

enum TextureClass
{
    Background,
    Infanty,
    Tank,
    Archer,
    Tower,
    Castle,
    HUD,
    TextureClassCount
};