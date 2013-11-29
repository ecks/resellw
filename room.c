#include <stdbool.h>
#include <stddef.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "room.h"

static struct rooms * get(char * buffer);

int room_add(char * room_desc)
{
  char buffer[200];

  sprintf(buffer, "INSERT INTO Room (room_description) VALUES ('%s')", room_desc);
  db_query(buffer); 
  return 0;
}

struct rooms * get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct rooms * rooms;
  struct room * room;


  rooms = calloc(1, sizeof(struct rooms));
  list_init(&rooms->room_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * room_id = row[0];
    char * desc = row[1];

    printf("Id: %s\n",room_id);
    printf("Room desc: %s\n",desc);

    room = calloc(1, sizeof(struct room));
    list_init(&room->node);
    room->room_id = calloc(strlen(room_id) + 1, sizeof(char)); // 1 extra for null terminating output
    room->desc = calloc(strlen(desc) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(room->room_id, room_id, strlen(room_id));
    strncpy(room->desc, desc, strlen(desc));

    room->room_id[strlen(room_id)] = '\0';
    room->desc[strlen(desc)] = '\0';

    list_push_back(&rooms->room_list, &room->node);    
  }

  mysql_free_result(res);
  return rooms;
}

struct rooms * rooms_get_all()
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Room");
  return get(buffer);
}

struct rooms * rooms_get(char * room_desc)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Room where room_description = '%s'", room_desc);
  return get(buffer);
}

int room_delete(struct room * room)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Room where room_id = '%s'", room->room_id);
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
