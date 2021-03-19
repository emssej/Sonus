#include "resources.h"

void
ResourceManager_initialize (ResourceManager *mgr)
{
  mgr->fonts.default_12 = TTF_OpenFont ("res/RobotoMono-Regular.ttf", 12);
  mgr->fonts.default_16 = TTF_OpenFont ("res/RobotoMono-Regular.ttf", 16);
  mgr->fonts.default_24 = TTF_OpenFont ("res/RobotoMono-Regular.ttf", 24);
  mgr->fonts.default_48 = TTF_OpenFont ("res/RobotoMono-Regular.ttf", 48);
  mgr->fonts.default_72 = TTF_OpenFont ("res/RobotoMono-Regular.ttf", 72);
}

void
ResourceManager_terminate (ResourceManager *mgr)
{
  TTF_CloseFont (mgr->fonts.default_12);
  TTF_CloseFont (mgr->fonts.default_16);
  TTF_CloseFont (mgr->fonts.default_24);
  TTF_CloseFont (mgr->fonts.default_48);
  TTF_CloseFont (mgr->fonts.default_72);
}
