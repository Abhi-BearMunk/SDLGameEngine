#include "TextRenderer.h"
#include "Game.h"
#include "Rect.h"


TextRenderer::TextRenderer(std::string _fontPath, int size, std::string _text, int _layer) : Renderer(_layer)
{
	gFont = TTF_OpenFont(_fontPath.c_str(), size);
	text = _text;
	LoadText();
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::Cleanup()
{
	FreeTexture();
	Renderer::Cleanup();
}

void TextRenderer::SetFont(std::string _font, int size)
{
	gFont = TTF_OpenFont(_font.c_str(), size);
	LoadText();
}

void TextRenderer::SetText(std::string _text)
{
	text = _text;
	LoadText();
}

const int& TextRenderer::GetWidth()
{
	return width;
}

const int& TextRenderer::GetHeight()
{
	return height;
}

void TextRenderer::Render()
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
	SDL_RenderCopyEx(Game::gRenderer, texture, NULL, &renderQuad, ceil(gameObject->transform->GetAbsoluteAngle()), &pivot, flip);
}

// BUGGY
void TextRenderer::SetColor(Color _color)
{
	SDL_SetTextureColorMod(texture, _color.r, _color.g, _color.b);
	SDL_SetTextureAlphaMod(texture, _color.a);
	color = _color;
}

bool TextRenderer::LoadText()
{
	//Get rid of preexisting texture
	FreeTexture();

	//Load image at specified path
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(Game::gRenderer, textSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return texture != NULL;
}

void TextRenderer::FreeTexture()
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

