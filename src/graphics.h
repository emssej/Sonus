#pragma once

#include <SDL2/SDL.h>
#include <cairo/cairo.h>

#include "state.h"
#include "utilities.h"

typedef struct
GraphicsContext
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *screen;
  cairo_t *canvas;
} GraphicsContext;

void GraphicsContext_initialize (GraphicsContext *ctx, SonusState *state);
void GraphicsContext_update (GraphicsContext *ctx, SonusState *state);
