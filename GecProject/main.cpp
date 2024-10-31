/*
    GecProject - For GEC students to use as a base for their projects.
    Already has SFML linked and ImGui set up.
*/
#include "ExternalHeaders.h"
#include "RedirectCout.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFMLGraphics.h"

//GameObject related
#include "BoundingBox.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Scene.h"
#include "EditorGUI.h"
#include "Physics.h"
#include "Sprite.h"


Scene* currentlyLoadedScene;

int main()
{

    //--Debug Section--

	//Redirect cout to HAPI
    outbuf ob;

    std::streambuf* sb = std::cout.rdbuf(&ob);

	//Redirect cerr
    outbuferr oberr;
   std::streambuf* sberr = std::cerr.rdbuf(&oberr);

    // Turn on memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //---END---



    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "GEC Engine");
    // Create the graphics handler (SFML, SDL, etc.)
    IGraphics* graphicsHandler = new SFMLGraphics(&window);


    //Create a starting scene and populate it with some game-objects with sprites
    currentlyLoadedScene = new Scene(graphicsHandler);
    //Sprite newSprite("Attack.png", 8, { 432,512 });
    
    for (int i = 0; i < 2; i++)
    {
        std::string name = "GameObj" + std::to_string(i);
        GameObject* obj = new GameObject(name);
        obj->GetComponent<Transform>()->SetPosition(Vector2(i * 500.0f, 0));
        obj->AttachComponent(new SpriteRenderer(Sprite("A.png", 1), graphicsHandler));
        obj->AttachComponent(new Physics());
        currentlyLoadedScene->AddGameObject((obj));
    }
	EditorGui editorGui(&window, currentlyLoadedScene);
    sf::Clock uiDeltaClock;
  
    currentlyLoadedScene->Start();

    while (window.isOpen())
    {
        //--EVENT HANDLING-- 
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::LostFocus:
                window.setFramerateLimit(20);
                break;
            case sf::Event::GainedFocus:
                window.setFramerateLimit(0);
                break;
            case sf::Event::Resized:
                window.setSize({ event.size.width, event.size.height });
                sf::View view(sf::FloatRect(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
                window.setView(view);
                break;
            }
        }

        //--UPDATE--

        sf::Time deltaTime = uiDeltaClock.restart(); //Calculates deltaTime aka time between last frame and this frame

        
        ImGui::SFML::Update(window, deltaTime);
        editorGui.Update(deltaTime.asSeconds());
        currentlyLoadedScene->Update(deltaTime.asSeconds());

        //--RENDERING--

        window.clear(); //Clear window before drawing new sprites

        currentlyLoadedScene->Render();
        editorGui.Render();

        window.display(); //Display all rendered objects
    }

    //std::cout << "Finished!" << std::endl;
    currentlyLoadedScene->Cleanup();
	ImGui::SFML::Shutdown();
    delete graphicsHandler;
    delete currentlyLoadedScene;

    return 0;
}



