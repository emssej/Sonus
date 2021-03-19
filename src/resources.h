#pragma once

#include <SDL2/SDL_ttf.h>

typedef struct
ResourceManager
{
  struct fonts
  {
	 TTF_Font *default_12;
	 TTF_Font *default_16;
	 TTF_Font *default_24;
	 TTF_Font *default_48;
	 TTF_Font *default_72;
  } fonts;
} ResourceManager;

void ResourceManager_initialize (ResourceManager *mgr);
void ResourceManager_terminate (ResourceManager *mgr);
