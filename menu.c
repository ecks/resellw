#include <stdlib.h>

#include "io.h"
#include "menu.h"

// items start

void menu_items_add()
{

}

void menu_items_modify()
{

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

}

void menu_rooms_delete()
{

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
