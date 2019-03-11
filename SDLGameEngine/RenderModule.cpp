#include "RenderModule.h"
#include "Renderer.h"
#include "GameObject.h"
#include <stdio.h>
#include <string>

int RenderModule::numberOfLayers = 2;
std::vector<std::list<Renderer*>> RenderModule::renderers = std::vector<std::list<Renderer*>>();

RenderModule::RenderModule()
{

}


RenderModule::~RenderModule()
{
}

void RenderModule::AddRenderer(Renderer* renderer)
{
	if (renderer->GetLayer() >= numberOfLayers)
	{
		std::cout << "Render layer for GameObject " << renderer->gameObject->name << " is " << renderer->GetLayer() << " which does not exist!";
		return;
	}
	renderers.at(renderer->GetLayer()).push_back(renderer);
}

void RenderModule::RemoveRenderer(Renderer* renderer)
{
	if (renderer->GetLayer() >= numberOfLayers)
	{
		std::cout << "Render layer for GameObject " << renderer->gameObject->name << " is " << renderer->GetLayer() << " which does not exist!";
		return;
	}
	renderers.at(renderer->GetLayer()).remove(renderer);
}

void RenderModule::Start()
{
	for (int i = 0; i < numberOfLayers; i++)
	{
		renderers.push_back(std::list<Renderer*>());
	}
}

void RenderModule::Update()
{
	for (auto renderLayer : renderers)
	{
		for (auto renderer : renderLayer)
		{
			if (renderer != NULL)
			{
				renderer->Render();
			}
		}
	}
}
