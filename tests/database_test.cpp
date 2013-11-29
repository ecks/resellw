extern "C"
{
#include <stdbool.h>
#include <stddef.h>
#include <mysql.h>

#include "util.h"
#include "list.h"
#include "db.h"
#include "room.h"
#include "item.h"
#include "store.h"
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

TEST(db_test, room_put_get_mod_del)
{
  room_add("1");
  struct rooms * rooms = rooms_get_all();

  struct room * room;
  LIST_FOR_EACH(room, struct room, node, &rooms->room_list)
  {
    STRCMP_EQUAL("1", room->desc);
  }
  rooms_delete(rooms);
}

TEST(db_test, item_put_get_mod_del)
{
  item_add("1234", "sweater", "1", "0.99", NULL);
  struct items * items = items_get_all();

  struct item * item;
  LIST_FOR_EACH(item, struct item, node, &items->item_list)
  {
    STRCMP_EQUAL("1234", item->upc);
    STRCMP_EQUAL("sweater", item->desc);
    STRCMP_EQUAL("1", item->quantity);
    STRCMP_EQUAL("0.99", item->purchase_price);
  }
  items_delete(items);
}

TEST(db_test, storing_put_get_mod_del)
{
  struct rooms * rooms;
  struct items * items;
  struct storings * storings;

  room_add("1");
  item_add("1234", "sweater", "1", "0.99", NULL);

  rooms = rooms_get_all();
  items = items_get_all();

  struct room * room;
  LIST_FOR_EACH(room, struct room, node, &rooms->room_list)
  {
    STRCMP_EQUAL("1", room->desc);

    struct item * item;
    LIST_FOR_EACH(item, struct item, node, &items->item_list)
    {
      STRCMP_EQUAL("1234", item->upc);
      STRCMP_EQUAL("sweater", item->desc);
      STRCMP_EQUAL("1", item->quantity);
      STRCMP_EQUAL("0.99", item->purchase_price);

      storing_add(item->iid, room->room_id);

      storings = storings_get_all();

      struct storing * storing;
      LIST_FOR_EACH(storing, struct storing, node, &storings->storing_list)
      {
        STRCMP_EQUAL(item->iid, storing->iid);
        STRCMP_EQUAL(room->room_id, storing->room_id);
      }
    }
  }
 
  rooms_delete(rooms);
  items_delete(items);
  storings_delete(storings);
}

TEST(db_test, item_elect_cloth_bathbody)
{
  struct electronics * elec;

  item_electronics_add("1234", "my monitor", "1", "0.99", "123", "monitor", "dell d12");

  elec = item_electronics_get("1234", "my monitor", "1", "0.99");

  STRCMP_EQUAL(elec->item.upc, "1234");
  STRCMP_EQUAL(elec->item.desc, "my monitor");
  STRCMP_EQUAL(elec->item.quantity, "1");
  STRCMP_EQUAL(elec->item.purchase_price, "0.99");
  STRCMP_EQUAL(elec->serial_number, "123");
  STRCMP_EQUAL(elec->electronic_type, "monitor");
  STRCMP_EQUAL(elec->model, "dell d12");

  item_electronics_delete(elec);
}
