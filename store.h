#ifndef STORE_H
#define STORE_H

struct storings
{
  struct list storing_list;
};

struct storing 
{
  char * iid;
  char * room_id;
  struct list node;
};

extern int storing_add(char * iid, char * room_id);
extern struct storings * storings_get_all();

extern int storing_delete(struct storing * storing);
extern int storings_delete(struct storings * storings);

#endif
