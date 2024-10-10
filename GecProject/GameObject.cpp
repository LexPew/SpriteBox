#include "GameObject.h"
#include "Component.h"
#include <iostream>
//Attaches a new component to the class if it doesnt already exist in the components map.
bool GameObject::AttachComponent(std::shared_ptr<Component> component)
{
	auto attachedComponentToFind = AttachedComponents.find(component->GetType());

	//If we have this already got this component attached then dont add it 
	if (attachedComponentToFind != AttachedComponents.end())
	{
		//std::cout << "Tried to add a component twice on gameobject: " << name;
		return false;
	}
	else //Add the component to the unordermap
	{
		AttachedComponents[component->GetType()] = component;
		component->SetOwner(this);
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
void GameObject::Update(float deltaTime)
{
	//Loop through every component and call the update function
	for (auto i = AttachedComponents.begin(); i != AttachedComponents.end(); i++)
	{
		i->second->Update(deltaTime);
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
