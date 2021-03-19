#include "node.h"

void
Node_initialize (Node *node, long long x, long long y, char *title)
{
  node->x = x;
  node->y = y;
  node->widgets_size = 0;

  Widget widget = { 0 };
  widget.type = WIDGETTYPE_TITLE;
  widget.symbol = title;
  Node_add_Widget (node, widget);

  Widget inlet = { 0 };
  inlet.type = WIDGETTYPE_INLET;
  Node_add_Widget (node, inlet);

  Widget outlet = { 0 };
  outlet.type = WIDGETTYPE_OUTLET;
  Node_add_Widget (node, outlet);
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
