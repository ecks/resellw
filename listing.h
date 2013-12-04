#ifndef LISTING_H
#define LISTING_H

struct listings
{
  struct list listing_list;
};

struct listing
{
  struct list node;
  struct item item;
  struct price price;
};

#define L_LIST(ptr) (&ptr->listing_list)

#define L_EACH(listing, listings) LIST_FOR_EACH(listing, struct listing, node, L_LIST(listings))

extern int listing_add(char * iid, char * price_id);
extern struct listings * listings_get_all();
extern struct listings * get_range_sell_price_listings_bid(char * low_price, char * high_price);
extern struct listings * get_range_sell_price_listings_buy_now(char * low_price, char * high_price);
extern struct listings * get_range_sell_price_listings(char * low_price, char * high_price);
extern int listing_delete(struct listing * listing);
extern int listings_delete(struct listings * listings);

#endif
