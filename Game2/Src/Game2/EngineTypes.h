#pragma once

typedef unsigned int EntityID;
constexpr EntityID EMPTY_ID = 0;

typedef unsigned int ComponentID;

enum class ComponentType { Collision, Transform, Texture, Physics };

enum TextureClass
{
    Background,
    Warrior,
    Tank,
    Archer,
    Tower,
    Castle,
    TextureClassCount
};