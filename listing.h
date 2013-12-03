#ifndef LISTING_H
#define LISTING_H

struct listings
{
  struct list listing_list;
};

struct listing
{
  char * iid;
  char * price_id;
  struct list node;
};

#define L_LIST(ptr) (&ptr->listing_list)

extern int listing_add(char * iid, char * price_id);
extern struct listings * listings_get_all();
extern int listing_delete(struct listing * listing);
extern int listings_delete(struct listings * listings);

#endif
