#pragma once

#include <SDL2/SDL.h>

#include "state.h"
#include "utilities.h"

typedef struct
GraphicsContext
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} GraphicsContext;

void GraphicsContext_initialize (GraphicsContext *ctx, unsigned short width,
											unsigned short height);
void GraphicsContext_prepare (GraphicsContext *ctx);
void GraphicsContext_done (GraphicsContext *ctx);
void GraphicsContext_draw_grid (GraphicsContext *ctx, SonusState *state);
void GraphicsContext_terminate (GraphicsContext *ctx);
