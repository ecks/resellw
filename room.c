#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
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
  struct roomer * roomer;


  rooms = calloc(1, sizeof(struct rooms));
  list_init(R_LIST(rooms));

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * room_id = row[0];
    char * desc = row[1];

    printf("Id: %s\n",room_id);
    printf("Room desc: %s\n",desc);

    roomer = calloc(1, sizeof(struct roomer));
    list_init(NODE(roomer));

    roomer->room.room_id = calloc(strlen(room_id) + 1, sizeof(char)); // 1 extra for null terminating output
    roomer->room.desc = calloc(strlen(desc) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(roomer->room.room_id, room_id, strlen(room_id));
    strncpy(roomer->room.desc, desc, strlen(desc));

    roomer->room.room_id[strlen(room_id)] = '\0';
    roomer->room.desc[strlen(desc)] = '\0';

    list_push_back(R_LIST(rooms), NODE(roomer));    
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

struct rooms * rooms_get_room_id(char * room_id)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Room where room_id = '%s'", room_id);
  return get(buffer);
}

struct roomer * room_get_room_id(char * room_id)
{  
  struct rooms * rooms;
  struct roomer * roomer;

  rooms = rooms_get_room_id(room_id);

  assert(list_size(R_LIST(rooms)) == 1);
  roomer = R_CONT(list_pop_front(R_LIST(rooms)));
  free(rooms);

  return roomer;
}

int room_delete(struct roomer * roomer)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Room where room_id = '%s'", roomer->room.room_id);
  db_query(buffer); 
  return 0;
}


int rooms_delete(struct rooms * rooms)
{
  struct roomer * roomer;
  R_EACH(roomer, rooms)
  {
    room_delete(roomer);
  }

  return 0;
}
