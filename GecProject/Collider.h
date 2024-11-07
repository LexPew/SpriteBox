#pragma once
#include "BoundingBox.h"
#include "CollisionLayers.h"
#include "CollisionListener.h"
#include "Component.h"
class Collider : public Component
{
private:
	int Bitmask = 0;
	BoundingBox ColliderBox;
	std::vector<CollisionListener*> CollisionEventListeners;
	Transform* TransformComponent;
public:

	Collider(const int p_bitmask)
	{
		ColliderBox = {0,0,100,100};
		Bitmask = p_bitmask;
	}

	Collider(const BoundingBox& p_boundingBox, const int p_bitmask)
	{
		ColliderBox = p_boundingBox;
		Bitmask = p_bitmask;
	}

	const BoundingBox& GetCollisionBounds() const
	{
		return ColliderBox;
	}


	int GetBitMask() const
	{
		return Bitmask;
	}

	void CheckCollision(const Collider& p_otherCollider) const;

	void AddListener(CollisionListener* p_collisionListener);
	void Start() override;
	void Update(const float p_deltaTime) override;
	void Render() override;

	void CalculateBoundsFromSprite();
	private:

		void NotifyListeners(const CollisionEvent& p_collisionEvent) const;
};

