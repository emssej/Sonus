#include "node.h"

void
Node_initialize (Node *node, long long x, long long y, const char *title,
					  unsigned short n_inlets, unsigned short n_outlets)
{
  node->x = x;
  node->y = y;
  node->title = title;
  node->widgets_size = 0;
  node->n_inlets = n_inlets;
  node->n_outlets = n_outlets;
}

void
Node_add_Widget (Node *node, Widget widget)
{
  node->widgets = realloc (node->widgets, sizeof (Widget)
									* (++node->widgets_size));

  if (node->widgets == NULL)
	 {
		FATAL ("Couldn't reallocate memory for node widget.");
	 }

  node->widgets[node->widgets_size - 1] = widget;
}


