#include "callback.h"

void
CallbackManager_add (CallbackManager *mgr, Callback callback)
{
  mgr->callbacks = realloc (mgr->callbacks, sizeof (Callback)
									 * (++mgr->callbacks_size));

  if (mgr->callbacks == NULL)
	 {
		FATAL ("Couldn't reallocate memory for callback.");
	 }

  mgr->callbacks[mgr->callbacks_size - 1] = callback;
}

void
CallbackManager_update (CallbackManager *mgr, CallbackArgs *args)
{
  for (size_t i = 0; i < mgr->callbacks_size; ++i)
	 {
		mgr->callbacks[i](args);
	 }
}
