#pragma once
#include "BoundingBox.h"
#include "Collider.h"
#include "Component.h"
#include "Transform.h"

class Physics : public Component, public CollisionListener
{
private:
	float Gravity = -9.81f;
	Transform *TransformComp{ nullptr };
	Vector2 Velocity{ 0,0 };
	bool IsGrounded{ false };
	Collider* PhysicsCollider;
	float CollisionOffset{ .1f };
public:

	Physics() = default;


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
	void OnCollision(const CollisionEvent& p_collisionEvent) override;
};

