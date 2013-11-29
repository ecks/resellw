#include <stddef.h>
#include <stdbool.h>

#include "util.h"
#include "io.h"
#include "list.h"
#include "item.h"
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
    menu_display_items(items);
  }
}

void client_menu_search_detailed()
{
  char * elec_model;
  char * clothing_brand;
  char * bathbody_brand;
  struct items * items;
  struct electronics * electronics;
  unsigned int detail_type;

  printf("Choose for the type of details you want to search by:\n");
  printf("1) Electronics model\n");
  printf("2) Clothing brand\n");
  printf("3) Bath and Body brand\n");
  detail_type = getchoice();

  switch(detail_type)
  {
    case 1:
      printf("Please enter Electronics model: ");
      elec_model = getline();
      items = items_electronics_get_model(elec_model);
      menu_display_items_electronics(items);
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