#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class TextureUtil
{
	//Call function to load texture from file path and return pointer with that texture, need to handle when we cant grab a texture file
	//and assign a different error texture

	//Unload function to unload a texture and delete the pointer
	//Delete all function to 
private:

	//Texture Handling
	std::string defaultWorkingPath = "Data/Textures/";	//This is the default directory for textures (Set to the data and textures folder)
	std::vector<sf::Texture*> loadedTextures;	//Holds all loaded texture pointer to delete later
	
	//Error Handling
	sf::Texture* errorTexture = new sf::Texture;
	std::string errorTextureFileName = "Error.png";

public:

	//Constructor assigns the error texture
	TextureUtil() 
	{
		loadedTextures.push_back(errorTexture);
		if (!errorTexture->loadFromFile(defaultWorkingPath + errorTextureFileName))
		{
			//This will result in instead of an error texture just the default shape colour being displayed
			std::cout << "TextureUtils: Failed to load error texture!";
		}
	}

	//Deconstructor unloads all textures
	~TextureUtil()
	{
		UnloadAll();
	}

	//Loads a texture by its filename in the defaultWorkingPath
	const sf::Texture* LoadTextureByName(const std::string& textureFileName)
	{
		//Create a new texture pointer to hold the texture
		sf::Texture* textureToLoad = new sf::Texture;
		//Try load from the file path
		if (textureToLoad->loadFromFile(defaultWorkingPath + textureFileName))
		{
			//Succesfully loaded texture 
			loadedTextures.push_back(textureToLoad);
			return textureToLoad;
		}
		else
		{
			//Delete the pointer as we wont need it
			delete textureToLoad;
			//Output an error with the file path for easier debugging
			std::cout << "TextureUtils: Failed to load texture : " + defaultWorkingPath + textureFileName;
			//Return the default error texture
			return errorTexture;

		}
		

	}
	//Loops through each held pointer in loadedTextures and deletes them
	void UnloadAll()
	{
		sf::Texture* textureToUnload;
		for (int i = 0; i < loadedTextures.size(); i++) 
		{
			delete loadedTextures[i];
		}
		loadedTextures.clear();
	}
};

