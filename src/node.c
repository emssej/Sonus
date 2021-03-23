#include "node.h"

void
Node_execute (Node *node)
{
  node->function(node);
}

void
Node_add_Widget (Node *node, Widget widget)
{
  node->widgets = realloc (node->widgets, sizeof (Widget)
									* (++node->widgets_size));

  if (node->widgets == NULL)
	 {
		FATAL ("Could not reallocate memory for node widget.");
	 }

  node->widgets[node->widgets_size - 1] = widget;
}
