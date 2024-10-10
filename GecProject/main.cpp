/*
    GecProject - For GEC students to use as a base for their projects.
    Already has SFML linked and ImGui set up.
*/
#include "ExternalHeaders.h"
#include "RedirectCout.h"
#include "TextureUtil.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "PerformanceMetrics.h"
#include "IGraphics.h"
#include "SFMLGraphics.h"

//GameObject related
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "Scene.h"
#include "EditorGUI.h"



//Performance metrics
PerformanceMetrics metrics;
GameObject newGameObject;
GameObject object2;
Scene loadedScene;
GameObject* selectedGameObject{ nullptr };
int main()
{
    // Redirect cout to HAPI
    outbuf ob;
    std::streambuf* sb = std::cout.rdbuf(&ob);

    // Redirect cerr
    outbuferr oberr;
    std::streambuf* sberr = std::cerr.rdbuf(&oberr);

    // Turn on memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "GEC Engine");

    srand(time(nullptr));

    IGraphics* graphicsHandler = new SFMLGraphics(&window);

    //std::string textureName = "Attack.png";

    newGameObject = GameObject("Retest");

    newGameObject.GetComponent<TransformComponent>()->SetPosition(Vector2(10, 10));
    newGameObject.AttachComponent(std::make_shared<SpriteRenderer>("Attack.png", 8, 0, *graphicsHandler));

    object2 = GameObject("TestObject6");
    object2.GetComponent<TransformComponent>()->SetPosition(Vector2(50, 10));
    object2.AttachComponent(std::make_shared<SpriteRenderer>("A.png", 1, 0, *graphicsHandler));
    std::cout << "TYPE TEST: " << typeid(*object2.GetComponent<TransformComponent>()).name() << "\n";
    loadedScene = Scene(graphicsHandler);
    loadedScene.AddGameObject(&newGameObject);
    loadedScene.AddGameObject(&object2);
    EditorGUI editorGui(window, loadedScene);
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
            case sf::Event::Resized:
                window.setSize({ event.size.width, event.size.height });
            default:
                break;
            }
        }

        //--UPDATE--

        sf::Time deltaTime = uiDeltaClock.restart(); //Calculates deltaTime aka time between last frame and this frame

        metrics.Update(deltaTime.asSeconds());
        ImGui::SFML::Update(window, deltaTime);
        editorGui.Update();
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



