#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
class TextureUtil
{
	//Call function to load texture from file path and return pointer with that texture, need to handle when we cant grab a texture file
	//and assign a different error texture

	//Unload function to unload a texture and delete the pointer
	//Delete all function to 
private:

	//Texture Handling
	std::string defaultWorkingPath = "Data/Textures/";	//This is the default directory for textures (Set to the data and textures folder)	
	std::unordered_map<std::string, sf::Texture*> loadedTextures; //Holds all loaded texture pointers with a key to their filenames to delete later
	//Error Handling
	sf::Texture* errorTexture = new sf::Texture;
	std::string errorTextureFileName = "Error.png";

public:

	//Constructor assigns the error texture
	TextureUtil() 
	{
		loadedTextures[errorTextureFileName] = errorTexture;
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
		//Check if we already have the texture loaded
		auto textureMapTexture = loadedTextures.find(textureFileName);

		if (textureMapTexture != loadedTextures.end())
		{
			std::cout << "TextureUtils: Attempted to load same texture twice : " + defaultWorkingPath + textureFileName;

			return textureMapTexture->second;
		}

		//Create a new texture pointer to hold the texture
		sf::Texture* textureToLoad = new sf::Texture;

		//Try load from the file path
		if (textureToLoad->loadFromFile(defaultWorkingPath + textureFileName))
		{
			//Succesfully loaded texture 
			loadedTextures[textureFileName] = textureToLoad;
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
		//Delete all the second values (pointers) from loaded textures map
		for (auto& pair : loadedTextures)
		{
			delete pair.second;
		}
		//Clear the map
		loadedTextures.clear();
	}
};

