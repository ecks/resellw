#ifndef PRICE_H
#define PRICE_H

struct prices
{
  struct list price_list;
};

struct price
{
  char * price_id;
  char * type_of_price;
  char * sell_price;
  struct list node;
};

#define P_LIST(ptr) (&ptr->price_list)

#define P_CONT(ptr) (CONTAINER_OF(ptr, struct price, node))

struct listed_price
{
  struct item item;
  char * price_id;
  char * type_of_price;
  char * sell_price;
};

extern int price_add_bid(char * sell_price);
extern int price_add_buy_now(char * sell_price);
extern struct prices * prices_get_all();
extern struct prices * prices_get_price_id(char * price_id);
extern struct price * price_get_price_id(char * price_id);
extern struct prices * prices_get_range_sell_price(char * low_price, char * high_price);
extern struct prices * prices_get_range_sell_price_bid(char * low_price, char * high_price);
extern struct prices * prices_get_range_sell_price_buy_now(char * low_price, char * high_price);
extern int price_delete(struct price * price);
extern int prices_delete(struct prices * prices);

#endif
