#include "EditorGUI.h"

#include "Sprite.h"
#include "SpriteRenderer.h"

void EditorGui::Update()
{

	//Render our Editor Tools window, this is where all other menus will be accessed from via buttons
	ImGui::Begin("Editor Tools");

	if (ImGui::Button("Scene Hierarchy"))
	{
		DisplaySceneHierarchy = !DisplaySceneHierarchy;

	}
	DisplaySceneHierarchyGui();

	ImGui::End();
}


void EditorGui::Render() const
{
	ImGui::SFML::Render(*RenderWindow);
}


void EditorGui::DisplaySceneHierarchyGui()
{
	if (DisplaySceneHierarchy)
	{
		//Create a new GUI window named Scene Hierarchy to hold our listbox element
		ImGui::Begin("Scene Hierarchy");

		if (ImGui::BeginListBox("GameObjects"))
		{

			//Loop through each game-object in the currently loaded scene and make a selectable
			for (GameObject* gameObject : CurrentlyLoadedScene->GetGameObjects())
			{
				ImGui::Bullet();
				if (ImGui::Selectable(gameObject->GetName().c_str()))
				{
					//We have clicked on this game-object
					CurrentlySelectedGameObject = gameObject;
					DisplayPropertiesWindow = true;

				}

			}
			ImGui::EndListBox();
		}
		DisplayPropertiesGui();
		ImGui::End();
	}
}

void EditorGui::DisplayPropertiesGui() const
{
	//Make sure we have a game-object selected otherwise it will cause an error
	if (DisplayPropertiesWindow && CurrentlySelectedGameObject != nullptr)
	{
		//Create it as a child of scene heir so it displays inside its window
		if (ImGui::BeginChild("SceneHierarchy"))
		{
			if (ImGui::CollapsingHeader((CurrentlySelectedGameObject->GetName() + " properties").c_str()))
			{
				//List each component
				for (const auto& component : CurrentlySelectedGameObject->GetComponents())
				{
					Component* comp = component.second;
					std::string type = component.second->GetType();
					//ImGui::Text(component.second->GetType().c_str());
					ImGui::PushStyleColor(ImGuiCol_Text, TEAL_GREEN);
					if (ImGui::CollapsingHeader(component.second->GetType().c_str()))
					{
						ImGui::PushStyleColor(ImGuiCol_Text, WHITE);
						if (type == "TransformComponent")
						{
							//Const as we are just grabbing xPos and yPos then assigning them to editable integers
							TransformComponent* transformComp = dynamic_cast<TransformComponent*>(comp);
							const float xPosition = transformComp->GetPosition().x;
							const float yPosition = transformComp->GetPosition().y;

							float xEditable = xPosition;
							float yEditable = yPosition;

							ImGui::Text("Position: ");
							ImGui::DragFloat("X: ", &xEditable);
							ImGui::DragFloat("Y: ", &yEditable);

							transformComp->SetPosition(Vector2(xEditable, yEditable));
						}
						else if (type == "SpriteRenderer")
						{
							SpriteRenderer* spriteComp = dynamic_cast<SpriteRenderer*>(comp);
							ImGui::Text("SpriteID: %s", spriteComp->GetSpriteID().c_str());
							bool playState = spriteComp->GetPlayState();
							if (ImGui::Checkbox("Playing", &playState))
							{
								spriteComp->SetPlayState(playState);
							}
							float animationMultiplierSpeed = spriteComp->GetSpeed();
							if (ImGui::SliderFloat("Animation Speed", &animationMultiplierSpeed, 0, 5))
							{
								spriteComp->SetSpeed(animationMultiplierSpeed);
							}
						}
						ImGui::PopStyleColor();

						ImGui::PushStyleColor(ImGuiCol_Text, RED);


						ImGui::PopStyleColor();
					}
					ImGui::PopStyleColor();
				}
			}

			ImGui::EndChild();
		}
	}
}
