#pragma once
#include "ExternalHeaders.h"
#include "GameObject.h"
#include "Scene.h"
#include "PerformanceMetrics.h"
class EditorGui
{
private:
	/**
	 * Pointer to our current render window which we use when drawing ImGui
	 */
	sf::RenderWindow* RenderWindow{nullptr};

	/**
	* Pointer to the currently loaded scene, this is used to grab the game-objects
	*/
	Scene* CurrentlyLoadedScene{nullptr};

	/**
	 * Pointer to the current game-object selected via ImGui
	 */
	GameObject* CurrentlySelectedGameObject{ nullptr };

	/**
	 * Pointer to the performance metrics object
	 */
	PerformanceMetrics* Metrics{ nullptr };
	/**
	 * Predefined colours used for ImGui
	 */
	#define WHITE IM_COL32(255, 255, 255,255)
	#define TEAL_GREEN IM_COL32(75, 202, 147,255)
	#define RED IM_COL32(230, 85, 85,255)


	bool DisplayPropertiesWindow{ false };
	bool DisplaySceneHierarchy{ false };
	bool DisplayPerformanceMetrics{ false };

public:

	/**
	 * Default constructor for use with copy assign later on, gui will not work otherwise as the CurrentlyLoadedScene and RenderWindow need to be assigned
	 */
	EditorGui() = default;

	/**
	 * 
	 * @param p_renderWindow			Pointer to the current SFML rendering window which will be used to draw ImGui gui's 
	 * @param p_currentlyLoadedScene	Pointer to the currently loaded scene which will be used to gather info from such as game-objects
	 */
	EditorGui(sf::RenderWindow* p_renderWindow, Scene* p_currentlyLoadedScene)
	{
		//Assign both the render window and the currently loaded scene
		RenderWindow = p_renderWindow;
		CurrentlyLoadedScene = p_currentlyLoadedScene;
		Metrics = new PerformanceMetrics;
		//Initialize ImGui for SFML
		ImGui::SFML::Init(*RenderWindow);
	}

	/**
	 * Cleans up any pointers and deletes memory
	 */
	~EditorGui()
	{
		delete Metrics;
	}


	/**
	 * Ran before render() to update or grab any properties from the scene to use when displaying a gui
	 */
	void Update(const float p_deltaTime);
	/**
	 * Renders all ImGui windows, called after the update function
	*/
	void Render() const;
private:
	/**
	 * Displays all the game-objects in the current scene in a ImGui::Listbox and makes them selectable
	 */
	void DisplaySceneHierarchyGui();

	/**
	 * Displays the components of the CurrentlySelectedGameObject and their respective properties such as X,Y position
	 */
	void DisplayPropertiesGui() const;

	void DisplayPerformanceMetricsGui(const float p_deltaTime) const;
};

