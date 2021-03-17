#include "graphics.h"

void
GraphicsContext_initialize (GraphicsContext *ctx, unsigned short width,
									 unsigned short height)
{
  ctx->window = SDL_CreateWindow ("Sonus", SDL_WINDOWPOS_UNDEFINED,
											 SDL_WINDOWPOS_UNDEFINED, width, height,
										    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);

  if (!ctx->window)
	 {
		FATAL ("Could not initialize SDL window: %s", SDL_GetError ());
	 }

  ctx->renderer = SDL_CreateRenderer (ctx->window, -1,
												  SDL_RENDERER_ACCELERATED);

  if (!ctx->renderer)
	 {
		FATAL ("Could not initialize SDL renderer: %s", SDL_GetError ());
	 }

  SDL_SetRenderDrawBlendMode (ctx->renderer, SDL_BLENDMODE_BLEND);
}

void
GraphicsContext_prepare (GraphicsContext *ctx)
{
  SDL_SetRenderDrawColor(ctx->renderer, 51, 51, 51, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ctx->renderer);
}

void
GraphicsContext_done (GraphicsContext *ctx)
{
  SDL_RenderPresent (ctx->renderer);
}

void
GraphicsContext_draw_grid (GraphicsContext *ctx, SonusState *state)
{
  SDL_SetRenderDrawColor (ctx->renderer, 255, 255, 255, 16);
  
  if (state->grid_enabled)
	 {
		unsigned short grid_size = state->zoom * 32;

		for (unsigned short x = 0; x < state->window_width; x += grid_size)
		  {
			 for (unsigned short y = 0; y < state->window_height; y += grid_size)
				{
				  SDL_Rect r = { x, y, grid_size, grid_size };
				  SDL_RenderDrawRect (ctx->renderer, &r);
				}
		  }
	 }
}

void
GraphicsContext_terminate (GraphicsContext *ctx)
{
  SDL_DestroyWindow (ctx->window);
  SDL_DestroyRenderer (ctx->renderer);
}
