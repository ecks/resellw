#ifndef ROOM_H
#define ROOM_H

struct rooms
{
  struct list roomer_list;
};

struct room
{
  char * room_id;
  char * desc;
};

struct roomer
{
  struct room room;
  struct list node;
};

#define R_LIST(ptr) (&ptr->roomer_list)

#define R_CONT(ptr) (CONTAINER_OF(ptr, struct roomer, node))

#define R_EACH(roomer, rooms) LIST_FOR_EACH(roomer, struct roomer, node, R_LIST(rooms))

extern int room_add(char *);
extern struct rooms * rooms_get_all();
extern struct rooms * rooms_get(char *);
extern struct rooms * rooms_get_room_id(char *);
extern struct roomer * room_get_room_id(char *);
extern int room_delete(struct roomer *);
extern int rooms_delete(struct rooms *);

#endif
