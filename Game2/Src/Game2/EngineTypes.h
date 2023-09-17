#pragma once

typedef unsigned int EntityID;
constexpr EntityID EMPTY_ID = 0;

typedef unsigned int ComponentID;
typedef unsigned int ComponentType;

typedef size_t ComponentIndex;
constexpr ComponentIndex INVALID_INDEX;

enum class ComponentType {Position, Health};
