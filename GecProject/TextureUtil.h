#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <Windows.h>
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
	std::string commandLinePrefix = "--TextureUtils-- ";

public:

	//Constructor assigns the error texture
	TextureUtil() 
	{
		loadedTextures[errorTextureFileName] = errorTexture;
		if (!errorTexture->loadFromFile(defaultWorkingPath + errorTextureFileName))
		{
			//If we fail to load the default error texture generate one from code and output an error message, if we fail tell user to reinstall files as something is very wrong if we fail all checks
			sf::Image generatedErrorImage;
			generatedErrorImage.create(100, 100, sf::Color(128, 0, 128, 255));
			if (!errorTexture->loadFromImage(generatedErrorImage))
			{
				std::cout << commandLinePrefix << "Failed to generate error texture, something is very wrong :(";
				MessageBoxA(nullptr, "!Please reinstall game files!", "ERROR--ERROR--ERROR", MB_ICONERROR);
			}



			std::cout << commandLinePrefix << "Failed to load error texture!\n";
			DisplayTextureError(errorTextureFileName, defaultWorkingPath);
		}
	}

	//Deconstructor unloads all textures
	~TextureUtil()
	{
		UnloadAll();
	}

	//Loads a texture by its filename in the defaultWorkingPath
	sf::Texture* LoadTextureByName(const std::string& textureFileName)
	{
		//Check if we already have the texture loaded
		auto textureMapTexture = loadedTextures.find(textureFileName);

		if (textureMapTexture != loadedTextures.end())
		{
			std::cout << commandLinePrefix << "Attempted to load same texture twice : " + defaultWorkingPath + textureFileName << "\n";

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
			std::cout << commandLinePrefix << "Failed to load texture : " + defaultWorkingPath + textureFileName << "\n";
			DisplayTextureError(textureFileName, defaultWorkingPath);
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

	//Display an error box with the texture path that is missing
	void DisplayTextureError(std::string textureName, std::string texturePath)
	{
		std::string errorMessage = "Error failed to locate and load texture: " + texturePath + textureName;
		MessageBoxA(nullptr, errorMessage.data(), commandLinePrefix.data(), MB_ICONHAND);
	}
};

