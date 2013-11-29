#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "io.h"
#include "util.h"
#include "list.h"
#include "menu.h"
#include "room.h"
#include "item.h"

// items start

void menu_items_add()
{
  char * upc;
  char * desc;
  char * quantity;
  char * purchase_price;
  
  char * serial_num;
  char * electronic_type;
  char * model;

  char * clothing_brand;
  char * size;

  char * bathbody_brand;
  char * feature;

  char * details;
  unsigned int detail_type; 

  printf("UPC: ");
  upc = getline();
  printf("Description: ");
  desc = getline();
  printf("Quantity: ");
  quantity = getline();
  printf("Purchase Price: ");
  purchase_price = getline();

  printf("Do you want to add additional details? (y/n) ");
  details = getline();
  if(strcmp(details, "y") == 0)
  {
    printf("Choose for the type of details you want to provide for the item:\n");
    printf("1) Electronics\n");
    printf("2) Clothing\n");
    printf("3) Bath and Body\n");
    detail_type = getchoice();

    switch(detail_type)
    {
      case 1:
        printf("Serial Number: ");
        serial_num = getline();
        printf("Electronic Type: ");
        electronic_type = getline();
        printf("Model: ");
        model = getline();
        item_electronics_add(upc, desc, quantity, purchase_price, serial_num, electronic_type, model);
        break;

      case 2:
        printf("Clothing Brand: ");
        clothing_brand = getline();
        printf("Size: ");
        size = getline();
        item_clothing_add(upc, desc, quantity, purchase_price, clothing_brand, size);
        break;

      case 3:
        printf("Bath and Body Brand: ");
        bathbody_brand = getline();
        printf("Bath and Body Feature: ");
        feature = getline();
        item_bathbody_add(upc, desc, quantity, purchase_price, bathbody_brand, feature);
        break;
 
      default:
        printf("Unrecognized\n");
        break;
    }
  }
  else if(strcmp(details, "n") == 0)
  {
    item_add(upc, desc, quantity, purchase_price, NULL);
  }      

}

void menu_items_modify()
{
  struct items * items;
  char * show_info;

  printf("Do you want to show detailed information about each item? (y/n) ");
  show_info = getline();
  if(strcmp(show_info, "y") == 0)
  {
    items = items_get_all_detailed();
  }
  else if(strcmp(show_info, "n") == 0)
  {
    items = items_get_all();
  }
  else
  {
    printf("Unrecognized input\n");
  }
}

void menu_items_delete()
{

}

// items end

// rooms start

void menu_rooms_add()
{ 
  char * room_desc = NULL;
  printf("Room Description: ");
  room_desc = getline();
  printf("Room Description entered: %s", room_desc);
  room_add(room_desc);
}

void menu_rooms_modify()
{
/*  struct rooms * rooms = rooms_get_all();
  int i = 1;
  struct room * room;
  LIST_FOR_EACH(room, struct room, node, &rooms->room_list)
  {
    printf("%d) Room %s\n", i, room->desc);
  }
  printf("Please select the Room you want to modify\n"); */
}

void menu_rooms_delete()
{
  struct rooms * rooms = rooms_get_all();
  int i = 1;
  struct room * room;
  unsigned int choice;

  LIST_FOR_EACH(room, struct room, node, &rooms->room_list)
  {
    printf("%d) Room %s", i, room->desc);
    i++;
  }
  printf("%d) All Rooms\n", i);
  printf("Please select the Room you want to delete: ");
  if((choice = getchoice()) == 0)
    printf("No line\n");
  else
  {
    if(choice == i)
    {
      rooms_delete(rooms);
    }
    else
    {
      int j = 1;
      LIST_FOR_EACH(room, struct room, node, &rooms->room_list)
      {
        if(choice == j)
        {
          room_delete(room);
          break;
        } 
        j++;
      }
    }
  }
}

// rooms end

// prices start

void menu_prices_add()
{

}

