#include <stddef.h>
#include <stdbool.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "item.h"
#include "price.h"
#include "listing.h"

static struct listings * get(char * buffer);

int listing_add(char * iid, char * price_id)
{
  char buffer[200];
  int error;

  sprintf(buffer, "INSERT INTO List (iid, price_id) VALUES (%s, %s)", iid, price_id);
  if((error = db_query(buffer)) == 1062)
  {
    printf("You cannot list a Price for more than one Item\n");
    return 1;   
  }
  return 0;
}

struct listings * item_list_price_get(char * buffer)
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
    char * price_id = row[0];

    char * iid = row[1];
    char * upc = row[2];
    char * description = row[3];
    char * quantity = row[4];
    char * purchase_price = row[5];
    char * detail = row[6];

    char * type_of_price = row[8];
    char * sell_price = row[9];

    listing = calloc(1, sizeof(struct listing));
    list_init(&listing->node);

    listing->price.price_id = calloc(strlen(price_id) + 1, sizeof(char)); // 1 extra for null terminating output

    listing->item.iid = calloc(strlen(iid) + 1, sizeof(char)); // 1 extra for null terminating output
    listing->item.upc = calloc(strlen(upc) + 1, sizeof(char)); // 1 extra for null terminating output
    listing->item.desc = calloc(strlen(description) + 1, sizeof(char)); // 1 extra for null terminating output
    listing->item.quantity = calloc(strlen(quantity) + 1, sizeof(char)); // 1 extra for null terminating output
    listing->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char)); // 1 extra for null terminating output
    
    listing->price.type_of_price = calloc(strlen(type_of_price) + 1, sizeof(char)); // 1 extra for null terminating output
    listing->price.sell_price = calloc(strlen(sell_price) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(listing->price.price_id, price_id, strlen(price_id));

    strncpy(listing->item.iid, iid, strlen(iid));
    strncpy(listing->item.upc, upc, strlen(upc));
    strncpy(listing->item.desc, description, strlen(description));
    strncpy(listing->item.quantity, quantity, strlen(quantity));
    strncpy(listing->item.purchase_price, purchase_price, strlen(purchase_price));

    strncpy(listing->price.type_of_price, type_of_price, strlen(type_of_price));
    strncpy(listing->price.sell_price, sell_price, strlen(sell_price));

    listing->price.price_id[strlen(price_id)] = '\0';

    listing->item.iid[strlen(iid)] = '\0';
    listing->item.upc[strlen(upc)] = '\0';
    listing->item.desc[strlen(description)] = '\0';
    listing->item.quantity[strlen(quantity)] = '\0';
    listing->item.purchase_price[strlen(purchase_price)] = '\0';

    listing->price.type_of_price[strlen(type_of_price)] = '\0';
    listing->price.sell_price[strlen(sell_price)] = '\0';

    list_push_back(&listings->listing_list, &listing->node);    
  }

  mysql_free_result(res);
  return listings;
}

struct listings * listings_get_all()
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join List natural join Price");
  return item_list_price_get(buffer);
}

struct listings * get_range_sell_price_listings_bid(char * low_price, char * high_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join List natural join Price where sell_price BETWEEN %s AND %s AND type_of_price='bid'", low_price, high_price);
  return item_list_price_get(buffer);
}

struct listings * get_range_sell_price_listings_buy_now(char * low_price, char * high_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join List natural join Price where sell_price BETWEEN %s AND %s AND type_of_price='buy now'", low_price, high_price);
  return item_list_price_get(buffer);
}

struct listings * get_range_sell_price_listings(char * low_price, char * high_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join List natural join Price where sell_price BETWEEN %s AND %s", low_price, high_price);
  return item_list_price_get(buffer);
}

int listing_modify(struct listing * listing, char * iid, char * price_id)
{
  char buffer[200];
  int error;

  sprintf(buffer, "Update List SET iid=%s, price_id=%s where price_id = '%s'", iid, price_id, listing->price.price_id);
  if((error = db_query(buffer)) == 1062)
  {
    printf("You cannot list a Price for more than one Item\n");
    return 1;   
  }

  return 0;
}

int listing_delete(struct listing * listing)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM List where price_id = '%s'", listing->price.price_id);
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
