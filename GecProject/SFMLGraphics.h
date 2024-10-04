#pragma once
#include "IGraphics.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>

class SFMLGraphics : public IGraphics
{
private:
	//Render window
	sf::RenderWindow *renderWindow;

	std::unordered_map<std::string, sf::Texture*> loadedTextures; //Holds all loaded texture pointers with a key to their filenames to delete later
	std::unordered_map<std::string, sf::Sprite*> loadedSprites; // Holds all of the loaded sprites
	//Error Texture
	sf::Texture* errorTexture = new sf::Texture;
	std::string commandLinePrefix = "--SFMLGraphics-- ";
public:
	SFMLGraphics(sf::RenderWindow *newRenderWindow)
	{
		renderWindow = newRenderWindow;
		TryLoadErrorTexture();
	}
	~SFMLGraphics() 
	{
		UnloadAll();
	}
	// Inherited via IGraphics
	bool CreateSprite(std::string& spriteId) override;
	bool RenderSprite(std::string& spriteId, float xPosition, float yPosition, int rows, int frame) override;
public:
	// Inherited via IGraphics
	void TryLoadErrorTexture() override;
	void* TryLoadTextureByFileName(std::string& textureFileName) override;
	void UnloadAll() override;
	void DisplayTextureError(std::string textureName, std::string texturePath);

};

