#pragma once
#include "Component.h"
#include "GameObject.h"
#include "IGraphics.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
#include "Transform.h"

class PhysicsBody : public Component
{
private:
	Transform* TransformComponent{ nullptr };

public:
	Rigidbody* PRigidBody;

	PhysicsBody(const Vector2& p_position, const Vector2& p_velocity, const Vector2& p_acceleration, const float p_mass, const float p_width, const float p_height)
	{
		PRigidBody = new Rigidbody{ p_position, p_velocity, p_acceleration, p_mass, p_width, p_height };
	}
	PhysicsBody(const Vector2& p_position, const Vector2& p_velocity, const Vector2& p_acceleration, const float p_mass, const Sprite& p_sprite)
	{
		const Vector2& spriteRect = IGraphics::GraphicsHandlerInstance->CalculateBounds(p_sprite);
		PRigidBody = new Rigidbody{ p_position, p_velocity, p_acceleration, p_mass,spriteRect.X,spriteRect.Y};
	}
	void Start() override
	{

		TransformComponent = Owner->GetComponent<Transform>();
	}
	void Update(const float p_deltaTime) override
	{
		TransformComponent->SetPosition(PRigidBody->GetPosition());
	}

	void Render() override
	{
		IGraphics::GraphicsHandlerInstance->DrawBounds(PRigidBody->GetRect());
	}
	~PhysicsBody() override
	{
	delete PRigidBody;
	}
};

