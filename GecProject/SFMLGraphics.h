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
	std::unordered_map<std::string, sf::Sprite*> loadedSprites; // Holds all the loaded sprites
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
	bool CreateSprite(const std::string& p_spriteId) override;
	bool RenderSprite(const Sprite& p_sprite, const float p_xPosition, const float p_yPosition, const int p_frame) override;
public:
	// Inherited via IGraphics
	void TryLoadErrorTexture() override;
	void* TryLoadTextureByFileName(const std::string& p_textureFileName) override;
	void UnloadAll() override;
	void DisplayTextureError(const std::string& p_textureName, const std::string& p_texturePath);

};

