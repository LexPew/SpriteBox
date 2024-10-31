#pragma once
#include <string>
#include <typeinfo>

class GameObject;

class Component
{
protected:
	/**
	 * Pointer to the Game-object that owns this component
	 */
	GameObject* Owner{ nullptr };

public:

	virtual ~Component() = default;

	/**
	 * @return Type of component as a string
	 */
	std::string GetType() //Returns the identifier for this component, e.g. Transform, Sprite, etc
	{
		//First we get the typeId of this
		std::string type = typeid(*this).name();
		//Then we need to strip "class " from the start of it, or it will return "class Component"
		std::string prefix = "class ";
		if (type.find(prefix) == 0) // If "class " is found at the start of the type name
		{
			std::string name = type.substr((prefix.size()));
			return name;
		}
		return type;
	}

	/**
	 * Sets the game-object owner of this component
	 * @param p_gameObject Game-object that owns this component
	 */
	void SetOwner(GameObject* p_gameObject)
	{
		this->Owner = p_gameObject;
	}

	/**
	 * Called once at the start of the game-objects life
	 */
	virtual void Start() {}

	/**
	* Updates this game-object and all attached components
	* @param p_deltaTime Time between last frame update and current frame update
	*/
	virtual void Update(const float p_deltaTime) {}

	/**
	* Render is ran every frame
	*/
	virtual void Render() {}
};
