#pragma once
#include "AABBBoundingBox.h"
#include "GameObject.h"
#include "Physics.hpp"
#include "CollisionSystem.h"
//Scene saves all gameobejcts and handles updating them, and removing them


class Scene 
{
private:
	std::vector<GameObject*> GameObjects; //Vector of all gameobjects in the scene
	CollisionSystem* CollisionsSystem;
	p2d::Physics* Physics;
	bool HasStarted{ false }; 
public:
	Scene()
	{
		Start();
		CollisionsSystem = new CollisionSystem;
		Physics = new p2d::Physics;
	}

	void AddGameObject(GameObject* p_gameObject)
	{
		GameObjects.push_back(p_gameObject);

		//If the game-object has a collider component add it to the collision system
		Collider* collider = p_gameObject->GetComponent<Collider>();
		if(collider != nullptr)
		{
			CollisionsSystem->AddCollider(collider);
			Physics->add(&collider->ColliderBox2);
		}
		if(HasStarted)
		{
			p_gameObject->Start();
		}
	}
	const std::vector<GameObject*>& GetGameObjects()
	{
		return GameObjects;
	}
	void Start()
	{
		for (GameObject* gameObject : GameObjects)
		{
			gameObject->Start();
		}
		HasStarted = true;
	};
	void Update(float p_deltaTime) const
	{
		CollisionsSystem->Update();
		for (GameObject* gameObject : GameObjects)
		{
			gameObject->Update(p_deltaTime);
		}
		Physics->update(p_deltaTime);

	}


	void Render() const
	{
		for (GameObject* gameObject : GameObjects)
		{
			gameObject->Render();
		}
	};	

	void Cleanup() 
	{
		delete CollisionsSystem;
		for (GameObject* gameObject : GameObjects)
		{
			delete gameObject;
		}
		GameObjects.clear();
	};
};

