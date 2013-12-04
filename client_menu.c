#include <stddef.h>
#include <stdbool.h>

#include "util.h"
#include "io.h"
#include "list.h"
#include "room.h"
#include "item.h"
#include "price.h"
#include "store.h"
#include "listing.h"
#include "menu_common.h"
#include "client_menu.h"

void client_menu_search_upc()
{
  char * upc;
  struct item * item;
  struct items * items;

  printf("Please enter the UPC Code: ");
  upc = getline();
  items = items_get_upc(upc);

  if(list_empty(&items->item_list))
  {
    printf("No items found!\n");
  }
  else
  {
    int i = 1;
    menu_display_items(items, &i);
  }
}

void client_menu_search_detailed()
{
  char * elec_model;
  char * clothing_brand;
  char * bathbody_brand;
  struct item_rooms * item_rooms;
  struct electronics * electronics;
  unsigned int detail_type;

  printf("1) Electronics model\n");
  printf("2) Clothing brand\n");
  printf("3) Bath and Body brand\n");
  printf("Choose for the type of details you want to search by:\n");
  detail_type = getchoice();

  switch(detail_type)
  {
    case 1:
      printf("Please enter Electronics model: ");
      elec_model = getline();
      item_rooms = get_elec_model_storings(elec_model);
      menu_display_items_rooms_detailed(item_rooms);
      break;

    case 2:
      printf("Please enter Clothing brand: ");
      clothing_brand = getline();
      break;

    case 3:
      printf("Please enter Bath and Body brand: ");
      bathbody_brand = getline();
      break;

    default:
      break;
      
  }
}

void client_menu_search_price()
{
  struct prices * prices;
  struct listed_price * l_price;
  char * low_price;
  char * high_price;
  unsigned int type_of_price;

  printf("Please enter lowest price range: ");
  low_price = getline();
  printf("Please enter highest price range: ");
  high_price = getline();

  printf("1) Don't care\n");
  printf("2) Bid\n");
  printf("3) Buy Now\n");
  printf("Please select the type of price you want to search by: \n");
  type_of_price = getchoice();

  switch(type_of_price)
  {
    case 1:
      prices = get_range_sell_price_listings(low_price, high_price);
      break;

    case 2:
      prices = get_range_sell_price_listings_bid(low_price, high_price);
      break;

    case 3:
      prices = get_range_sell_price_listings_buy_now(low_price, high_price);
      break;

    default:
      printf("Unknown choice");
      return;
  }
  LIST_FOR_EACH(l_price, struct listed_price, item.node, &prices->price_list)
  {
    printf("Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s, Type of Sell: %s, Sell Price: %s\n", 
           l_price->item.upc, l_price->item.desc, l_price->item.quantity, l_price->item.purchase_price, l_price->type_of_price, l_price->sell_price);
  }
}

void client_menu()
{
  unsigned int choice;

  printf("Welcome, Reseller Warehouse client!\n");

  while(1)
  {
    printf("Please select from the following options:\n");
    printf("1) Search for an Item by UPC Code\n");
    printf("2) Search for an Item by Detailed Information\n");
    printf("3) Search for an Item by a Price Range\n");
    printf("4) Quit\n");

    if((choice = getchoice()) == 0)
      printf("No line\n");
    else
    {
      switch(choice)
      {
        case 1:
          client_menu_search_upc();
          break;

        case 2:
          client_menu_search_detailed();
          break;

        case 3:
          client_menu_search_price();
          break;

        case 4:
          printf("Bye\n");
          exit(0);
          break;

        default:
          printf("Unrecognized\n");
          break;

      }
    }
  }
}
