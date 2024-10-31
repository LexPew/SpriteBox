#pragma once
#include "BoundingBox.h"
#include "GameObject.h"
#include "Physics.h"
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
	void Start() const
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Start();
		}
	};
	void Update(float p_deltaTime) const
	{
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			GameObject* gameObject1 = gameObjects[i];
			Physics* collider1 = gameObject1->GetComponent<Physics>();

			//If game-object doesn't have a box collider skip it
			if (!collider1)
			{
				continue;
			}
			for (size_t j = i + 1; j < gameObjects.size(); j++)
			{

				GameObject* gameObject2 = gameObjects[j];

				Physics* collider2 = gameObject2->GetComponent<Physics>();

				//If game-object doesn't have a box collider skip it
				if (!collider2)
				{
					continue;
				}
				// Check if the colliders are intersecting
				if (collider1->GetBounds().Intersects(collider2->GetBounds()))
				{
					collider1->OnCollide(collider2->GetBounds());
					collider2->OnCollide(collider1->GetBounds());
				}
			}
		 gameObject1->Update(p_deltaTime);
		 }

		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Update(p_deltaTime);
		}
	}


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

