#pragma once
#include "Rect.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "PhysicsEngine.h"
#include "Rigidbody.h"
//Scene saves all gameobejcts and handles updating them, and removing them


class Scene 
{
private:
	//Physics
	PhysicsEngine *PEngine = new PhysicsEngine;

	std::vector<GameObject*> gameObjects; //Vector of all gameobjects in the scene
	bool HasStarted{ false };

public:
	Scene()
	{
		PEngine->SetGravity({ 0,25 });
		Start();
	}

	void AddGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
		if(HasStarted)
		{
			gameObject->Start();
		}
		PhysicsBody* physicsBody = gameObject->GetComponent<PhysicsBody>();
		if(physicsBody != nullptr)
		{
			PEngine->AddRigidbody(physicsBody->PRigidBody);
		}

	}
	const std::vector<GameObject*>& GetGameObjects()
	{
		return gameObjects;
	}
	void Start()
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Start();
		}
		HasStarted = true;
	};
	void Update(float p_deltaTime) const
	{
		PEngine->Update(p_deltaTime);
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Update(p_deltaTime);
		}

	}


	void Render() const
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Render();
		}
	};	

	void Cleanup() 
	{
		delete PEngine;
		for (GameObject* gameObject : gameObjects)
		{
			delete gameObject;
		}
		gameObjects.clear();
	};
};

