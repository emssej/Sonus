#pragma once

#include <stdlib.h>

#include "utilities.h"

typedef enum
WidgetType
  {
	 WIDGETTYPE_DECIMAL_SLIDER,
	 WIDGETTYPE_INTEGER_SLIDER,
	 WIDGETTYPE_TEXT_BOX
  } WidgetType;

typedef struct
Widget
{
  WidgetType type;
  _Bool inlet, outlet;
  union
  {
	 long double decimal;
	 long long integer;
	 char *string;					  /* TODO: unicode */
  };
} Widget;

typedef struct
Node
{
  long long x, y;
  const char *title;
  size_t widgets_size;
  Widget *widgets;

  unsigned short n_inlets, n_outlets;
} Node;

void Node_initialize (Node *node, long long x, long long y, const char *title,
							 unsigned short n_inlets, unsigned short n_outlets);

