#pragma once

#include "utilities.h"

typedef struct
SonusState
{
  _Bool running;
  _Bool dragging;
  _Bool grid_enabled;

  unsigned short window_width, window_height;
  long x, y, drag_x, drag_y;
  unsigned short zoom;
} SonusState;

void SonusState_initialize (SonusState *state);
