#pragma once
#include <string>

class IGraphics;
class GameObject;

class Component
{
protected:
	GameObject* owner;
public:
	virtual ~Component() = default;
	//Returns the identifier for this component, e.g Transform, Sprite, etc

	virtual std::string GetType() = 0;
	
	virtual void Update(float deltaTime) = 0;

	virtual void Render(IGraphics& graphicsHandler) = 0;

	void SetOwner(GameObject* gameObject)
	{
		this->owner = gameObject;
	}
};

