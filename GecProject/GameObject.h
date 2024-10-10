#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "Transform.h"
#include "iostream"

class Component;

class GameObject
{
private:
	/**
	 * This acts as the game-objects identifier and name
	 */
	std::string GameObjectName{"GameObject"};

	/**
	 * Unordered map that holds all the currently attached components to this game-object via their type, and a ptr
	 */
	std::unordered_map<std::string, Component*> AttachedComponents;

public:

	/**
	 * Creates a new game-object with the default name "GameObject" and attaches a Transform component
	 */
	GameObject()
	{
		AttachComponent(new Transform);
	}

	/**
	 * Creates a new game-object with the chosen name and attaches a Transform component
	 * @param p_gameObjectName The name of this new game-object
	 */
	explicit GameObject(const std::string& p_gameObjectName)
	{
		GameObjectName = p_gameObjectName;

		AttachComponent(new Transform);
	}

	/**
	 * Runs the cleanup function to delete all component pointers and clear the AttachedComponents map
	 */
	~GameObject()
	{
		Cleanup();
	}

	void SetName(const std::string& p_gameObjectName)
	{
		GameObjectName = p_gameObjectName;
	}
	/**
	 * @return Game-object's name
	 */
	const std::string& GetName()
	{
		return GameObjectName;
	}

	/**
	 * @return Constant reference to AttachedComponents on this game-object
	 */
	const std::unordered_map<std::string, Component*>& GetComponents() const;

	/**
	 * Tries to attach p_component will return a bool depending on the result
	 * @param p_component The given component to be attached to this game-object
	 * @return True or false depending on whether the game-object could be attached or not
	 */
	bool AttachComponent(Component* p_component);
 
	/**
	 * Removes a component via its type, use GetType() to receive the type from a component
	 * @param p_componentType This is the type of component to remove
	 */
	void RemoveComponent(const std::string& p_componentType);

	/**
	 * Attempts to retrieve a component based on the input type
	 * @tparam T Type of component to retrieve
	 * @return Component or nullptr
	 */
	template <typename T> inline
	T* GetComponent()
	{
		T* result = nullptr;
		for (const auto& pair : AttachedComponents)
		{
			result = dynamic_cast<T*>(pair.second);
			if (result)
			{
				break;
			}
		}
		return result;
	}



	/**
	 * Called once at the start of the game-objects life
	 */
	void Start();

	/**
	 * Updates this game-object and all attached components
	 * @param p_deltaTime Time between last frame update and current frame update
	 */
	void Update(const float p_deltaTime);


	/**
	 * Renders all render based components
	 */
	void Render();

private:
	/**
	 * Deletes all component pointers in AttachedComponents and cleans up
	 */
	void Cleanup()
	{
		for (const auto& pair : AttachedComponents)
		{
			delete pair.second;
		}
		AttachedComponents.clear();

	}
};
