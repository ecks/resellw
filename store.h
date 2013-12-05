#ifndef STORE_H
#define STORE_H

struct storings
{
  struct list storing_list;
};

struct storing 
{
  struct list node;
  struct item item;
  struct room room;
};

struct item_rooms
{
  struct list item_room_list;
};

struct electronics_room
{
  struct list node;
  struct item item;
  struct elec elec;
  struct room room;
};

struct clothing_room 
{
  struct list node;
  struct item item;
  struct cloth cloth;
  struct room room;
};

struct bathbody_room
{
  struct list node;
  struct item item;
  struct bb bb;
  struct room room;
};

#define S_LIST(ptr) (&ptr->storing_list)
#define IR_LIST(ptr) (&ptr->item_room_list)

#define S_EACH(storing, storings) LIST_FOR_EACH(storing, struct storing, node, S_LIST(storings))

#define IR_EACH(itemer, item_rooms) LIST_FOR_EACH(itemer, struct itemer, node, IR_LIST(item_rooms))

extern int storing_add(char * iid, char * room_id);
extern struct storings * storings_get_all();
extern struct item_rooms * get_elec_model_storings(char * model);
extern struct item_rooms * get_cloth_brand_storings(char * clothing_brand);
extern struct item_rooms * get_bb_brand_storings(char * bathbody_brand);

extern int storing_modify(struct storing * storing, char * iid, char * room_id);
extern int storing_delete(struct storing * storing);
extern int storings_delete(struct storings * storings);

#endif
