#pragma once
#include "BoundingBox.h"
#include "BoxCollider.h"
#include "GameObject.h"
//Scene saves all gameobejcts and handles updating them, and removing them
class IGraphics;

class Scene 
{
private:
	IGraphics* graphicsHandler; //Passed to certain rendering components
	std::vector<GameObject*> gameObjects; //Vector of all gameobjects in the scene
public:
	Scene()
	{
		graphicsHandler = nullptr;
	}
	Scene(IGraphics* _graphicsHandler)
	{
		graphicsHandler = _graphicsHandler;
		Start();
	}
	void AddGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
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
	};
	void Update(float deltaTime) 
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			GameObject* gameObject1 = gameObjects[i];
			const BoxCollider* collider1 = gameObject1->GetComponent<BoxCollider>();

			//If game-object doesn't have a box collider skip it
			if (!collider1)
			{
				continue;
			}
			for (int j = i + 1; j < gameObjects.size(); j++)
			{

				GameObject* gameObject2 = gameObjects[j];

				const BoxCollider* collider2 = gameObject2->GetComponent<BoxCollider>();

				//If game-object doesn't have a box collider skip it
				if (!collider2)
				{
					continue;
				}
				// Check if the colliders are intersecting
				if (collider1->ColliderBox.Intersects(collider2->ColliderBox))
				{

				}
			}

			gameObject1->Update(deltaTime);
		}
	};
	void Render() 
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Render();
		}
	};	

	void Cleanup() 
	{
		for (GameObject* gameObject : gameObjects)
		{
			delete gameObject;
		}
		gameObjects.clear();
	};
};

