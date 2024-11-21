#pragma once
#include "Component.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "SFML/Graphics.hpp"
class CharacterController : public Component
{
public:
	float baseMovementSpeed = 1000.0f;
	float jumpForce = 50000.0f;
	PhysicsBody* physics{ nullptr };
	void Start() override
	{
		physics = Owner->GetComponent<PhysicsBody>();
	}
	void Update(const float p_deltaTime) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		{
			physics->PRigidBody->SetVelocity({-baseMovementSpeed, physics->PRigidBody->GetVelocity().Y });
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			physics->PRigidBody->SetVelocity({baseMovementSpeed, physics->PRigidBody->GetVelocity().Y });
		}
		else
		{
			physics->PRigidBody->SetVelocity({ 0 + (baseMovementSpeed * p_deltaTime), physics->PRigidBody->GetVelocity().Y });
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			physics->PRigidBody->AddForce({0, -jumpForce });
		}
	}
};

