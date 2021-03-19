#include <SDL2/SDL_ttf.h>

#include "callback.h"
#include "graphics.h"
#include "resources.h"

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
  if (args->event->type == SDL_MOUSEBUTTONUP &&
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
  SDL_Init (SDL_INIT_VIDEO);
  TTF_Init ();

  CallbackManager cb_mgr = { 0 };
  CallbackArgs args = { 0 };

  CallbackManager_add (&cb_mgr, Callback_quit);
  CallbackManager_add (&cb_mgr, Callback_resize);
  CallbackManager_add (&cb_mgr, Callback_dragstart);
  CallbackManager_add (&cb_mgr, Callback_drag);
  CallbackManager_add (&cb_mgr, Callback_dragend);

  SonusState state = { 0 };
  SonusState_initialize (&state);
  
  GraphicsContext gfx_ctx = { 0 };
  GraphicsContext_initialize (&gfx_ctx, state.window_width,
										state.window_height);

  ResourceManager res_mgr = { 0 };
  ResourceManager_initialize (&res_mgr);

  Node example;
  Node_initialize (&example, 200, 200, "Oscillator", 3, 4);
  Node example2;
  Node_initialize (&example2, 400, 200, "Addition", 2, 1);

  SonusState_add_Node (&state, example);
  SonusState_add_Node (&state, example2);

  SDL_Event event;
  
  while (state.running)
	 {
		SonusState_update (&state);
		
		while (SDL_PollEvent (&event))
		  {
			 args.event = &event;
			 args.state = &state;
			 
			 CallbackManager_update (&cb_mgr, &args);
		  }

		GraphicsContext_update (&gfx_ctx, &res_mgr, &state);
	 }

  ResourceManager_terminate (&res_mgr);
  GraphicsContext_terminate (&gfx_ctx);
  
  TTF_Quit ();
  SDL_Quit ();
  
  return 0;
}
