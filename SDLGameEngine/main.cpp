#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Game.h"


Game* game = new Game();

int main( int argc, char* args[] )
{
	game->Awake();
	//Start up SDL and create window
	if( !game->Init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{		
		game->Setup();		
		while (!Game::quit)
		{
			game->Update();
		}
	}

	//Free resources and close SDL
	game->End();

	return 0;
}
