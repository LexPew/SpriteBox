#pragma once
#include "Component.h"
#include "Vector2.h"

class TransformComponent : public Component
{
private:
	Vector2 position{ Vector2(0, 0) };
public:
	TransformComponent(){}
	TransformComponent(Vector2 newPosition)
	{
		position = newPosition;
	}
	Vector2 GetPosition()
	{
		return position;
	}
	void SetPosition(Vector2 newPosition)
	{
		position = newPosition;
	}


	// Inherited via Component
	virtual std::string GetType() override { return std::string("Transform"); };

	virtual void Update(float deltaTime) override {};

	virtual void Render(IGraphics& graphicsHandler) override {};

};

