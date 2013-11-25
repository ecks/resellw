#include <stdbool.h>
#include <stddef.h>
#include <mysql.h>

#include "util.h"
#include "list.h"
#include "room.h"

int room_add(char * room_desc)
{
  char buffer[200];

  sprintf(buffer, "INSERT INTO Room (room_description) VALUES ('%s')", room_desc);
  db_query(buffer); 
  return 0;
}

struct rooms * rooms_get(char * room_desc)
{
  char buffer[200];
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct rooms * rooms;
  struct room * room;

  rooms = calloc(1, sizeof(struct rooms));
  list_init(&rooms->room_list);

  sprintf(buffer, "SELECT * FROM Room where room_description = '%s'", room_desc);
  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * id = row[0];
    char * desc = row[1];

    printf("Id: %s\n",id);
    printf("Table: %s\n",desc);

    room = calloc(1, sizeof(struct room));
    list_init(&room->node);
    room->id = calloc(strlen(id) + 1, sizeof(char)); // 1 extra for null terminating output
    room->desc = calloc(strlen(desc) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(room->id, id, strlen(id));
    strncpy(room->desc, desc, strlen(desc));

    room->id[strlen(id)] = '\0';
    room->desc[strlen(desc)] = '\0';

    list_push_back(&rooms->room_list, &room->node);    
  }

  mysql_free_result(res);
  return rooms;
}

int room_delete(struct room * room)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Room where room_id = '%s'", room->id);
  db_query(buffer); 
  return 0;
}


int rooms_delete(struct rooms * rooms)
{
  struct room * room;
  LIST_FOR_EACH(room, struct room, node, &rooms->room_list)
  {
    room_delete(room);
  }

  return 0;
}
