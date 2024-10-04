#include "SFMLGraphics.h"
#include <iostream>


bool SFMLGraphics::CreateSprite(std::string& spriteId)
{
	//First check if we already have a sprite created that is associated with the objects ID
	auto spriteToFind = loadedSprites.find(spriteId);

	//If we have already created a sprite for this object Id return false with an erorr
	if (spriteToFind != loadedSprites.end()) {
		std::cout << commandLinePrefix << "Attempted to create a duplicate sprite for object: " << spriteId;
		return false;
	}
	//If we haven't already created a sprite for this object try to create one and loaded the texture, also add to our sprite map
	sf::Sprite* newSprite = new sf::Sprite();
	loadedSprites[spriteId] = newSprite;
	//Cast from void* to sf::texture* then deref(Maybe not best practice but fuck it)
	newSprite->setTexture(*static_cast<sf::Texture*>(TryLoadTextureByFileName(spriteId)));

	return false;
}
bool SFMLGraphics::RenderSprite(std::string& spriteId, float xPosition, float yPosition, int rows, int frame)
{

	//First we try to find the sprite to render it, if we are unsucesful return false
	auto spriteToFind = loadedSprites.find(spriteId);
	if (spriteToFind == loadedSprites.end())
	{
		std::cout << commandLinePrefix << "No sprite assigned to object: " << spriteId;
		//Create the sprite if we havent one assigned to the id yet, if it fails return false
		if (!CreateSprite(spriteId))
		{
			return false;
		}
	}
	//Since we found a sprite, draw it to the window at the requested position
	spriteToFind->second->setPosition(xPosition, yPosition);
	int ySize = (loadedTextures[spriteId]->getSize().y / rows);
	spriteToFind->second->setTextureRect(sf::IntRect(0, ySize * frame , loadedTextures[spriteId]->getSize().x, ySize));
	renderWindow->draw(*spriteToFind->second);
	return true;
}

//Tries to load the error texture
void SFMLGraphics::TryLoadErrorTexture()
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
			//MessageBoxA(nullptr, "!Please reinstall game files!", "ERROR--ERROR--ERROR", MB_ICONERROR);
		}



		std::cout << commandLinePrefix << "Failed to load error texture!\n";
		//DisplayTextureError(errorTextureFileName, defaultWorkingPath);
	}
}

//Tries to load a texture via the filename and return it
void* SFMLGraphics::TryLoadTextureByFileName(std::string& textureFileName)
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
void SFMLGraphics::UnloadAll()
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
void SFMLGraphics::DisplayTextureError(std::string textureName, std::string texturePath)
{
	std::string errorMessage = "Error failed to locate and load texture: " + texturePath + textureName;
	//MessageBoxA(nullptr, errorMessage.data(), commandLinePrefix.data(), MB_ICONHAND);
}



