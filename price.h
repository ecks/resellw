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

struct pricer
{
  struct list node;
  struct price price;
};

#define P_LIST(ptr) (&ptr->price_list)

#define P_CONT(ptr) (CONTAINER_OF(ptr, struct price, node))

extern int price_add_bid(char * sell_price);
extern int price_add_buy_now(char * sell_price);
extern struct prices * prices_get_all();
extern struct prices * prices_get_price_id(char * price_id);
extern struct price * price_get_price_id(char * price_id);
extern int price_delete(struct price * price);
extern int prices_delete(struct prices * prices);

#endif
