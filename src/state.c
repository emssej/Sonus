#include "state.h"

void
SonusState_initialize (SonusState *state)
{
  state->running = 1;
  state->dragging = 0;
  state->grid_enabled = 1;

  state->window_width = 640;
  state->window_height = 480;
  state->x = 0;
  state->y = 0;
  state->drag_x = 0;
  state->drag_y = 0;
  state->zoom = 1;
}
