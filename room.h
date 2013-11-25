#ifndef ROOM_H
#define ROOM_H

struct rooms
{
  struct list room_list;
};

struct room
{
  char * id;
  char * desc;
  struct list node;
};

extern int room_add(char * room_desc);
extern struct rooms * rooms_get(char * room_desc);
extern int room_delete(struct room * room);
extern int rooms_delete(struct rooms * rooms);

#endif
