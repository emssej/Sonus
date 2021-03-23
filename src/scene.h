#pragma once

#include "node.h"
#include "utilities.h"

typedef struct
Connection
{
  long long from_id, to_id;
} Connection;

typedef struct
Scene
{
  size_t nodes_size;
  Node *nodes;
  size_t connections_size;
  Connection *connections;
} Scene;

void Scene_add_Node (Scene *scene, Node node);
void Scene_add_Connection (Scene *scene, Connection connection);
Widget *Scene_get_Widget_by_id (Scene *scene, long long id);
void Scene_execute (Scene *scene);
