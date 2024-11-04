#include "SFMLGraphics.h"
#include <iostream>


bool SFMLGraphics::CreateSprite(const std::string& p_spriteId)
{
	//First check if we already have a sprite created that is associated with the objects ID
	const auto spriteToFind = loadedSprites.find(p_spriteId);

	//If we have already created a sprite for this object Id return false with an erorr
	if (spriteToFind != loadedSprites.end()) {
		std::cout << commandLinePrefix << "Attempted to create a duplicate sprite for object: " << p_spriteId;
		return false;
	}
	//If we haven't already created a sprite for this object try to create one and loaded the texture, also add to our sprite map
	sf::Sprite* newSprite = new sf::Sprite();
	loadedSprites[p_spriteId] = newSprite;
	//Cast from void* to sf::texture* then de-ref(Maybe not best practice but fuck it)
	newSprite->setTexture(*static_cast<sf::Texture*>(TryLoadTextureByFileName(p_spriteId)));

	return false;
}
bool SFMLGraphics::RenderSprite(const Sprite& p_sprite, const float p_xPosition, const float p_yPosition, const int p_frame)
{
	const std::string spriteId = p_sprite.SpriteId;
	//First we try to find the sprite to render it, if we are unsuccessful return false
	const auto spriteToFind = loadedSprites.find(spriteId);
	if (spriteToFind == loadedSprites.end())
	{
		std::cout << commandLinePrefix << "No sprite assigned to object: " << p_sprite.SpriteId;
		//Create the sprite if we haven't one assigned to the id yet, if it fails return false
		if (!CreateSprite(spriteId))
		{
			return false;
		}
	}
	//Since we found a sprite, draw it to the window at the requested position
	spriteToFind->second->setPosition(p_xPosition, p_yPosition);
	const int ySize = (loadedTextures[spriteId]->getSize().y / p_sprite.SpriteSheetRows);
	spriteToFind->second->setTextureRect(sf::IntRect(0, ySize * p_frame , loadedTextures[spriteId]->getSize().x, ySize));
	renderWindow->draw(*spriteToFind->second);
	return true;
}

Vector2 SFMLGraphics::CalculateBounds(const Sprite& p_spriteId)
{
	//First check if we already have a sprite created that is associated with the objects ID
	const auto spriteToFind = loadedSprites.find(p_spriteId.SpriteId);

	//If we have already created a sprite for this object Id fetch the texture and calculate the bounds
	if (spriteToFind == loadedSprites.end())
	{
		CreateSprite(p_spriteId.SpriteId);
	}
	const float ySize = (loadedTextures[p_spriteId.SpriteId]->getSize().y / p_spriteId.SpriteSheetRows);
	const float xSize = loadedTextures[p_spriteId.SpriteId]->getSize().x;
	
	return { xSize,ySize };

}

void SFMLGraphics::DrawBounds(const BoundingBox& p_boundingBox)
{
	BoundSprite.setTextureRect({ (int)p_boundingBox.Left, (int)p_boundingBox.Top
	, (int)p_boundingBox.Width, (int)p_boundingBox.Height });
	BoundSprite.setPosition(p_boundingBox.Left, p_boundingBox.Top);

	renderWindow->draw(BoundSprite);
}

//Tries to load the error texture
void SFMLGraphics::TryLoadErrorTexture()
{
	loadedTextures[ErrorTextureFileName] = errorTexture;
	if (!errorTexture->loadFromFile(DefaultWorkingPath + ErrorTextureFileName))
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
void* SFMLGraphics::TryLoadTextureByFileName(const std::string& p_textureFileName)
{
	//Check if we already have the texture loaded
	const auto textureMapTexture = loadedTextures.find(p_textureFileName);

	if (textureMapTexture != loadedTextures.end())
	{
		std::cout << commandLinePrefix << "Attempted to load same texture twice : " + DefaultWorkingPath + p_textureFileName << "\n";

		return textureMapTexture->second;
	}

	//Create a new texture pointer to hold the texture
	sf::Texture* textureToLoad = new sf::Texture;

	//Try load from the file path
	if (textureToLoad->loadFromFile(DefaultWorkingPath + p_textureFileName))
	{
		//Successfully loaded texture 
		loadedTextures[p_textureFileName] = textureToLoad;
		return textureToLoad;
	}
	else
	{
		//Delete the pointer as we won't need it
		delete textureToLoad;
		//Output an error with the file path for easier debugging
		std::cout << commandLinePrefix << "Failed to load texture : " + DefaultWorkingPath + p_textureFileName << "\n";
		DisplayTextureError(p_textureFileName, DefaultWorkingPath);
		//Return the default error texture
		return errorTexture;

	}
}

//Loops through each held pointer in loadedTextures and deletes them
void SFMLGraphics::UnloadAll()
{

	//Delete all the second values (pointers) from loaded sprites map
	for (const auto& pair : loadedSprites)
	{
		delete pair.second;
	}
	loadedSprites.clear();
	//Delete all the second values (pointers) from loaded textures map
	for (const auto& pair : loadedTextures)
	{
		delete pair.second;
	}
	//Clear the map
	loadedTextures.clear();


	
}


//Display an error box with the texture path that is missing
void SFMLGraphics::DisplayTextureError(const std::string& p_textureName, const std::string& p_texturePath)
{
	std::string errorMessage = "Error failed to locate and load texture: " + p_texturePath + p_textureName;
	//MessageBoxA(nullptr, errorMessage.data(), commandLinePrefix.data(), MB_ICONHAND);
}



