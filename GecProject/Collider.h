#pragma once
#include "AABBBoundingBox.h"
#include "CollisionLayers.h"
#include "CollisionListener.h"
#include "Component.h"
#include "Physics.hpp"

class Collider : public Component
{
private:
	bool IsStatic{false};
	int CollisionLayer = 0;
	AABBBoundingBox ColliderBox;
	std::vector<CollisionListener*> CollisionEventListeners;

	Transform* TransformComponent;
public:
	p2d::RectangleBody ColliderBox2;
	bool Overlapping{false};
	Collider(const int p_collisionLayer, const bool p_static)
	{
		ColliderBox = {0,0,100,100};
		CollisionLayer = p_collisionLayer;
		IsStatic = p_static;
	}

	Collider(const AABBBoundingBox& p_boundingBox, const int p_collisionLayer, const bool p_static)
	{
		ColliderBox = p_boundingBox;
		CollisionLayer = p_collisionLayer;
		IsStatic = p_static;
	}

	const AABBBoundingBox& GetCollisionBounds() const
	{
		return ColliderBox;
	}


	int GetCollisionLayer() const
	{
		return CollisionLayer;
	}

	bool GetIsStatic() const
	{
		return IsStatic;
	}



	void AddListener(CollisionListener* p_collisionListener);
	void Start() override;
	void Update(const float p_deltaTime) override;
	void Render() override;

	void CalculateBoundsFromSprite();
	void NotifyListeners(const CollisionEvent& p_collisionEvent) const;
};

