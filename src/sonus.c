#include <SDL2/SDL2_framerate.h>

#include "graphics.h"
#include "event.h"

void
Callback_quit (CallbackArgs *args)
{
  if (args->event->type == SDL_QUIT)
	 {
		args->state->running = 0;
	 }
}

void
Callback_resize (CallbackArgs *args)
{
  if (args->event->type == SDL_WINDOWEVENT &&
		args->event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	 {
		args->state->window_width = args->event->window.data1;
		args->state->window_height = args->event->window.data2;
	 }
}

void
Callback_dragstart (CallbackArgs *args)
{
  if (args->event->type == SDL_MOUSEBUTTONDOWN &&
		args->event->button.state == SDL_PRESSED &&
		args->event->button.button == SDL_BUTTON_MIDDLE)
	 {
		args->state->dragging = 1;
		args->state->drag_x = args->event->button.x - args->state->x;
		args->state->drag_y = args->event->button.y - args->state->y;
	 }
}

void
Callback_drag (CallbackArgs *args)
{
  if (args->event->type == SDL_MOUSEMOTION && args->state->dragging)
	 {
		args->state->x = args->event->motion.x - args->state->drag_x;
		args->state->y = args->event->motion.y - args->state->drag_y;
	 }
}

void
Callback_dragend (CallbackArgs *args)
{
  if (args->event->type == SDL_MOUSEBUTTONDOWN &&
		args->event->button.state == SDL_RELEASED &&
		args->event->button.button == SDL_BUTTON_MIDDLE)
	 {
		args->state->dragging = 0;
		args->state->drag_x = 0;
		args->state->drag_y = 0;
	 }
}

int
main ()
{
  SonusState state = { 0 };
  SonusState_initialize (&state);

  CallbackManager cb_mgr = { 0 };
  CallbackArgs args = { 0 };

  CallbackManager_add (&cb_mgr, Callback_quit);
  INFO ("%zu", cb_mgr.callbacks_size);
  CallbackManager_add (&cb_mgr, Callback_resize);
  INFO ("%zu", cb_mgr.callbacks_size);
  CallbackManager_add (&cb_mgr, Callback_dragstart);
  INFO ("%zu", cb_mgr.callbacks_size);
  CallbackManager_add (&cb_mgr, Callback_drag);
  INFO ("%zu", cb_mgr.callbacks_size);
  CallbackManager_add (&cb_mgr, Callback_dragend);
  INFO ("%zu", cb_mgr.callbacks_size);

  GraphicsContext gfx_ctx = { 0 };
  GraphicsContext_initialize (&gfx_ctx, state.window_width, state.window_height);

  SDL_Event event;
  FPSmanager fps_manager;
  SDL_initFramerate (&fps_manager);
  SDL_setFramerate (&fps_manager, 60);
  
  while (state.running)
	 {
		SDL_framerateDelay (&fps_manager);
		
		while (SDL_PollEvent (&event))
		  {
			 args.event = &event;
			 args.state = &state;
			 
			 CallbackManager_update (&cb_mgr, &args);
		  }

		GraphicsContext_prepare (&gfx_ctx);
		GraphicsContext_draw_grid (&gfx_ctx, &state);
		GraphicsContext_done (&gfx_ctx);
	 }
  
  GraphicsContext_terminate (&gfx_ctx);
  SDL_Quit ();
  
  return 0;
}