void menu_prices_modify()
{

}

void menu_prices_delete()
{

}
// prices end


// storings start

void menu_storings_add()
{

}

void menu_storings_modify()
{

}

void menu_storings_delete()
{

}

// storings end


// listings start

void menu_listings_add()
{

}

void menu_listings_modify()
{

}

void menu_listings_delete()
{

}

// listings end

// top level start

void menu_add()
{
  unsigned int choice;

  printf("1) Add an Item\n");
  printf("2) Add a Room\n");
  printf("3) Add a Price\n");
  printf("4) Store an Item to a Room\n");
  printf("5) List an Item with a Price\n");
  if((choice = getchoice()) == 0)
    printf("No line\n");
  else
  {
    switch(choice)
    {
        case 1:
          printf("Asked to add an Item\n");
          menu_items_add();
          break;

        case 2:
          printf("Asked to add a Room\n");
          menu_rooms_add();
          break;

        case 3:
          printf("Asked to add a Price\n");
          menu_prices_add();
          break;

        case 4:
          printf("Asked to store an Item to a Room\n");
          menu_storings_add();
          break;
      
        case 5:
          printf("Asked to list an Item with a Price\n");
          menu_listings_add();
          break;

        default:
          printf("Unrecognized\n");
          break;
    } 
  }
}

void menu_modify()
{
  unsigned int choice;;

  printf("1) Modify an Item\n");
  printf("2) Modify a Room\n");
  printf("3) Modify a Price\n");
  printf("4) Move an Item to another Room\n");
  printf("5) Relist an Item with another Price\n");
  if((choice = getchoice()) == 0)
    printf("No line\n");
  else
  {
    switch(choice)
    {
        case 1:
          printf("Asked to modify an Item\n");
          menu_items_modify();
          break;

        case 2:
          printf("Asked to modify a Room\n");
          menu_rooms_modify();
          break;

        case 3:
          printf("Asked to modify a Price\n");
          menu_prices_modify();
          break;

        case 4:
          printf("Asked to move an Item to another Price\n");
          menu_storings_modify();
          break;

        case 5:
          printf("Asked to relist an Item with another Price\n");
          menu_listings_modify();
          break;
      
        default:
          printf("Unrecognized\n");
          break;
    } 
  }
}

void menu_delete()
{
  unsigned int choice;;

  printf("1) Delete an Item\n");
  printf("2) Delete a Room\n");
  printf("3) Delete a Price\n");
  printf("4) Remove an Item from a Room\n");
  printf("5) Take down an Item with a Price\n");
  if((choice = getchoice()) == 0)
    printf("No line\n");
  else
  {
    switch(choice)
    {
        case 1:
          printf("Asked to delete an Item\n");
          menu_items_delete();
          break;

        case 2:
          printf("Asked to delete a Room\n");
          menu_rooms_delete();
          break;

        case 3:
          printf("Asked to delete a Price\n");
          menu_prices_delete();
          break;


        case 4:
          printf("Asked to remove an Item from a Room\n");
          menu_rooms_delete();
          break;

        case 5:
          printf("Asked to take down an Item with a Price\n");
          menu_listings_delete();
          break;
      
        default:
          printf("Unrecognized\n");
          break;
    } 
  }
}

// top level end

void menu()
{
  char * line = NULL;
  size_t size;
  unsigned int choice;

  printf("Welcome to Reseller Warehouse Administrative System!\n");

  while(1)
  {
    printf("Please select from the following options:\n");
    printf("1) Add\n");
    printf("2) Modify\n");
    printf("3) Delete\n");
    printf("4) Quit\n");

    if((choice = getchoice()) == 0)
      printf("No line\n");
    else
    {
      switch(choice)
      {
        case 1:
          printf("Asked to add\n");
          menu_add();
          break;

        case 2:
          printf("Asked to modify\n");
          menu_modify();
          break;


        case 3:
          printf("Asked to delete\n");
          menu_delete();
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
