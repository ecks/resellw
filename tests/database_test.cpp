extern "C"
{
#include <stdbool.h>
#include <stddef.h>
#include <mysql.h>

#include "util.h"
#include "list.h"
#include "db.h"
#include "room.h"
}

#include "CppUTest/TestHarness.h" 

TEST_GROUP(db_test)
{
  void setup()
  {
    db_init();
  }
  void teardown()
  {
    db_close();
  }
};

TEST(db_test, room_put_get)
{
  room_add("1");
  struct rooms * rooms = rooms_get("1");

  struct room * room;
  LIST_FOR_EACH(room, struct room, node, &rooms->room_list)
  {
    STRCMP_EQUAL("1", room->desc);
  }
  rooms_delete(rooms);
}
