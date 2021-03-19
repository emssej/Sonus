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
Callback_mousedown (CallbackArgs *args)
{
  /* First, we check if we click on any nodes. */
  _Bool found = 0;
  if (args->event->type == SDL_MOUSEBUTTONDOWN &&
		args->event->button.button == SDL_BUTTON_LEFT)
	 {
		for (size_t i = 0; i < args->state->nodes_size; ++i)
		  {
			 Node n = args->state->nodes[i];
			 long long relx = n.x + args->state->x;
			 long long rely = n.y + args->state->y;

			 if (args->event->button.x > relx && args->event->button.y > rely
				  && args->event->button.x < relx + n.w
				  && args->event->button.y < rely + n.h)
				{
				  args->state->nodes[i].dragging = 1;
				  found = 1;
				  break;
				}
		  }

		if (!found)
		  {
			 args->state->dragging = 1;
			 args->state->drag_x = args->event->button.x - args->state->x;
			 args->state->drag_y = args->event->button.y - args->state->y;
		  }
	 }
}

void
Callback_mousemotion (CallbackArgs *args)
{
  if (args->event->type == SDL_MOUSEMOTION && args->state->dragging)
	 {
		args->state->x = args->event->motion.x - args->state->drag_x;
		args->state->y = args->event->motion.y - args->state->drag_y;
	 }
  else if (args->event->type == SDL_MOUSEMOTION)
	 {
		for (size_t i = 0; i < args->state->nodes_size; ++i)
		  {
			 if (args->state->nodes[i].dragging)
				{
				  args->state->nodes[i].x = args->event->motion.x - args->state->drag_x;
				  args->state->nodes[i].y = args->event->motion.y - args->state->drag_y;
				}
		  }
	 }

}

void
Callback_mouseup (CallbackArgs *args)
{
  if (args->event->type == SDL_MOUSEBUTTONUP)
	 {
		args->state->dragging = 0;
		args->state->drag_x = 0;
		args->state->drag_y = 0;

		for (size_t i = 0; i < args->state->nodes_size; ++i)
		  {
			 args->state->nodes[i].dragging = 0;
		  }
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
  CallbackManager_add (&cb_mgr, Callback_mousedown);
  CallbackManager_add (&cb_mgr, Callback_mousemotion);
  CallbackManager_add (&cb_mgr, Callback_mouseup);

  SonusState state = { 0 };
  SonusState_initialize (&state);
  
  GraphicsContext gfx_ctx = { 0 };
  GraphicsContext_initialize (&gfx_ctx, state.window_width,
										state.window_height);

  ResourceManager res_mgr = { 0 };
  ResourceManager_initialize (&res_mgr);

  Node example = { 0 };
  Node_initialize (&example, 200, 200, "Oscillator");

  SonusState_add_Node (&state, example);
  
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
