#pragma once

#include <stdlib.h>

#include "utilities.h"

typedef enum
WidgetType
  {
	 WIDGETTYPE_TITLE,
	 WIDGETTYPE_NUMBER,
	 WIDGETTYPE_SYMBOL,
	 WIDGETTYPE_INLET,
	 WIDGETTYPE_OUTLET
  } WidgetType;

typedef struct
Widget
{
  WidgetType type;
  union
  {
	 long double number;
	 char *symbol;
  };
} Widget;

typedef struct
Node
{
  long long x, y;
  int w, h;
  _Bool dragging;
  
  size_t widgets_size;
  Widget *widgets;
} Node;

void Node_initialize (Node *node, long long x, long long y, char *title);
void Node_add_Widget (Node *node, Widget widget);

