#include "state.h"

void
SonusState_initialize (SonusState *state)
{
  state->running = 1;
  state->dragging = 0;
  state->grid_enabled = 0;		  /* TODO: fix the grid */

  state->window_width = 640;
  state->window_height = 480;
  state->current_time = SDL_GetTicks ();
  
  state->x = 0;
  state->y = 0;
  state->drag_x = 0;
  state->drag_y = 0;

  state->nodes_size = 0;
}

void
SonusState_update (SonusState *state)
{
  unsigned short last_time = state->current_time;
  state->current_time = SDL_GetTicks ();
  state->delta_time = (state->current_time - last_time) / 1000.0;
}

void
SonusState_add_Node (SonusState *state, Node node)
{
  state->nodes = realloc (state->nodes, sizeof (Node)
								  * (++state->nodes_size));

  if (state->nodes == NULL)
	 {
		FATAL ("Couldn't reallocate memory for node.");
	 }

  state->nodes[state->nodes_size - 1] = node;
}
