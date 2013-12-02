#include <stddef.h>
#include <stdbool.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "store.h"

int storing_add(char * iid, char * room_id)
{
  char buffer[200];
  sprintf(buffer, "INSERT INTO Store (iid, room_id) VALUES (%s, %s)", iid, room_id);
  db_query(buffer); 
  return 0;
}

struct storings * get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct storings * storings;
  struct storing * storing;

  storings = calloc(1, sizeof(struct storings));
  list_init(&storings->storing_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * iid = row[0];
    char * room_id = row[1];

    storing = calloc(1, sizeof(struct storing));
    list_init(&storing->node);
    storing->iid = calloc(strlen(iid) + 1, sizeof(char)); // 1 extra for null terminating output
    storing->room_id = calloc(strlen(room_id) + 1, sizeof(char)); // 1 extra for null terminating output
 
    strncpy(storing->iid, iid, strlen(iid));
    strncpy(storing->room_id, room_id, strlen(room_id));

    storing->iid[strlen(iid)] = '\0';
    storing->room_id[strlen(room_id)] = '\0';

    list_push_back(&storings->storing_list, &storing->node);    
  }

  mysql_free_result(res);
  return storings;
}

struct storings * storings_get_all()
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Store");
  return get(buffer);
}

int storing_delete(struct storing * storing)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Store where iid = '%s'", storing->iid);
  db_query(buffer); 
  return 0;
}


int storings_delete(struct storings * storings)
{
  struct storing * storing;
  LIST_FOR_EACH(storing, struct storing, node, &storings->storing_list)
  {
    storing_delete(storing);
  }

  return 0;
}
