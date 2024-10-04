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
	IGraphics* graphicsHandler{ nullptr };
	std::string name{"Null"}; //This is the name for our game object and will be used in the scene to identify it
	std::unordered_map<std::string, std::shared_ptr<Component>> attachedComponents; //This map holds the components as pointers with their name as the key
public:
	GameObject(std::string gameObjectName, IGraphics* graphicsHandlerInput)
	{
		graphicsHandler = graphicsHandlerInput;
		name = gameObjectName;
		//Attach a transform component by default
		AttachComponent(std::make_shared<TransformComponent>());
	}
	//Attaches a new component to the class if it doesnt already exist in the components map. Returns true/false depending on whether it was succesfull
	bool AttachComponent(std::shared_ptr<Component> component);

	// Returns a component if attached
	template <typename T>
	inline std::shared_ptr<T> GetComponent()
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


	//Game Logic functions

	void Update(float deltaTime);

	void Render();
};
