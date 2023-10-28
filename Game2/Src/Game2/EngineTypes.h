#pragma once

typedef unsigned int EntityID;
typedef unsigned int PrefabID;
constexpr EntityID EMPTY_ID = 0;

typedef unsigned int ComponentID;

enum class ComponentType { Collision, Transform, Texture, Physics, Unknown };

enum class TextureClass
{
    Null,
    Unit,
    Background,
    Tower,
};

enum class TextureType
{ 
    Null,
    Type1,
    Type2,
    Type3,
};
