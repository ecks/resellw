#include <stddef.h>
#include <stdbool.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "listing.h"

static struct listings * get(char * buffer);

int listing_add(char * iid, char * price_id)
{
  char buffer[200];
  sprintf(buffer, "INSERT INTO List (iid, price_id) VALUES (%s, %s)", iid, price_id);
  db_query(buffer); 
  return 0;
}

struct listings * get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct listings * listings;
  struct listing * listing;

  listings = calloc(1, sizeof(struct listings));
  list_init(&listings->listing_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * iid = row[0];
    char * price_id = row[1];

    listing = calloc(1, sizeof(struct listing));
    list_init(&listing->node);
    listing->iid = calloc(strlen(iid) + 1, sizeof(char)); // 1 extra for null terminating output
    listing->price_id = calloc(strlen(price_id) + 1, sizeof(char)); // 1 extra for null terminating output
 
    strncpy(listing->iid, iid, strlen(iid));
    strncpy(listing->price_id, price_id, strlen(price_id));

    listing->iid[strlen(iid)] = '\0';
    listing->price_id[strlen(price_id)] = '\0';

    list_push_back(&listings->listing_list, &listing->node);    
  }

  mysql_free_result(res);
  return listings;
}

struct listings * listings_get_all()
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM List");
  return get(buffer);
}

int listing_delete(struct listing * listing)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM List where price_id = '%s'", listing->price_id);
  db_query(buffer); 
  return 0;
}


int listings_delete(struct listings * listings)
{
  struct listing * listing;
  LIST_FOR_EACH(listing, struct listing, node, &listings->listing_list)
  {
    listing_delete(listing);
  }

  return 0;
}
