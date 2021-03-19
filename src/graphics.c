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
GraphicsContext_draw_grid (GraphicsContext *ctx, SonusState *state)
{
  unsigned short grid_size = state->zoom * 32;
  short xx = state->x % grid_size;
  short yy = state->y % grid_size;

  SDL_SetRenderDrawColor (ctx->renderer, 255, 255, 255, 16);
  
  for (short x = -xx; x < state->window_width + grid_size; x += grid_size)
	 {
		SDL_RenderDrawLine (ctx->renderer, x, 0, x, state->window_height);
	 }

  for (short y = -yy; y < state->window_height + grid_size; y += grid_size)
	 {
		SDL_RenderDrawLine (ctx->renderer, 0, y, state->window_width, y);
	 }
}

void
GraphicsContext_draw_coords (GraphicsContext *ctx, ResourceManager *mgr,
									  SonusState *state)
{
  char buffer[256];
  sprintf (buffer, "X = %lli, Y = %lli, DRAG_X = %lli, DRAG_Y = %lli, FPS=%.2Lf",
			  state->x, state->y, state->drag_x, state->drag_y, 1 / state->delta_time);
  
  SDL_Color c = { 255, 255, 255, 255 };
  SDL_Surface *s = TTF_RenderText_Blended (mgr->fonts.default_16, buffer, c);
  SDL_Texture *t = SDL_CreateTextureFromSurface (ctx->renderer, s);
  int w, h;

  SDL_QueryTexture (t, NULL, NULL, &w, &h);

  SDL_RenderCopy (ctx->renderer, t, NULL, &(SDL_Rect) { 0, 0, w, h });

  SDL_DestroyTexture(t);
  SDL_FreeSurface(s);
}

void
GraphicsContext_draw_node (GraphicsContext *ctx, ResourceManager *mgr,
									SonusState *state, Node *node)
{
  SDL_Color c = { 255, 255, 255, 255 };
  SDL_Surface *s = TTF_RenderText_Blended (mgr->fonts.default_16, node->title, c);
  SDL_Texture *t = SDL_CreateTextureFromSurface (ctx->renderer, s);
  int w, h;

  SDL_QueryTexture (t, NULL, NULL, &w, &h);

  long long relx = state->x + node->x;
  long long rely = state->y + node->y;
  SDL_Rect wrect = { relx, rely, w, h };

  /* Draw the title bar. */
  
  SDL_SetRenderDrawColor(ctx->renderer, 127, 127, 127, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect (ctx->renderer, &wrect);

  SDL_RenderCopy (ctx->renderer, t, NULL, &wrect);

  /* Draw the inlets. */
  
  for (unsigned short i = 0; i < node->n_inlets; ++i)
	 {
		int y = rely + i * h + h;
		SDL_Rect rect = { relx, y, w, h };
		SDL_SetRenderDrawColor(ctx->renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect (ctx->renderer, &rect);

		int size = h / 2;
		SDL_Rect connection = { relx - size / 2, y + size / 2, size, size };
		SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect (ctx->renderer, &connection);
	 }

  /* Draw the outlets. */
  
  for (unsigned short i = 0; i < node->n_outlets; ++i)
	 {
		int y = node->n_inlets * h + (rely + i * h + h);
		SDL_Rect rect = { relx, y, w, h };
		SDL_SetRenderDrawColor(ctx->renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect (ctx->renderer, &rect);

		int size = h / 2;
		SDL_Rect connection = { relx + w - size / 2, y + size / 2, size, size };
		SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect (ctx->renderer, &connection);
	 }

  SDL_DestroyTexture(t);
  SDL_FreeSurface(s);
}

void
GraphicsContext_update (GraphicsContext *ctx, ResourceManager *mgr,
								SonusState *state)
{
  SDL_SetRenderDrawColor(ctx->renderer, 51, 51, 51, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(ctx->renderer);

  if (state->grid_enabled)
	 {
		GraphicsContext_draw_grid (ctx, state);
	 }

  for (size_t i = 0; i < state->nodes_size; ++i)
	 {
		GraphicsContext_draw_node (ctx, mgr, state, &state->nodes[i]);
	 }
  
  GraphicsContext_draw_coords (ctx, mgr, state);
  
  SDL_RenderPresent (ctx->renderer);
}

void
GraphicsContext_terminate (GraphicsContext *ctx)
{
  SDL_DestroyWindow (ctx->window);
  SDL_DestroyRenderer (ctx->renderer);
}
