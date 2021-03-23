#pragma once

#include "utilities.h"

typedef enum
WidgetType
  {
	 WIDGETTYPE_INLET,
	 WIDGETTYPE_OUTLET,
	 WIDGETTYPE_NUMBER
  } WidgetType;

typedef struct
Widget
{
  WidgetType type;
  long long id;
  union {
	 long double number;
  };
} Widget;

typedef struct
Node
{
  size_t widgets_size;
  Widget *widgets;
  void (*function)(struct Node *self);
  /* Metadata */
  const char *title;
  long long x, y;
} Node;

void Node_execute (Node *node);
void Node_add_Widget (Node *node, Widget widget);
