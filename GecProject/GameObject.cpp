#include "GameObject.h"
#include "Component.h"
#include <iostream>

const std::unordered_map<std::string, Component*>& GameObject::GetComponents() const
{
	return AttachedComponents;
}

//Attaches a new component to the class if it doesnt already exist in the components map.
bool GameObject::AttachComponent(Component* p_component)
{
	auto attachedComponentToFind = AttachedComponents.find(p_component->GetType());

	//If we have this already got this component attached then dont add it 
	if (attachedComponentToFind != AttachedComponents.end())
	{
		//std::cout << "Tried to add a component twice on gameobject: " << name;
		return false;
	}
	else //Add the component to the unordermap
	{
		AttachedComponents[p_component->GetType()] = p_component;
		p_component->SetOwner(this);
		return true;
	}


}

void GameObject::RemoveComponent(const std::string& p_componentType)
{
	auto attachedComponentToFind = AttachedComponents.find(p_componentType);

	//If we have  got this component attached then delete it
	if (attachedComponentToFind != AttachedComponents.end())
	{
		std::cout << "Deleting component";
		AttachedComponents.erase(attachedComponentToFind->first);
		std::cout << "Deleted component";
	}
		
}

void GameObject::Start()
{
	//Loop through every component and call the start function
	for (auto i = AttachedComponents.begin(); i != AttachedComponents.end(); i++)
	{
		i->second->Start();
	}
}
//Runs the update function on each attached component.
void GameObject::Update(float p_deltaTime)
{
	//Loop through every component and call the update function
	for (auto i = AttachedComponents.begin(); i != AttachedComponents.end(); i++)
	{
		i->second->Update(p_deltaTime);
	}
}
//Runs the render function on each attached component("Used for things like sprites")
void GameObject::Render()
{	
	//Loop through every component and call the Render function
	for (auto i = AttachedComponents.begin(); i != AttachedComponents.end(); i++)
	{
		i->second->Render();
	} 
}
