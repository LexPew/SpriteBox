#pragma once
#include <string>
class IGraphics
{
protected:
	//--Texture Variables--
	std::string defaultWorkingPath = "Data/Textures/";	//This is the default directory for textures (Set to the data and textures folder)	
	std::string errorTextureFileName = "Error.png";

public:
	//--Sprite Handling--

	//Handles creating a sprite with an input texture name to load and then output the Sprite
	virtual bool CreateSprite(unsigned int objectId, std::string& textureName) = 0;
	//Handles rendering a sprite at the given location and frame number
	virtual void RenderSprite(unsigned int objectId, int xPosition, int yPosition) = 0;
	public:
	//--Texture Handling--
	
	//Handles loading the initial error texture when constructor called
	virtual void TryLoadErrorTexture() = 0;
	//Loads the texture onto a sprite via the fileName in default working dir
	virtual void* TryLoadTextureByFileName( std::string& textureFileName) = 0;
	//Unloads and deletes all textures on destructor
	virtual void UnloadAll() = 0;

};

