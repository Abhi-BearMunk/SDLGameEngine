#include "SpriteRenderer.h"
#include "Game.h"



SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::SpriteRenderer(Sprite* _sprite, int _layer) : Renderer(_layer)
{
	SetSprite(_sprite);
}

SpriteRenderer::SpriteRenderer(std::string _imagePath, Rect * _clipFrame, int _layer) : Renderer(_layer)
{
	Sprite* _sprite = new Sprite(_imagePath, _clipFrame);
	SetSprite(_sprite);
}

SpriteRenderer::~SpriteRenderer()
{
	
}

void SpriteRenderer::Cleanup()
{
 	FreeTexture();
	Renderer::Cleanup();
}

void SpriteRenderer::SetSprite(Sprite* _sprite)
{
	if (sprite == NULL || sprite->GetPath() != _sprite->GetPath())
	{
		sprite = _sprite;
		LoadSprite();
		return;
	}
	sprite = _sprite;
}

const int& SpriteRenderer::GetWidth()
{
	return sprite->GetClipFrame() != NULL ? sprite->GetClipFrame()->w : width;
}

const int& SpriteRenderer::GetHeight()
{
	return sprite->GetClipFrame() != NULL ? sprite->GetClipFrame()->h : height;
}

void SpriteRenderer::Render()
{
	Renderer::Render();
	SDL_Point pivot;
	int scaledWidth = ceil(GetWidth() * gameObject->transform->GetAbsoluteScale().x);
	int scaledHeight = ceil(GetHeight() * gameObject->transform->GetAbsoluteScale().y);
	pivot.x = floor(scaledWidth * 0.5f);
	pivot.y = floor(scaledHeight * 0.5f);
	int xPos = ceil(gameObject->transform->GetAbsolutePosition().x) - pivot.x;
	int yPos = ceil(gameObject->transform->GetAbsolutePosition().y) - pivot.y;
	xPos -= Camera::x;
	yPos -= Camera::y;
	Rect renderQuad;
	/*if (abs(lastXpos - xPos) >= 1)
	{
		lastXpos = xPos;
	}
	if (abs(lastYpos - yPos) >= 1)
	{
		lastYpos = yPos;
	}*/
	renderQuad.x = (xPos);
	renderQuad.y = (yPos);
	renderQuad.w = (scaledWidth);
	renderQuad.h = (scaledHeight);
	SDL_RendererFlip flip = flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE | flipY ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(Game::gRenderer, texture, sprite->GetClipFrame(), &renderQuad, ceil(gameObject->transform->GetAbsoluteAngle()), &pivot, flip);
}

void SpriteRenderer::SetColor(Color _color)
{
	SDL_SetTextureColorMod(texture, _color.r, _color.g, _color.b);
	SDL_SetTextureAlphaMod(texture, _color.a);
	color = _color;
}

bool SpriteRenderer::LoadSprite()
{
	//Get rid of preexisting texture
	FreeTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(sprite->GetPath().c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", sprite->GetPath().c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", sprite->GetPath().c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

void SpriteRenderer::FreeTexture()
{
	//Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}
