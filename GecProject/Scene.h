#pragma once
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
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Update(deltaTime);
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

