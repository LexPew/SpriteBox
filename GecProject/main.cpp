/*
    GecProject - For GEC students to use as a base for their projects.
    Already has SFML linked and ImGui set up.
*/
#include "ExternalHeaders.h"
#include "RedirectCout.h"
#include "TextureUtil.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "IGraphics.h"
#include "SFMLGraphics.h"

//GameObject related
#include "GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Scene.h"
#include "EditorGUI.h"
#include "Sprite.h"


//Performance metrics
GameObject* newGameObject;
GameObject* object2;
Scene loadedScene;
GameObject* selectedGameObject{ nullptr };
int main()
{
     //Redirect cout to HAPI
    outbuf ob;

    std::streambuf* sb = std::cout.rdbuf(&ob);

     //Redirect cerr
    outbuferr oberr;
   std::streambuf* sberr = std::cerr.rdbuf(&oberr);

    // Turn on memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "GEC Engine");

    IGraphics* graphicsHandler = new SFMLGraphics(&window);

    Sprite newSprite("Attack.png", 8);
    newGameObject = new GameObject("GameObject1");
    newGameObject->GetComponent<Transform>()->SetPosition(Vector2(10, 10));
    newGameObject->AttachComponent(new SpriteRenderer(newSprite, graphicsHandler));

    object2 = new GameObject("GameObject2");
    object2->SetName("GameObject2");
    object2->GetComponent<Transform>()->SetPosition(Vector2(50, 10));
    object2->AttachComponent(new SpriteRenderer(newSprite, graphicsHandler));



    loadedScene = Scene(graphicsHandler);
    loadedScene.AddGameObject(newGameObject);
    loadedScene.AddGameObject(object2);

    for (int i = 0; i < 10; i++)
    {
        std::string name = "GameObj" + std::to_string(i);
        GameObject* obj = new GameObject(name);
        obj->GetComponent<Transform>()->SetPosition(Vector2(i * 10.0f, i * 10.0f));
        obj->AttachComponent(new SpriteRenderer(newSprite, graphicsHandler));
        loadedScene.AddGameObject((obj));
   }

    EditorGui editorGui(&window, &loadedScene);
    sf::Clock uiDeltaClock;
  


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
        loadedScene.Update(deltaTime.asSeconds());

        //--RENDERING--

        window.clear(); //Clear window before drawing new sprites

        loadedScene.Render();
        editorGui.Render();

        window.display(); //Display all rendered objects
    }

    //std::cout << "Finished!" << std::endl;
    loadedScene.Cleanup();
	ImGui::SFML::Shutdown();
    delete graphicsHandler;

    return 0;
}



