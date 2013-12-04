#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "io.h"
#include "util.h"
#include "list.h"
#include "room.h"
#include "item.h"
#include "price.h"
#include "store.h"
#include "listing.h"
#include "menu_common.h"
#include "admin_menu.h"

// items start

void admin_menu_items_add()
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

void admin_menu_display_item_choice(struct item * item)
{
  unsigned int choice;
  char * upc;
  char * desc;
  char * quantity;
  char * purchase_price;

  printf("1) UPC\n");
  printf("2) Description\n");
  printf("3) Quantity\n");
  printf("4) Purchase Price\n");
  printf("Please select column of Item you would like to modify: ");
  if((choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }
  switch (choice)
  {
    case 1:
      printf("New UPC value: ");
      upc = getline();
      item_modify(item, "upc", upc);
      break;

    case 2:
      printf("New Description value: ");
      desc = getline();
      item_modify(item, "description", desc);
      break;

    case 3:
      printf("New Quantity value: ");
      quantity = getline();
      item_modify(item, "quantity", quantity);
      break;

    case 4:
      printf("New Purchase Price value: ");
      purchase_price = getline();
      item_modify(item, "purchase_price", purchase_price);
      break;

    default:
      printf("Not a valid choice");
      return;
  }
}

void admin_menu_display_item_choice_detailed(struct item * item)
{
  unsigned int choice;

  char * serial_number;
  char * elec_type;
  char * model;

  char * clothing_brand;
  char * size;

  char * bathbody_brand;
  char * feature;

  if(item->detail == NULL)
  {
    printf("No detailed information found!\n");
    return;  
  }
  else
  {
    if(strcmp(item->detail, "elec") == 0)
    {
      printf("1) Serial number\n");
      printf("2) Electronic type\n");
      printf("3) Model\n");
      printf("Please select column of Item you would like to modify: ");
      if((choice = getchoice()) == 0)
      {
        printf("No line\n");
        return;
      }
      switch (choice)
      {
        case 1:
          printf("New Serial Number value: ");
          serial_number = getline();
          item_elec_modify(item, "serial_number", serial_number);
          break;

        case 2:
          printf("New Electronic Type value: ");
          elec_type = getline();
          item_elec_modify(item, "electronic_type", elec_type);
          break;

        case 3:
          printf("New Model value: ");
          model = getline();
          item_elec_modify(item, "model", model);
          break;

        default:
          printf("Not a valid choice");
          return;
       }
    }
    if(strcmp(item->detail, "clothing") == 0)
    {
      printf("1) Clothing Brand\n");
      printf("2) Size\n");
      printf("Please select column of Item you would like to modify: ");
      if((choice = getchoice()) == 0)
      {
        printf("No line\n");
        return;
      }
      switch (choice)
      {
        case 1:
          printf("New Clothing Brand value: ");
          clothing_brand = getline();
          item_clothing_modify(item, "clothing_brand", clothing_brand);
          break;

        case 2:
          printf("New Size value: ");
          size = getline();
          item_clothing_modify(item, "size", size);
          break;

        default:
          printf("Not a valid choice");
          return;
      }
    }
    if(strcmp(item->detail, "bathbody") == 0)
    {
      printf("1) Bath and Body Brand\n");
      printf("2) Feature\n");
      printf("Please select column of Item you would like to modify: ");
      if((choice = getchoice()) == 0)
      {
        printf("No line\n");
        return;
      }
      switch (choice)
      {
        case 1:
          printf("New Bath and Body Brand value: ");
          bathbody_brand = getline();
          item_bathbody_modify(item, "bathbody_brand", bathbody_brand);
          break;

        case 2:
          printf("New Feature value: ");
          feature = getline();
          item_bathbody_modify(item, "feature", feature);
          break;

        default:
          printf("Not a valid choice");
          return;
      }
    }
  }
}

void admin_menu_items_modify()
{
  unsigned int choice;
  struct items * items;
  struct itemer * itemer;
  char * show_info;
  char * modify_info;
  bool detail;

  printf("Do you want to show detailed information about each item? (y/n) ");
  show_info = getline();
  if(strcmp(show_info, "y") == 0)
  {
    items = items_get_all_detailed();
    menu_display_items_detailed(items);
  }
  else if(strcmp(show_info, "n") == 0)
  {
    items = items_get_all();
    int i = 1;
    menu_display_items(items, &i);
  }
  else
  {
    printf("Unrecognized input\n");
    return;
  }
  printf("Please select the Item you want to modify: ");
  if((choice = getchoice()) == 0)
    printf("No line\n");
  else
  {
    printf("Do you want to modify detailed information? (y/n) ");
    modify_info = getline();
    if(strcmp(modify_info, "y") == 0)
    {
      detail = true;
    }
    else if(strcmp(modify_info, "n") == 0)
    {
      detail = false;
    }
    else
    {
      printf("Unrecognized input");
      return;
    }
 
    int j = 1;
    I_EACH(itemer, items)
    {
      if(choice == j)
      {
        if(detail == true)
        {
          admin_menu_display_item_choice_detailed(&itemer->item);  
        }
        else
        {
          admin_menu_display_item_choice(&itemer->item);
        }
      }
      j++;
    }
  }  
}

void admin_menu_items_delete()
{
  struct items * items;
  struct itemer * itemer;
  int i = 1;
  unsigned int choice;

  items = items_get_all();
  menu_display_items(items, &i);

  printf("%d) All Items\n", i);
  printf("Please select the Item you want to delete: ");
  if((choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }
  else
  {
    if(choice == i)
    {
      items_delete(items);
    }
    else
    {
      int j = 1;
      I_EACH(itemer, items)
      {
        if(choice == j)
        {
          item_delete(&itemer->item);
          break;
        } 
        j++;
      }
    }
  }
}

// items end

// rooms start

void admin_menu_rooms_add()
{ 
  char * room_desc = NULL;
  printf("Room Description: ");
  room_desc = getline();
  room_add(room_desc);
}

void admin_menu_rooms_modify()
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

void admin_menu_rooms_delete()
{
  struct rooms * rooms = rooms_get_all();
  int i = 1;
  struct roomer * roomer;
  unsigned int choice;

  menu_display_rooms(rooms, &i);

  printf("%d) All Rooms\n", i);
  printf("Please select the Room you want to delete: ");
  if((choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }
  else
  {
    if(choice == i)
    {
      rooms_delete(rooms);
    }
    else
    {
      int j = 1;
      R_EACH(roomer, rooms)
      {
        if(choice == j)
        {
          room_delete(roomer);
          break;
        } 
        j++;
      }
    }
  }
}

// rooms end

// prices start

void admin_menu_prices_add()
{
  char * sell_price;
  unsigned int choice;

  printf("1) Bid\n");
  printf("2) Buy Now\n");
  printf("Please select type of price: ");
  if((choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }
  else
  {
    printf("Sell Price: ");
    sell_price = getline();

    switch(choice)
    {
      case 1:
        price_add_bid(sell_price);
        break;

      case 2:
        price_add_buy_now(sell_price);
        break;

      default:
        printf("Unrecognized input\n");
        return;
    }
  }
}

void admin_menu_prices_modify()
{

}

void admin_menu_prices_delete()
{
  struct prices * prices;
  struct price * price;
  unsigned int choice;

  int i = 1;

  prices = prices_get_all();
  menu_display_prices(prices, &i);

  printf("%d) All Prices\n", i);
  printf("Please select the Price you want to delete: ");
  if((choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }
  else
  {
    if(choice == i)
    {
      prices_delete(prices);
    }
    else
    {
      int j = 1;
      LIST_FOR_EACH(price, struct price, node, &prices->price_list)
      {
        if(choice == j)
        {
          price_delete(price);
          break;
        } 
        j++;
      }
    }
  }
}
// prices end


// storings start

void admin_menu_storings_add()
{
  struct items * items;
  struct itemer * itemer;
  struct rooms * rooms;
  struct roomer * roomer;

  unsigned int item_choice;
  unsigned int room_choice;

  int i = 1;
  int j = 1;

  items = items_get_all();
  if(list_empty(I_LIST(items)))
  {
    printf("No Items found, please add an item before storing it in a Room\n");
    return;
  }

  rooms = rooms_get_all();
  if(list_empty(R_LIST(rooms)))
  {
    printf("No Rooms found, please add a Room so you can store Items in it\n");
    return;
  }

  menu_display_items(items, &i);
  printf("Please select item: ");
  if((item_choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }

  menu_display_rooms(rooms, &j);
  printf("Please select Room: ");
  if((room_choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }

  i = 1;
  I_EACH(itemer, items)
  {
    if(item_choice == i)
    {
      j = 1;
      R_EACH(roomer, rooms)
      {
        if(room_choice == j)
        {
          storing_add(itemer->item.iid, roomer->room.room_id);
        }
        j++;
      }
    }
    i++;
  }
}

void admin_menu_storings_modify()
{

}

void admin_menu_storings_delete()
{
  struct storings * storings;
  struct storing * storing;
  unsigned int choice;
  int i = 1;

  storings = storings_get_all();

  menu_display_storings(storings, &i);
  printf("%d) All Storings\n", i);
  printf("Please select the Storing you want to delete: ");
  if((choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }
  else
  {
    if(choice == i)
    {
      storings_delete(storings);
    }
    else
    {
      int j = 1;
      LIST_FOR_EACH(storing, struct storing, node, &storings->storing_list)
      {
        if(choice == j)
        {
          storing_delete(storing);
          break;
        } 
        j++;
      }
    }
  }
}

// storings end


// listings start

void admin_menu_listings_add()
{
  struct items * items;
  struct itemer * itemer;
  struct prices * prices;
  struct price * price;

  unsigned int item_choice;
  unsigned int price_choice;

  int i = 1;
  int j = 1;

  items = items_get_all();
  if(list_empty(&items->item_list))
  {
    printf("No Items found, please add an item before Listing it with a Price\n");
    return;
  }

  prices = prices_get_all();
  if(list_empty(&prices->price_list))
  {
    printf("No Prices found, please add a Price before Listing it\n");
    return;
  }

  menu_display_items(items, &i);
  printf("Please select Item: ");

  if((item_choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }

  menu_display_prices(prices, &j);
  printf("Please select Price: ");
  if((price_choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }

  i = 1;
  I_EACH(itemer, items)
  {
    if(item_choice == i)
    {
      j = 1;
      LIST_FOR_EACH(price, struct price, node, &prices->price_list)
      {
        if(price_choice == j)
        {
          listing_add(itemer->item.iid, price->price_id);
        }
        j++;
      }
    }
    i++;
  }
}

void admin_menu_listings_modify()
{

}

void admin_menu_listings_delete()
{
  struct listings * listings;
  struct listing * listing;
  unsigned int choice;
  int i = 1;

  listings = listings_get_all();

  menu_display_listings(listings, &i);
  printf("%d) All Listings\n", i);
  printf("Please select the Listing you want to delete: ");
  if((choice = getchoice()) == 0)
  {
    printf("No line\n");
    return;
  }
  else
  {
    if(choice == i)
    {
      listings_delete(listings);
    }
    else
    {
      int j = 1;
      LIST_FOR_EACH(listing, struct listing, node, &listings->listing_list)
      {
        if(choice == j)
        {
          listing_delete(listing);
          break;
        } 
        j++;
      }
    }
  }
}

// listings end

// top level start

void admin_menu_add()
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
          admin_menu_items_add();
          break;

        case 2:
          printf("Asked to add a Room\n");
          admin_menu_rooms_add();
          break;

        case 3:
          printf("Asked to add a Price\n");
          admin_menu_prices_add();
          break;

        case 4:
          printf("Asked to store an Item to a Room\n");
          admin_menu_storings_add();
          break;
      
        case 5:
          printf("Asked to list an Item with a Price\n");
          admin_menu_listings_add();
          break;

        default:
          printf("Unrecognized\n");
          break;
    } 
  }
}

void admin_menu_modify()
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
          admin_menu_items_modify();
          break;

        case 2:
          printf("Asked to modify a Room\n");
          admin_menu_rooms_modify();
          break;

        case 3:
          printf("Asked to modify a Price\n");
          admin_menu_prices_modify();
          break;

        case 4:
          printf("Asked to move an Item to another Price\n");
          admin_menu_storings_modify();
          break;

        case 5:
          printf("Asked to relist an Item with another Price\n");
          admin_menu_listings_modify();
          break;
      
        default:
          printf("Unrecognized\n");
          break;
    } 
  }
}

void admin_menu_delete()
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
          admin_menu_items_delete();
          break;

        case 2:
          printf("Asked to delete a Room\n");
          admin_menu_rooms_delete();
          break;

        case 3:
          printf("Asked to delete a Price\n");
          admin_menu_prices_delete();
          break;


        case 4:
          printf("Asked to remove an Item from a Room\n");
          admin_menu_storings_delete();
          break;

        case 5:
          printf("Asked to take down an Item with a Price\n");
          admin_menu_listings_delete();
          break;
      
        default:
          printf("Unrecognized\n");
          break;
    } 
  }
}

// top level end

void admin_menu()
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
          admin_menu_add();
          break;

        case 2:
          printf("Asked to modify\n");
          admin_menu_modify();
          break;


        case 3:
          printf("Asked to delete\n");
          admin_menu_delete();
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
