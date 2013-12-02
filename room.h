#ifndef ROOM_H
#define ROOM_H

struct rooms
{
  struct list room_list;
};

struct room
{
  char * room_id;
  char * desc;
  struct list node;
};

struct room_m
{
  char * room_id;
  char * desc;
};

extern int room_add(char * room_desc);
extern struct rooms * rooms_get_all();
extern struct rooms * rooms_get(char * room_desc);
extern int room_delete(struct room * room);
extern int rooms_delete(struct rooms * rooms);

#endif
