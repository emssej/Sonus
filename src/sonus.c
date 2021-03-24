#include "graphics.h"

int
main ()
{
  SDL_Init (SDL_INIT_VIDEO);

  SonusState state = { 0 };
  SonusState_initialize (&state, 800, 600);

  Scene_add_Node
	 (&state.scene, (Node) {
		.widgets_size = 0, .widgets = NULL, .function = NULL,
		.title = "Addition", .x = 100, .y = 100
	 });

  Scene_add_Node
	 (&state.scene, (Node) {
		.widgets_size = 0, .widgets = NULL, .function = NULL,
		.title = "Display number", .x = 300, .y = 100
	 });

  Node_add_Widget
	 (&state.scene.nodes[1], (Widget) {
		.type = WIDGETTYPE_NUMBER,
		.id = 0,
		.value = 0
	 });
  
  Node_add_Widget
	 (&state.scene.nodes[0], (Widget) {
		.type = WIDGETTYPE_OUTLET,
		.id = 1,
		.value = 0
	 });
  
  Node_add_Widget
	 (&state.scene.nodes[0], (Widget) {
		.type = WIDGETTYPE_INLET,
		.id = 2,
		.value = 0
	 });

  Node_add_Widget
	 (&state.scene.nodes[0], (Widget) {
		.type = WIDGETTYPE_INLET,
		.id = 3,
		.value = 0
	 });
  
  GraphicsContext gfx_ctx = { 0 };
  GraphicsContext_initialize (&gfx_ctx, &state);
  
  _Bool running = 1;
  SDL_Event e;
  
  while (running)
	 {
		while (SDL_PollEvent (&e))
		  {
			 if (e.type == SDL_QUIT)
				{
				  running = 0;
				}
		  }

		GraphicsContext_update (&gfx_ctx, &state);
	 }

  SDL_Quit ();
  
  return 0;
}
