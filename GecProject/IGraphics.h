#pragma once
#include <string>
#include <SFML/Window/Window.hpp>

#include "Sprite.h"
class IGraphics
{
protected:
	/**
	 * String that holds the default working directory path for texture assets
	 */
	std::string DefaultWorkingPath{ "Data/Textures/" };

	/**
	 * String that holds the default error texture file name within the working dir
	 */
	std::string ErrorTextureFileName{ "Error.png" };


public:
	static IGraphics* GraphicsHandlerInstance;
	IGraphics() = default;
	virtual ~IGraphics() = default;
	/**
	 * Attempt to create a new sprite with the input ID
	 * @param p_spriteId Sprite file name
	 * @return True or false depending on whether it was successful in creating a new sprite
	 */
	virtual bool CreateSprite(const std::string& p_spriteId) = 0;
	/**
	 * Renders a given sprite at the location and frame input
	 * @param p_sprite Sprite to render
	 * @param p_xPosition X Position for sprite to be rendered at
	 * @param p_yPosition Y Position for sprite to be rendered at
	 * @param p_frame Used for sprite-sheets to define which frame to play
	 * @return 
	 */
	virtual bool RenderSprite(const Sprite& p_sprite, const float p_xPosition, const float p_yPosition,  const int p_frame) = 0;

	/**
	 * Creates a bounding box for an input sprite
	 * @param p_spriteId Sprite file name
	 * @return 
	 */
	virtual Vector2 CalculateBounds(const Sprite& p_spriteId) = 0;

	virtual void DrawBounds(const BoundingBox& p_boundingBox) = 0;
protected:
	//--Texture Handling--

	/**
	 * Attempts to load the error texture
	 */
	virtual void TryLoadErrorTexture() = 0;

	/**
	 * Attemps to load a texture via its filename
	 * @param p_textureFileName Filename of the texture in working dir
	 * @return 
	 */
	virtual void* TryLoadTextureByFileName(const std::string& p_textureFileName) = 0;

	/**
	 * Unloads and deletes all textures
	 */
	virtual void UnloadAll() = 0;

};

