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

struct electronics_room
{
  struct item item;
  struct elec elec;
  struct room room;
};

struct clothing_room 
{
  struct item item;
  struct cloth cloth;
  struct room room;
};

struct bathbody_room
{
  struct item item;
  struct bb bb;
  struct room room;
};

#define S_LIST(ptr) (&ptr->storing_list)

extern int storing_add(char * iid, char * room_id);
extern struct storings * storings_get_all();
extern struct items * get_model_storings(char * model);

extern int storing_delete(struct storing * storing);
extern int storings_delete(struct storings * storings);

#endif
