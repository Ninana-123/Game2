#pragma once

#include "Component.h"
#include "EngineTypes.h"
#include "Vector2d.h"
#include "ShootingSystem.h"

namespace Engine
{
	class ShootingComponent : public Component
	{
	public:
		VECTORMATH::Vec2 shootingPosition; // Shooting position
		VECTORMATH::Vec2 targetPosition;   // Target position
		float shootingRate = 0.0f;         // Shooting rate
		bool isShooting = false;           // Flag indicating whether shooting is happening

		ComponentType GetType() const override { return ComponentType::Shooting; }

		Component* Clone() const override
		{
			ShootingComponent* cloneComponent = new ShootingComponent();
			cloneComponent->shootingPosition = shootingPosition;
			cloneComponent->targetPosition = targetPosition;
			cloneComponent->shootingRate = shootingRate;
			cloneComponent->isShooting = isShooting;
			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "shootingPosition: " << shootingPosition.x << ' ' << shootingPosition.y << '\n';
			outputStream << "targetPosition: " << targetPosition.x << ' ' << targetPosition.y << '\n';
			outputStream << "shootingRate: " << shootingRate << '\n';
			outputStream << "isShooting: " << isShooting << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			inputStream >> temp >> shootingPosition.x >> shootingPosition.y;
			inputStream >> temp >> targetPosition.x >> targetPosition.y;
			inputStream >> temp >> shootingRate;
			inputStream >> temp >> isShooting;
		}
	};
}