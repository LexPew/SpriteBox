#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "TransformComponent.h"

//Forward declaration
class Component;

class GameObject
{
private:
	std::string gameObjectName{"GameObject"}; //This is the gameobjects name and will be used to identify it, e.g for a scene search "Null" would return this
	std::unordered_map<std::string, std::shared_ptr<Component>> attachedComponents; //Attached components holds all current components associated with this gameobject, by their string name and a shared ptr
public:
	//Constructors (Gameobjects are assigned a transform component by default
	GameObject()
	{
		AttachComponent(std::make_shared<TransformComponent>());
	};
	GameObject(std::string _gameObjectName)
	{
		gameObjectName = _gameObjectName;

		AttachComponent(std::make_shared<TransformComponent>());
	}

	//Tries to attach a component, returns bool whether succesfull
	bool AttachComponent(std::shared_ptr<Component> component);
	const std::string& GetName()
	{
		return gameObjectName;
	}
	//Returns a component T if the search was succesfull
	template <typename T> inline
	std::shared_ptr<T> GetComponent()
	{
		std::shared_ptr<T> result = nullptr;
		for (const auto& pair : attachedComponents)
		{
			result = std::dynamic_pointer_cast<T>(pair.second); // Using dynamic_pointer_cast for shared pointers
			if (result)
			{
				break;
			}
		}
		return result;
	}

	// Get all components (returns by reference)
	const std::unordered_map<std::string, std::shared_ptr<Component>>& GetComponents() const
	{
		return attachedComponents;
	}

	//Game logic funcs
	void Start();

	void Update(float deltaTime);//Update is run every frame

	void Render();  //Render is ran every frame after update
};
