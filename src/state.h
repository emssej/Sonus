#pragma once

#include "scene.h"

typedef struct
SonusState
{
  Scene scene;
  long long x, y, drag_x, drag_y;
  _Bool running, dragging;

  unsigned short window_width, window_height;
  unsigned short current_time;
  long double delta_time;
} SonusState;

void SonusState_initialize (SonusState *state, unsigned short width,
									 unsigned short height);
