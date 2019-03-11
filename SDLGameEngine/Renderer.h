#pragma once
#include "Component.h"
#include "Vector2.h"

class Renderer:
	public Component
{
public:
	Renderer();
	Renderer(int _layer);
	virtual ~Renderer();
	virtual void Render();
	void SetLayer(int _layer);
	int GetLayer();
	virtual void Cleanup();
private:
	int layer;
};

