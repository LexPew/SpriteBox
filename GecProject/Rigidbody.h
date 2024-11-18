#pragma once
#include "BoundingBox.h"
#include "Collider.h"
#include "Component.h"
#include "Transform.h"


/**
 * A rigid-body is made from a mass, size and position
 */
class Rigidbody : public Component, public CollisionListener
{
private:
	/**
	* Holds the linear position of the rigid-body in world space
	*/
	Vector2 Position;

	/**
	 * Holds the linear velocity of the rigid-body in world space
	 */
	Vector2 Velocity;

	/**
	 * Holds the linear acceleration of the rigid-body.
	 */
	Vector2 Acceleration;

	/**
	 * Holds the accumulated forces to be applied at the next simulation step, this is rest to zero at the end of each step.
	 */
	Vector2 ForceAccumulation{ 0,0 };


	/**
	 * Holds the drag force that will act upon the rigid-body slowing its velocity over time
	 */
	float Drag{ 0.9995f };

	/**
	 * Holds the gravity force that will act upon the rigid-body over time
	 */
	float Gravity{ 9.81f };

	/**
	 * Holds the transform component of this components entity
	 */
	Transform* TransformComp{ nullptr };


	/**
	 * Holds the collider of this components entity
	 */
	Collider* PhysicsCollider;

	float CollisionOffset{ .1f };
public:

	Rigidbody() = default;


	const Vector2& GetVelocity() const
	{
		return Velocity;
	}
	void SetVelocity(const Vector2& p_newVelocity) 
	{
		Velocity = p_newVelocity;
	}

	//~Rigidbody() override;
	void Start() override;
	void Update(const float p_deltaTime) override;
	void Render() override;
	void OnCollision(const CollisionEvent& p_collisionEvent) override;
};

