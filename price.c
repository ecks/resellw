#include <stddef.h>
#include <stdbool.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "item.h"
#include "price.h"

static struct prices * get(char * buffer);
static struct prices * listed_get(char * buffer);

int price_add_bid(char * sell_price)
{
  char buffer[200];

  sprintf(buffer, "INSERT INTO Price (type_of_price, sell_price) VALUES ('%s', %s)", "bid", sell_price);
  db_query(buffer); 
  return 0;
}

int price_add_buy_now(char * sell_price)
{
  char buffer[200];

  sprintf(buffer, "INSERT INTO Price (type_of_price, sell_price) VALUES ('%s', %s)", "buy now", sell_price);
  db_query(buffer); 
  return 0;
}

struct prices * get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct prices * prices;
  struct price * price;


  prices = calloc(1, sizeof(struct prices));
  list_init(&prices->price_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * price_id = row[0];
    char * type_of_price = row[1];
    char * sell_price = row[2];

    price = calloc(1, sizeof(struct price));
    list_init(&price->node);

    price->price_id = calloc(strlen(price_id) + 1, sizeof(char)); // 1 extra for null terminating output
    price->type_of_price = calloc(strlen(type_of_price) + 1, sizeof(char)); // 1 extra for null terminating output
    price->sell_price = calloc(strlen(sell_price) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(price->price_id, price_id, strlen(price_id));
    strncpy(price->type_of_price, type_of_price, strlen(type_of_price));
    strncpy(price->sell_price, sell_price, strlen(sell_price));

    price->price_id[strlen(price_id)] = '\0';
    price->type_of_price[strlen(type_of_price)] = '\0';
    price->sell_price[strlen(sell_price)] = '\0';

    list_push_back(&prices->price_list, &price->node);    
  }

  mysql_free_result(res);
  return prices;
}

struct prices * listed_get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct prices * prices;
  struct listed_price * l_price;


  prices = calloc(1, sizeof(struct prices));
  list_init(&prices->price_list);

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

    char * type_of_price = row[7];
    char * sell_price = row[8];

    l_price = calloc(1, sizeof(struct listed_price));
    list_init(&l_price->item.node);

    l_price->price_id = calloc(strlen(price_id) + 1, sizeof(char)); // 1 extra for null terminating output

    l_price->item.iid = calloc(strlen(iid) + 1, sizeof(char)); // 1 extra for null terminating output
    l_price->item.upc = calloc(strlen(upc) + 1, sizeof(char)); // 1 extra for null terminating output
    l_price->item.desc = calloc(strlen(description) + 1, sizeof(char)); // 1 extra for null terminating output
    l_price->item.quantity = calloc(strlen(quantity) + 1, sizeof(char)); // 1 extra for null terminating output
    l_price->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char)); // 1 extra for null terminating output
    
    l_price->type_of_price = calloc(strlen(type_of_price) + 1, sizeof(char)); // 1 extra for null terminating output
    l_price->sell_price = calloc(strlen(sell_price) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(l_price->price_id, price_id, strlen(price_id));

    strncpy(l_price->item.iid, iid, strlen(iid));
    strncpy(l_price->item.upc, upc, strlen(upc));
    strncpy(l_price->item.desc, description, strlen(description));
    strncpy(l_price->item.quantity, quantity, strlen(quantity));
    strncpy(l_price->item.purchase_price, purchase_price, strlen(purchase_price));

    strncpy(l_price->type_of_price, type_of_price, strlen(type_of_price));
    strncpy(l_price->sell_price, sell_price, strlen(sell_price));

    l_price->price_id[strlen(price_id)] = '\0';

    l_price->item.iid[strlen(iid)] = '\0';
    l_price->item.upc[strlen(upc)] = '\0';
    l_price->item.desc[strlen(description)] = '\0';
    l_price->item.quantity[strlen(quantity)] = '\0';
    l_price->item.purchase_price[strlen(purchase_price)] = '\0';

    l_price->type_of_price[strlen(type_of_price)] = '\0';
    l_price->sell_price[strlen(sell_price)] = '\0';

    list_push_back(&prices->price_list, &l_price->item.node);    
  }

  mysql_free_result(res);
  return prices;
}

struct prices * prices_get_all()
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Price");
  return get(buffer);
}

struct prices * prices_get_range_sell_price(char * low_price, char * high_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join List natural join Price where sell_price BETWEEN %s AND %s", low_price, high_price);
  return listed_get(buffer);
}

struct prices * prices_get_range_sell_price_bid(char * low_price, char * high_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join List natural join Price where sell_price BETWEEN %s AND %s AND type_of_price='bid'", low_price, high_price);
  return listed_get(buffer);
}

struct prices * prices_get_range_sell_price_buy_now(char * low_price, char * high_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join List natural join Price where sell_price BETWEEN %s AND %s AND type_of_price='buy now'", low_price, high_price);
  return listed_get(buffer);
}
int price_delete(struct price * price)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Price where price_id = '%s'", price->price_id);
  db_query(buffer); 
  return 0;
}

int prices_delete(struct prices * prices)
{
  struct price * price;
  LIST_FOR_EACH(price, struct price, node, &prices->price_list)
  {
    price_delete(price);
  }

  return 0;
}

