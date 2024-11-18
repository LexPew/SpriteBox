#pragma once
#include "BoundingBox.h"
#include "GameObject.h"
#include "Rigidbody.h"
//Scene saves all gameobejcts and handles updating them, and removing them


class Scene 
{
private:
	std::vector<GameObject*> gameObjects; //Vector of all gameobjects in the scene
	bool HasStarted{ false }; 
public:
	Scene()
	{
		Start();
	}

	void AddGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
		if(HasStarted)
		{
			gameObject->Start();
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
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			GameObject* gameObject1 = gameObjects[i];
			Collider* collider1 = gameObject1->GetComponent<Collider>();

			//If game-object doesn't have a box collider skip it
			if (!collider1)
			{
				continue;
			}
			for (size_t j = i + 1; j < gameObjects.size(); j++)
			{

				GameObject* gameObject2 = gameObjects[j];

				Collider* collider2 = gameObject2->GetComponent<Collider>();

				//If game-object doesn't have a box collider skip it
				if (!collider2)
				{
					continue;
				}
				//Compare their bitmasks to see if they should collide before running intersection
				if(collider1->GetBitMask() & collider2->GetBitMask())
				{
					// Check if the colliders are intersecting
					if (collider1->GetCollisionBounds().Intersects(collider2->GetCollisionBounds()))
					{
						collider1->CheckCollision(*collider2);
						collider2->CheckCollision(*collider1);
					}
				}
	
			}
		 gameObject1->Update(p_deltaTime);
		 }

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
		for (GameObject* gameObject : gameObjects)
		{
			delete gameObject;
		}
		gameObjects.clear();
	};
};

