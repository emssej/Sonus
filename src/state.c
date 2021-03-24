#include "state.h"

void
SonusState_initialize (SonusState *state, unsigned short width,
							  unsigned short height)
{
  state->window_width = width;
  state->window_height = height;
}
