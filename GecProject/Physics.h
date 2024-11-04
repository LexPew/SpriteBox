#pragma once
#include "BoundingBox.h"
#include "Component.h"
#include "Transform.h"

class Physics : public Component
{
private:
	int Bitmask{0};
	float Gravity = 0;
	Transform *TransformComp{ nullptr };
	Vector2 Velocity{ 0,0 };
	BoundingBox SpriteBounds;
	float CollisionOffset{ .1f };
public:

	Physics(const int p_collisionBitMask)
	{
		Bitmask = p_collisionBitMask;
	}

	int GetBitMask() const
	{
		return Bitmask;
	}
	const BoundingBox& GetBounds() const
	{
		return SpriteBounds;
	}
	const Vector2& GetVelocity() const
	{
		return Velocity;
	}
	void SetVelocity(const Vector2& p_newVelocity) 
	{
		Velocity = p_newVelocity;
	}

	//~Physics() override;
	void Start() override;
	void Update(const float p_deltaTime) override;
	void Render() override;
	void OnCollide(const BoundingBox& p_otherObject);
};

