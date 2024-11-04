#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "EditorGUI.h"
#include "IGraphics.h"
#include "Scene.h"
#include "SFMLGraphics.h"

class Game
{
private:
	//Essential Game Function Variables
	sf::RenderWindow* Window;
	IGraphics* GraphicsHandler;
	EditorGui* DebugGui;
	bool Running{ false };


	//Scene Management
	Scene* CurrentlyLoadedScene{ nullptr };

	//Dt
	sf::Clock DeltaClock;
	sf::Time DeltaTime;

public:
	Game()
	{
		//Load a new empty scene
		CurrentlyLoadedScene = new Scene;

		// Set the game loop to run
		Running = true;
		// Create the render window via sfml
		Window = new sf::RenderWindow(sf::VideoMode(800, 800), "Game Engine");
		// Create the graphics handler (SFML, SDL, etc.)
		GraphicsHandler = new SFMLGraphics(Window);

	#ifndef NDEBUG
		//Create the EditorGui
		DebugGui = new EditorGui(Window, CurrentlyLoadedScene);
	#endif


		Start();
	}
	void Shutdown();

	bool GetRunning() const
	{
		return Running;
	}
private:
	void Start();
	void Loop();
	void HandleEvents();

	void Update();

	void Render() const;


};


