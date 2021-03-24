#include "scene.h"

void
Scene_add_Node (Scene *scene, Node node)
{
  scene->nodes = realloc (scene->nodes, sizeof (Node)
								  * (++scene->nodes_size));

  if (scene->nodes == NULL)
	 {
		FATAL ("Could not reallocate memory for node in scene.");
	 }

  scene->nodes[scene->nodes_size - 1] = node;
}

void
Scene_add_Connection (Scene *scene, long long from_id, long long to_id)
{
  scene->connections = realloc (scene->connections, sizeof (Connection)
										  * (++scene->connections_size));

  if (scene->nodes == NULL)
	 {
		FATAL ("Could not reallocate memory for connection in scene.");
	 }

  Widget *from = Scene_get_Widget_by_id (scene, from_id);
  Widget *to = Scene_get_Widget_by_id (scene, to_id);

  if (from == NULL || to == NULL)
	 {
		WARN ("Could not find connection input or output. No connection added.");
		return;
	 }
  
  if (from->type != WIDGETTYPE_OUTLET)
	 {
		WARN ("The connection input is not an outlet. No connection added.");
		return;
	 }

  if (to->type == WIDGETTYPE_OUTLET)
	 {
		WARN ("The connection output is an outlet. No connection added.");
		return;
	 }

  scene->connections[scene->connections_size - 1] =
	 (Connection) { from_id, to_id, from, to };
}

Widget
*Scene_get_Widget_by_id (Scene *scene, long long id)
{
  /* Two for loops should be good for now, I guess. Maybe implement a
	  hashmap later. */
  for (size_t i = 0; i < scene->nodes_size; ++i)
	 {
		for (size_t j = 0; j < scene->nodes[i].widgets_size; ++j)
		  {
			 if (scene->nodes[i].widgets[j].id == id)
				{
				  return &scene->nodes[i].widgets[j];
				}
		  }
	 }

  return NULL;
}

void
Scene_execute (Scene *scene)
{
  /* First, we put all the values from the "from" widget to the "to"
	  widget. */
  for (size_t i = 0; i < scene->connections_size; ++i)
	 {
		scene->connections[i].to->value = scene->connections[i].from->value;
	 }
  /* Then, we can execute the functions that each node has. */
  for (size_t i = 0; i < scene->nodes_size; ++i)
	 {
		if (scene->nodes[i].function != NULL)
		  {
			 Node_execute (&scene->nodes[i]);
		  }
	 }
}
