#pragma once
#include "Component.h"
#include "Vector2.h"

class Transform : public Component
{
private:
	/**
	 * Vector2 that holds the current position of the entity 
	 */
	Vector2 Position{ Vector2(0, 0) };
public:

	/**
	 * Creates a new Transform component with a starting position of 0,0
	 */
	Transform() = default;

	/**
	 * Creates a new Transform component with an input starting position
	 * @param p_newPosition Starting position
	 */
	explicit Transform(Vector2 const p_newPosition)
	{
		Position = p_newPosition;
	}

	/**
	 * @return The current position
	 */
	Vector2 GetPosition() const
	{
		return Position;
	}

	/**
	 * Sets the position Vector2 to the new input position
	 * @param p_newPosition The new position of the game-object that owns this transform component
	 */
	void SetPosition(const Vector2& p_newPosition)
	{
		Position = p_newPosition;
	}

	virtual void Start() override {};

	virtual void Update(const float p_deltaTime) override {}

	virtual void Render() override {}




};

