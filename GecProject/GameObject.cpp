#include "GameObject.h"
#include "Component.h"
#include <iostream>
//Attaches a new component to the class if it doesnt already exist in the components map.
bool GameObject::AttachComponent(std::shared_ptr<Component> component)
{
	auto attachedComponentToFind = attachedComponents.find(component->GetType());

	//If we have this already got this component attached then dont add it 
	if (attachedComponentToFind != attachedComponents.end())
	{
		//std::cout << "Tried to add a component twice on gameobject: " << name;
		return false;
	}
	else //Add the component to the unordermap
	{
		attachedComponents[component->GetType()] = component;
		component->SetOwner(this);
	}
	
}
/*/Returns a component if attached
std::shared_ptr<Component> GameObject::GetComponent(std::string component)
{
	auto attachedComponentToFind = attachedComponents.find(component);

	//If we have this already got this component attached then dont add it 
	if (attachedComponentToFind == attachedComponents.end())
	{
		return attachedComponents[component];
	}
	else
	{
		return nullptr;
	}
}*/
//Runs the update function on each attached component.
void GameObject::Update(float deltaTime)
{
	//Loop through every component and call the update function
	for (auto i = attachedComponents.begin(); i != attachedComponents.end(); i++)
	{
		i->second->Update(deltaTime);
	}
}
//Runs the render function on each attached component("Used for things like sprites")
void GameObject::Render()
{	
	//Loop through every component and call the Render function
	for (auto i = attachedComponents.begin(); i != attachedComponents.end(); i++)
	{
		i->second->Render(*graphicsHandler);
	} 
}
