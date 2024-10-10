#pragma once
#include <string>
#include <typeinfo>
class GameObject;

class Component
{
protected:
	GameObject* owner{ nullptr };
public:
	virtual ~Component() = default;

	std::string GetType() //Returns the identifier for this component, e.g Transform, Sprite, etc
	{
		//First we get the typeId of this
		std::string type = typeid(*this).name();
		//Then we need to strip "class " from the start of it or it will return "class Componenet"
		std::string prefix = "class ";
		if (type.find(prefix) == 0)  // If "class " is found at the start of the type name
		{
			return type.substr(prefix.size());
		}
		return type;
	};
	
	virtual void Start() = 0;

	virtual void Update(float deltaTime) = 0; //Update is run every frame

	virtual void Render() = 0; //Render is ran every frame after update

	void SetOwner(GameObject* gameObject) //Sets the owner of this component
	{
		this->owner = gameObject;
	}
};

