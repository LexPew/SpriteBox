#pragma once
#include "ExternalHeaders.h"
#include "GameObject.h"
#include "Scene.h"

class EditorGUI
{
private:
	sf::RenderWindow& renderWindow;

	//Gameobject variables
	GameObject* currentlySelectedGameObject{ nullptr }; //This holds a reference to our currently selected gameobject, useful for displaying its properties / editing them
	
	//Colours
	#define White IM_COL32(255, 255, 255,255)
	#define TealGreen IM_COL32(75, 202, 147,255)
	#define Red IM_COL32(230, 85, 85,255)

	//Window Bools
	bool displayPropertiesWindow{ false };
	bool displaySceneHeirarchy{ false };


	//Loaded Scene Reference, used for scene heirarchy
	Scene& currentlyLoadedScene;
public:
	EditorGUI(sf::RenderWindow& _renderWindow, Scene& _currentlyLoadedScene) : renderWindow(_renderWindow), currentlyLoadedScene(_currentlyLoadedScene)
	{
		// Set up ImGui (the UI library)
		ImGui::SFML::Init(renderWindow);
	};

	void Update();
	void Render();
private:
	void DiplaySceneHeirarchyGUI();
	void DisplayPropertiesGUI();
};

