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
  unsigned short grid_size = 32;
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
  
  SDL_Color c = { 255, 255, 255, 127 };
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
  long long relx = state->x + node->x;
  long long rely = state->y + node->y;
  int w, h;
  
  /* Draw the widgets. */
  
  for (size_t i = 0; i < node->widgets_size; ++i)
	 {
		Widget widget = node->widgets[i];

		switch (widget.type)
		  {
		  case WIDGETTYPE_TITLE:
			 {
				SDL_Color c = { 255, 255, 255, 255 };
				SDL_Surface *s = TTF_RenderText_Blended (mgr->fonts.default_16,
																	  widget.symbol, c);
				SDL_Texture *t = SDL_CreateTextureFromSurface (ctx->renderer, s);

				SDL_QueryTexture (t, NULL, NULL, &w, &h);

				SDL_Rect r = { relx, i * h + rely, w, h };
				
				SDL_SetRenderDrawColor (ctx->renderer, 127, 127, 127,
												SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect (ctx->renderer, &r);
				SDL_RenderCopy (ctx->renderer, t, NULL, &r);

				SDL_DestroyTexture(t);
				SDL_FreeSurface(s);
			 }
			 break;
		  case WIDGETTYPE_INLET:
			 {
				SDL_Rect r = { relx, i * h + rely, w, h };
				SDL_SetRenderDrawColor (ctx->renderer, 100, 100, 100,
												SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect (ctx->renderer, &r);

				int size = h / 2;
				SDL_Rect p = { relx - size / 2, (i * h + rely) + size / 2, size, size};
				SDL_SetRenderDrawColor(ctx->renderer, 255, 0, 0, 127);
				SDL_RenderFillRect (ctx->renderer, &p);
			 }
			 break;
		  case WIDGETTYPE_OUTLET:
			 {
				SDL_Rect r = { relx, i * h + rely, w, h };
				SDL_SetRenderDrawColor (ctx->renderer, 100, 100, 100,
												SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect (ctx->renderer, &r);

				int size = h / 2;
				SDL_Rect p = { relx + w - size / 2, (i * h + rely) + size / 2, size, size};
				SDL_SetRenderDrawColor(ctx->renderer, 0, 255, 0, 127);
				SDL_RenderFillRect (ctx->renderer, &p);
			 }
			 break;
		  default:
			 break;
		  }
	 }
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
