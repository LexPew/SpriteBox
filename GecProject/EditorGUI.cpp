#include "EditorGUI.h"
#include "SpriteRenderer.h"

void EditorGUI::Update()
{

	//Render our Editor Tools window, this is where all other menus will be accessed from via buttons
	ImGui::Begin("Editor Tools");
	if (currentlySelectedGameObject != nullptr)
	{
		ImGui::Text(currentlySelectedGameObject->GetName().c_str());
	}

	if (ImGui::Button("Scene Heirarchy"))
	{
		displaySceneHeirarchy = !displaySceneHeirarchy;

	}
	DiplaySceneHeirarchyGUI();

	ImGui::End();
}

void EditorGUI::Render()
{
	ImGui::SFML::Render(renderWindow);
}

//Lists all gameobjects in the scene and makes them selectable
void EditorGUI::DiplaySceneHeirarchyGUI()
{
	if (displaySceneHeirarchy)
	{
		//Create a new GUI window named Scene Heirarchy to hold our listbox element
		ImGui::Begin("Scene Heirarchy");

		if (ImGui::BeginListBox("GameObjects"))
		{

			//Loop through each gameobject in the currently loaded scene and make a selectable
			for (GameObject* gameObject : currentlyLoadedScene.GetGameObjects())
			{
				ImGui::Bullet();
				if (ImGui::Selectable(gameObject->GetName().c_str()))
				{
					//We have clicked on this gameobject
					currentlySelectedGameObject = gameObject;
					displayPropertiesWindow = true;

				}

			}
			ImGui::EndListBox();
		}
		DisplayPropertiesGUI();
		ImGui::End();
	}
}
//This will display the objects properties in a neat header below the scene heirarchy list
void EditorGUI::DisplayPropertiesGUI()
{
	//Make sure we have a gameobject selected otherwise it will cause an error
	if (displayPropertiesWindow && currentlySelectedGameObject != nullptr)
	{
		//Create it as a child of scene heir so it displays inside its window
		if (ImGui::BeginChild("SceneHeirarchy"))
		{
			if (ImGui::CollapsingHeader((currentlySelectedGameObject->GetName() + " properties").c_str()))
			{
				//List each components
				for (auto component : currentlySelectedGameObject->GetComponents())
				{
					std::shared_ptr<Component>& comp = component.second;
					std::string type = component.second->GetType();
					//ImGui::Text(component.second->GetType().c_str());
					ImGui::PushStyleColor(ImGuiCol_Text, TealGreen);
					if (ImGui::CollapsingHeader(component.second->GetType().c_str()))
					{
						ImGui::PushStyleColor(ImGuiCol_Text, White);
						if (type == "TransformComponent")
						{
							std::shared_ptr<TransformComponent> transformComp = std::dynamic_pointer_cast<TransformComponent>(comp);
							float xPosition = transformComp->GetPosition().x;
							float yPosition = transformComp->GetPosition().y;

							float xEditable = xPosition;
							float yEditable = yPosition;

							ImGui::Text("Position: ");
							ImGui::DragFloat("X: ", &xEditable);
							ImGui::DragFloat("Y: ", &yEditable);

							transformComp->SetPosition(Vector2(xEditable, yEditable));
						}
						else if (type == "SpriteRenderer")
						{
							std::shared_ptr<SpriteRenderer> spriteComp = std::dynamic_pointer_cast<SpriteRenderer>(comp);
							ImGui::Text(("Sprite ID: " + spriteComp->GetSpriteID()).c_str());
							bool playState = spriteComp->GetPlayState();
							if (ImGui::Checkbox("Playing", &playState))
							{
								spriteComp->SetPlayState(playState);
							}
							float animationMultiplierSpeed = spriteComp->GetSpeed();
							if (ImGui::SliderFloat("Animation Spped", &animationMultiplierSpeed, 0, 5))
							{
								spriteComp->SetSpeed(animationMultiplierSpeed);
							}
						}
						ImGui::PopStyleColor();
					}
					ImGui::PopStyleColor();
					//Display each component by name

				}
			}

			ImGui::EndChild();
		}


	}
}
