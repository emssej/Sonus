#pragma once

#include <SDL2/SDL.h>

#include "state.h"
#include "utilities.h"

typedef struct
CallbackArgs
{
  SDL_Event *event;
  Uint8 **keystates;
  SonusState *state;
} CallbackArgs;

typedef void (*Callback) (CallbackArgs *args);

typedef struct
CallbackManager
{
  size_t callbacks_size;
  Callback *callbacks;
} CallbackManager;

void CallbackManager_add (CallbackManager *mgr, Callback callback);
void CallbackManager_update (CallbackManager *mgr, CallbackArgs *args);
