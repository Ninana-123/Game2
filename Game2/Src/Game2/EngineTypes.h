#pragma once

typedef unsigned int EntityID;
constexpr EntityID EMPTY_ID = 0;

typedef unsigned int ComponentID;

typedef size_t ComponentIndex;
constexpr ComponentIndex INVALID_INDEX = 0;

enum class ComponentType {Position, Health, Hitbox, Transform};
