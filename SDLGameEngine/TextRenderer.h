#pragma once
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Color.h"

class TextRenderer :
	public Renderer
{
public:
	TextRenderer(std::string _fontPath, int size, std::string _text = "");
	~TextRenderer();

	void Render();

	bool flipX;
	bool flipY;

	const int& GetWidth();
	const int& GetHeight();

	void SetColor(Color _color);
	void SetFont(std::string _fontPath, int size);
	void SetText(std::string _text);

	void Cleanup();

private:
	TTF_Font* gFont;
	bool LoadText();
	void FreeTexture();
	std::string text;
	SDL_Texture* texture = NULL;
	Color color;
	int width;
	int height;
	SDL_Point pivot;
	int lastXpos;
	int lastYpos;
};

