#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "TransformComponent.h"
#include "iostream"

//Forward declaration
class Component;

class GameObject
{
private:
	std::string GameObjectName{"GameObject"}; //This is the game-objects name and will be used to identify it, e.g for a scene search "Null" would return this
	std::unordered_map<std::string, std::shared_ptr<Component>> AttachedComponents; //Attached components holds all current components associated with this gameobject, by their string name and a shared ptr
public:
	//Constructors (Game-objects are assigned a transform component by default
	GameObject()
	{
		AttachComponent(std::make_shared<TransformComponent>());
	};
	GameObject(std::string _gameObjectName)
	{
		GameObjectName = _gameObjectName;

		AttachComponent(std::make_shared<TransformComponent>());
	}

	//Tries to attach a component, returns bool whether succesfull
	bool AttachComponent(std::shared_ptr<Component> component);

 
	void RemoveComponent(std::string componentName)
	{
		auto attachedComponentToFind = AttachedComponents.find(componentName);

		//If we have  got this component attached then delete it
		if (attachedComponentToFind != AttachedComponents.end())
		{
			std::cout << "Deleting component";
			AttachedComponents.erase(attachedComponentToFind->first);
			std::cout << "Deleted component";
		}
		
	}

	const std::string& GetName()
	{
		return GameObjectName;
	}
	//Returns a component T if the search was succesfull
	template <typename T> inline
	std::shared_ptr<T> GetComponent()
	{
		std::shared_ptr<T> result = nullptr;
		for (const auto& pair : AttachedComponents)
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
		return AttachedComponents;
	}

	//Game logic funcs
	void Start();

	void Update(float deltaTime);//Update is run every frame

	void Render();  //Render is ran every frame after update
};
