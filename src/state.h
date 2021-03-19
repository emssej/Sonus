#pragma once

#include <stdlib.h>

#include <SDL2/SDL.h>

#include "node.h"
#include "utilities.h"

typedef struct
SonusState
{
  _Bool running;
  _Bool dragging;
  _Bool grid_enabled;

  unsigned short window_width, window_height;
  unsigned short current_time;
  long double delta_time;
  
  long long x, y, drag_x, drag_y;

  size_t nodes_size;
  Node *nodes;
} SonusState;

void SonusState_initialize (SonusState *state);
void SonusState_update (SonusState *state);
void SonusState_add_Node (SonusState *state, Node node);
