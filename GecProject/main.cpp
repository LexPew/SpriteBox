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

void DefineGUI();

//Performance metrics
PerformanceMetrics metrics;
GameObject newGameObject;
GameObject object2;
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "GEC Milestone 1 Example");

    // Set up ImGui (the UI library)
    ImGui::SFML::Init(window);    

    //Init TextureUtils 
    //TextureUtil textureUtils;


    IGraphics* graphicsHandler = new SFMLGraphics(&window);

    //std::string textureName = "Attack.png";

    newGameObject = GameObject("TestObject", graphicsHandler);
    newGameObject.GetComponent<TransformComponent>()->SetPosition(Vector2(10, 10));
    newGameObject.AttachComponent(std::make_shared<SpriteRenderer>("Attack.png", 8, 0));

    object2 = GameObject("TestObject6", graphicsHandler);
    object2.GetComponent<TransformComponent>()->SetPosition(Vector2(50, 10));
    object2.AttachComponent(std::make_shared<SpriteRenderer>("A.png", 1, 0));

    //Animation attackAnimation;
    //animation = Animation(static_cast<sf::Texture*>(graphicsHandler->TryLoadTextureByFileName(textureName)), &sprite, 8);
    // Clock required by the UI
    sf::Clock uiDeltaClock;
  


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }        
        sf::Time deltaTime = uiDeltaClock.restart();

        metrics.Update(deltaTime.asSeconds());
        // ImGui must be updated each frame
        ImGui::SFML::Update(window, deltaTime);
        newGameObject.Update(deltaTime.asSeconds());
        object2.Update(deltaTime.asSeconds());
        // The UI gets defined each time
        DefineGUI();

        // Clear the window
        window.clear();
       
        // Draw the shape
        //window.draw(sprite);
        //graphicsHandler->RenderSprite(0,10,10);
                 newGameObject.Render();
                 object2.Render();
        // UI needs drawing last
        ImGui::SFML::Render(window);

        window.display();
    }

    //std::cout << "Finished!" << std::endl;

	ImGui::SFML::Shutdown();
    delete graphicsHandler;
    return 0;
}

// Use IMGUI for a simple on screen GUI
void DefineGUI()
{
    // Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("Animation Test and Performance Metrics");				// Create a window called "3GP" and append into it.

    //ImGui::Text("Some Text.");	      	// Display some text (you can use a format strings too)	

    //ImGui::Button("Button");			// Buttons return true when clicked (most widgets return true when edited/activated)
    
 //   ImGui::Checkbox("Wireframe", &m_wireframe);	// A checkbox linked to a member variable

  //  ImGui::Checkbox("Cull Face", &m_cullFace);
    static float xPosition{ 10 };
    if (ImGui::SliderFloat("XPosition", &xPosition, 0.f, 1000.f)) {
        newGameObject.GetComponent<TransformComponent>()->SetPosition(Vector2(xPosition, 10));
    }
    static float animationSpeed{ 1 };
    if(ImGui::SliderFloat("Speed", &animationSpeed, 0.f, 5.0f))
    {
        newGameObject.GetComponent<SpriteRenderer>()->SetSpeed(animationSpeed);
    }// Slider from 0.0 to 1.0
    static float fpsSmoothingFactor{ 0 };

    if (ImGui::SliderFloat("FPS Smoothing Factor", &fpsSmoothingFactor, 0.1f, .9f))
    {
        metrics.SetSmoothingFactor(fpsSmoothingFactor);
    }// Slider from 0.0 to 1.0

    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("Application average %.3f ms/frame (%.f FPS)", 1000.0f / ImGui::GetIO().Framerate, metrics.GetAveragedFrameRate());

    ImGui::PlotLines("Frame Rate Graph", metrics.framesPerSecondSamples, metrics.GetMaxSamples());

    ImGui::End();
}
