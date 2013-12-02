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
#include "price.h"
#include "listing.h"
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
  struct items * items = items_get("1234", "sweater", "1", "0.99");

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
  items = items_get("1234", "sweater", "1", "0.99");

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

  struct clothing * cloth;

  item_clothing_add("234", "my morning jacket", "2", "10.99", "structure", "M");

  cloth = item_clothing_get("234", "my morning jacket", "2", "10.99");

  STRCMP_EQUAL(cloth->item.upc, "234");
  STRCMP_EQUAL(cloth->item.desc, "my morning jacket");
  STRCMP_EQUAL(cloth->item.quantity, "2");
  STRCMP_EQUAL(cloth->item.purchase_price, "10.99");
  STRCMP_EQUAL(cloth->clothing_brand, "structure");
  STRCMP_EQUAL(cloth->size, "M");

  item_clothing_delete(cloth);

  struct bathbody * bb;

  item_bathbody_add("345", "soap", "5", "10.99", "dove", "cleans well");

  bb = item_bathbody_get("345", "soap", "5", "10.99");

  STRCMP_EQUAL(bb->item.upc, "345");
  STRCMP_EQUAL(bb->item.desc, "soap");
  STRCMP_EQUAL(bb->item.quantity, "5");
  STRCMP_EQUAL(bb->item.purchase_price, "10.99");
  STRCMP_EQUAL(bb->bathbody_brand, "dove");
  STRCMP_EQUAL(bb->feature, "cleans well");

  item_bathbody_delete(bb);
}

TEST(db_test, price_put_get_mod_del)
{
  struct prices * prices;
  struct price * price;

  price_add_bid("4.99");
  prices = prices_get_all();

  LIST_FOR_EACH(price, struct price, node , &prices->price_list)
  {
    STRCMP_EQUAL(price->type_of_price, "bid");
    STRCMP_EQUAL(price->sell_price, "4.99");
  }

  prices_delete(prices);

  price_add_buy_now("9.99");
  prices = prices_get_all();

  LIST_FOR_EACH(price, struct price, node , &prices->price_list)
  {
    STRCMP_EQUAL(price->type_of_price, "buy now");
    STRCMP_EQUAL(price->sell_price, "9.99");
  }

  prices_delete(prices);
}

TEST(db_test, listing_put_get_mod_del)
{
  struct prices * prices;
  struct items * items;
  struct listings * listings;
  struct price * price;
  struct item * item;
  struct listing * listing;

  price_add_bid("10.99");
  item_add("678", "yoyo", "5", "1.99");

  prices = prices_get_all();
  items = items_get("678", "yoyo", "5", "1.99");

  LIST_FOR_EACH(price, struct price, node, &prices->price_list)
  {
    STRCMP_EQUAL(price->sell_price, "1.99");
    LIST_FOR_EACH(item, struct item, node, &items->item_list)
    {
      STRCMP_EQUAL(item->upc, "678");
      STRCMP_EQUAL(item->desc, "yoyo");
      STRCMP_EQUAL(item->quantity, "5");
      STRCMP_EQUAL(item->purchase_price, "1.99");

      listing_add(item->iid, price->price_id);

      listings = listings_get_all();

      LIST_FOR_EACH(listing, struct listing, node, &listings->listing_list)
      {
        STRCMP_EQUAL(item->iid, listing->iid);
        STRCMP_EQUAL(price->price_id, listing->price_id);
      }     
    }
  }

  prices_delete(prices);
  items_delete(items);
  listings_delete(listings);
}
