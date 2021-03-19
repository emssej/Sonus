#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "node.h"
#include "resources.h"
#include "state.h"
#include "utilities.h"

typedef struct
GraphicsContext
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} GraphicsContext;

void GraphicsContext_initialize(GraphicsContext *ctx, unsigned short width,
										  unsigned short height);
void GraphicsContext_draw_node (GraphicsContext *ctx, ResourceManager *mgr,
										  SonusState *state, Node *node);
void GraphicsContext_update (GraphicsContext *ctx, ResourceManager *mgr,
									  SonusState *state);
void GraphicsContext_terminate (GraphicsContext *ctx);
