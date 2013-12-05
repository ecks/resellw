#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "room.h"
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
  struct pricer * pricer;


  prices = calloc(1, sizeof(struct prices));
  list_init(&prices->price_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * price_id = row[0];
    char * type_of_price = row[1];
    char * sell_price = row[2];

    pricer = calloc(1, sizeof(struct pricer));
    list_init(&pricer->node);

    pricer->price.price_id = calloc(strlen(price_id) + 1, sizeof(char)); // 1 extra for null terminating output
    pricer->price.type_of_price = calloc(strlen(type_of_price) + 1, sizeof(char)); // 1 extra for null terminating output
    pricer->price.sell_price = calloc(strlen(sell_price) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(pricer->price.price_id, price_id, strlen(price_id));
    strncpy(pricer->price.type_of_price, type_of_price, strlen(type_of_price));
    strncpy(pricer->price.sell_price, sell_price, strlen(sell_price));

    pricer->price.price_id[strlen(price_id)] = '\0';
    pricer->price.type_of_price[strlen(type_of_price)] = '\0';
    pricer->price.sell_price[strlen(sell_price)] = '\0';

    list_push_back(&prices->price_list, &pricer->node);    
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

struct prices * prices_get_price_id(char * price_id)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Price where price_id = '%s'", price_id);
  return get(buffer);
}

struct price * price_get_price_id(char * price_id)
{  
  struct prices * prices;
  struct pricer * pricer;

  prices = prices_get_price_id(price_id);

  assert(list_size(P_LIST(prices)) == 1);
  pricer = P_CONT(list_pop_front(&prices->price_list));
  free(prices);

  return &pricer->price;
}

int price_modify(struct price * price, char * column, char * value)
{
  char buffer[200];
  sprintf(buffer, "UPDATE Price SET %s='%s' WHERE price_id=%s", column, value, price->price_id);
  db_query(buffer);
  return 0;
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
  struct pricer * pricer;
  P_EACH(pricer, prices)
  {
    price_delete(&pricer->price);
  }

  return 0;
}

