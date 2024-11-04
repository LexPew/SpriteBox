#include "Game.h"

#include <imgui-SFML.h>
#include <SFML/Window/Event.hpp>

#include "SpriteRenderer.h"


void Game::Start()
{

    //Free Space


	//Place any essential game related startup functions in here
    CurrentlyLoadedScene->Start();


    for (int i = 0; i < 3; i++)
    {

        std::string name = "GameObj" + std::to_string(i);
        GameObject* obj = new GameObject(name);
        obj->GetComponent<Transform>()->SetPosition(Vector2(i * 500.0f, 0));
        obj->AttachComponent(new SpriteRenderer(Sprite("A.png", 1), GraphicsHandler));
        if (i == 1)
        {
            obj->AttachComponent(new Physics(2));
        }
        else
        {
            obj->AttachComponent(new Physics(1));
        }

        CurrentlyLoadedScene->AddGameObject((obj));
    }


	Loop();
}

void Game::Loop()
{
	while(Running)
	{
		HandleEvents();
		Update();
		Render();
	}
    Shutdown();
}

void Game::HandleEvents()
{

	//--EVENT HANDLING-- 
    sf::Event event;
    while (Running && Window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(*Window, event);

        switch (event.type)
        {
        case sf::Event::Closed:
            Running = false;
            break;

        case sf::Event::LostFocus:
            Window->setFramerateLimit(20);
            break;
        case sf::Event::GainedFocus:
            Window->setFramerateLimit(0);
            break;
        case sf::Event::Resized:
            Window->setSize({ event.size.width, event.size.height });
            sf::View view(sf::FloatRect(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
            Window->setView(view);
            break;
        }
    }

}

void Game::Update()
{
    if (!Running) { return; }
    //Recalculate Deltatime 
    DeltaTime = DeltaClock.restart();

    ImGui::SFML::Update(*Window, DeltaTime);
    DebugGui->Update(DeltaTime.asSeconds());
    CurrentlyLoadedScene->Update(DeltaTime.asSeconds());
}

void Game::Render() const
{
    if (!Running) { return; }
    Window->clear(); //Clear window before drawing new sprites

    CurrentlyLoadedScene->Render();
    DebugGui->Render();

    Window->display(); //Display all rendered objects
}

void Game::Shutdown()
{
    Running = false;
    Window->close();
    CurrentlyLoadedScene->Cleanup();
    delete DebugGui;
    delete GraphicsHandler;
    delete CurrentlyLoadedScene;
    delete Window;
    
}
