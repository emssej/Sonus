#include "graphics.h"

void
GraphicsContext_initialize (GraphicsContext *ctx, SonusState *state)
{
  ctx->window = SDL_CreateWindow ("Sonus", SDL_WINDOWPOS_UNDEFINED,
											 SDL_WINDOWPOS_UNDEFINED, state->window_width,
											 state->window_height, SDL_WINDOW_RESIZABLE
											 | SDL_WINDOW_ALLOW_HIGHDPI);

  if (!ctx->window)
	 {
		FATAL ("Could not initialize SDL window: %s", SDL_GetError ());
	 }
  
  ctx->renderer = SDL_CreateRenderer (ctx->window, -1,
												  SDL_RENDERER_ACCELERATED);

  if (!ctx->window)
	 {
		FATAL ("Could not initialize SDL renderer: %s", SDL_GetError ());
	 }

  ctx->screen = SDL_CreateTexture (ctx->renderer, SDL_PIXELFORMAT_ARGB8888,
											  SDL_TEXTUREACCESS_STREAMING,
											  state->window_width, state->window_height);

  void *pixels;
  int pitch;
  SDL_LockTexture (ctx->screen, NULL, &pixels, &pitch);
  
  cairo_surface_t *c = cairo_image_surface_create_for_data
	 (pixels, CAIRO_FORMAT_ARGB32, state->window_width, state->window_height,
	  pitch);

  ctx->canvas = cairo_create (c);

  SDL_UnlockTexture (ctx->screen);
}

void
GraphicsContext_draw_Node (GraphicsContext *ctx, SonusState *state, Node *node)
{
  long long relx = state->x + node->x;
  long long rely = state->y + node->y;
  cairo_text_extents_t extents;
  cairo_set_font_size (ctx->canvas, 13.0);
  cairo_text_extents (ctx->canvas, node->title, &extents);
  cairo_set_source_rgba (ctx->canvas, 0.9, 0.9, 0.9, 1.0);
  cairo_move_to (ctx->canvas, relx, rely - extents.height);
  cairo_show_text (ctx->canvas, node->title);

  for (size_t i = 0; i < node->widgets_size; ++i)
	 {
		cairo_set_source_rgba (ctx->canvas, 0.2, 0.2, 0.2, 1.0);
		cairo_set_line_width (ctx->canvas, 0);
		cairo_rectangle (ctx->canvas, relx, rely + i * WIDGET_HEIGHT,
							  WIDGET_WIDTH, WIDGET_HEIGHT);
		cairo_fill (ctx->canvas);

		switch (node->widgets[i].type)
		  {
		  case WIDGETTYPE_INLET:
			 {
				long long r = WIDGET_HEIGHT / 4;
				cairo_set_source_rgba (ctx->canvas, 0.9, 0.1, 0.1, 0.5);
				cairo_arc (ctx->canvas, relx, rely + i * WIDGET_HEIGHT + r * 2,
							  r, 0, 2 * 3.14);
				cairo_fill (ctx->canvas);
			 }
			 break;
		  case WIDGETTYPE_OUTLET:
			 {
				long long r = WIDGET_HEIGHT / 4;
				cairo_set_source_rgba (ctx->canvas, 0.1, 0.1, 0.9, 0.5);
				cairo_arc (ctx->canvas, relx + WIDGET_WIDTH,
							  rely + i * WIDGET_HEIGHT + r * 2, r, 0, 2 * 3.14);
				cairo_fill (ctx->canvas);
			 }
			 break;
		  case WIDGETTYPE_NUMBER:
			 {
				char buf[128];
				snprintf (buf, 128, "%.2Lf", node->widgets[i].value);
				
				cairo_set_font_size (ctx->canvas, 11.0);
				cairo_text_extents (ctx->canvas, buf, &extents);

				cairo_set_source_rgba (ctx->canvas, 0.4, 0.4, 0.4, 1.0);
				cairo_rectangle (ctx->canvas, relx + MARGIN,
									  rely + i * WIDGET_HEIGHT + MARGIN, WIDGET_WIDTH
									  - 2 * MARGIN, WIDGET_HEIGHT - 2 * MARGIN);
				cairo_fill (ctx->canvas);

				cairo_set_source_rgba (ctx->canvas, 0.9, 0.9, 0.9, 1.0);
				cairo_move_to (ctx->canvas, relx + WIDGET_WIDTH / 2
									- extents.width / 2, rely + WIDGET_HEIGHT / 2
									+ extents.height / 2);
				cairo_show_text (ctx->canvas, buf);

				long long r = WIDGET_HEIGHT / 4;
				cairo_set_source_rgba (ctx->canvas, 0.9, 0.1, 0.1, 0.5);
				cairo_arc (ctx->canvas, relx, rely + i * WIDGET_HEIGHT + r * 2,
							  r, 0, 2 * 3.14);
				cairo_fill (ctx->canvas);
			 }
			 break;
		  }
	 }
}

void
GraphicsContext_draw_Scene (GraphicsContext *ctx, SonusState *state, Scene *scene)
{
  for (size_t i = 0; i < scene->nodes_size; ++i)
	 {
		GraphicsContext_draw_Node (ctx, state, &scene->nodes[i]);
	 }
}

void
GraphicsContext_update (GraphicsContext *ctx, SonusState *state)
{
  void *pixels;
  int pitch;
  SDL_LockTexture (ctx->screen, NULL, &pixels, &pitch);

  cairo_set_source_rgba (ctx->canvas, 0.1, 0.1, 0.1, 1.0);
  cairo_rectangle (ctx->canvas, 0, 0, state->window_width,
						 state->window_height);
  cairo_fill (ctx->canvas);

  GraphicsContext_draw_Scene (ctx, state, &state->scene);
  
  SDL_UnlockTexture (ctx->screen);

  SDL_RenderCopy (ctx->renderer, ctx->screen, NULL, NULL);
  SDL_RenderPresent(ctx->renderer);
}
