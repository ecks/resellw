#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "util.h"
#include "list.h"
#include "room.h"
#include "item.h"
#include "price.h"
#include "store.h"
#include "listing.h"
#include "menu_common.h"

static void menu_display_item_electronics(struct electronics * elec);
static void menu_display_item_electronics_room(struct electronics_room * elec_room);
static void menu_display_item_clothing(struct clothing * cloth);
static void menu_display_item_clothing_room(struct clothing_room * cloth_room);
static void menu_display_item_bathbody(struct bathbody * bathbody);
static void menu_display_item_bathbody_room(struct bathbody_room * bathbody_room);

void menu_display_rooms(struct rooms * rooms, int * i_ptr)
{
  struct roomer * roomer;

  LIST_FOR_EACH(roomer, struct roomer, node, R_LIST(rooms))
  {
    printf("%d) Room %s\n", *i_ptr, roomer->room.desc);
    (*i_ptr)++;
  }
}

void menu_display_prices(struct prices * prices, int * i_ptr)
{
  struct pricer * pricer;

  P_EACH(pricer, prices)
  {
    printf("%d) Price type:  %s, selling price: %s\n", *i_ptr, pricer->price.type_of_price, pricer->price.sell_price);
    (*i_ptr)++;
  }
}

void menu_display_items(struct items * items, int * i_ptr)
{
  struct itemer * itemer;

  I_EACH(itemer, items)
  {   
    printf("%d) Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s\n", *i_ptr, itemer->item.upc, itemer->item.desc, itemer->item.quantity, itemer->item.purchase_price);
    (*i_ptr)++;
  }   
}

void menu_display_items_detailed(struct items * items)
{
  struct itemer * itemer;

  int i = 1;
  I_EACH(itemer, items)
  {
    printf("%d) ", i);
    if(strcmp(itemer->item.detail, "elec") == 0)
    {
      menu_display_item_electronics((struct electronics *)itemer);
    }
    else if(strcmp(itemer->item.detail, "clothing") == 0)
    {
      menu_display_item_clothing((struct clothing *)itemer);
    }
    else if(strcmp(itemer->item.detail, "bathbody") == 0)
    {
      menu_display_item_bathbody((struct bathbody *)itemer);
    }
    i++;
  }
}

void menu_display_items_rooms_detailed(struct item_rooms * item_rooms)
{
  struct itemer * itemer;

  int i = 1;
  IR_EACH(itemer, item_rooms)
  {
    printf("%d) ", i);
    if(strcmp(itemer->item.detail, "elec") == 0)
    {
      menu_display_item_electronics_room((struct electronics_room *)itemer);
    }
    else if(strcmp(itemer->item.detail, "clothing") == 0)
    {
      menu_display_item_clothing_room((struct clothing_room *)itemer);
    }
    else if(strcmp(itemer->item.detail, "bathbody") == 0)
    {
      menu_display_item_bathbody_room((struct bathbody_room *)itemer);
    }
    i++;
  }

}

void menu_display_item_electronics(struct electronics * elec)
{
  printf("Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s, Serial Number: %s, Electronic Type: %s, Model: %s\n", 
          elec->item.upc, elec->item.desc, elec->item.quantity, elec->item.purchase_price, elec->elec.serial_number, elec->elec.electronic_type, elec->elec.model);
}

void menu_display_item_electronics_room(struct electronics_room * elec_room)
{
  printf("Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s, Serial Number: %s, Electronic Type: %s, Model: %s, Room Desc: %s\n", 
          elec_room->item.upc, elec_room->item.desc, elec_room->item.quantity, elec_room->item.purchase_price, elec_room->elec.serial_number, elec_room->elec.electronic_type, elec_room->elec.model, elec_room->room.desc);
}


void menu_display_item_clothing(struct clothing * cloth)
{
  printf("Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s, Clothing Brand: %s, Size: %s\n", 
          cloth->item.upc, cloth->item.desc, cloth->item.quantity, cloth->item.purchase_price, cloth->cloth.clothing_brand, cloth->cloth.size);
}

void menu_display_item_clothing_room(struct clothing_room * cloth_room)
{
  printf("Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s, Clothing Brand: %s, Size: %s, Room Desc: %s\n", 
          cloth_room->item.upc, cloth_room->item.desc, cloth_room->item.quantity, cloth_room->item.purchase_price, cloth_room->cloth.clothing_brand, cloth_room->cloth.size, cloth_room->room.desc);
}

void menu_display_item_bathbody(struct bathbody * bathbody)
{
  printf("Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s, Bath&Body Brand: %s, Feature: %s\n", 
          bathbody->item.upc, bathbody->item.desc, bathbody->item.quantity, bathbody->item.purchase_price, bathbody->bb.bathbody_brand, bathbody->bb.feature);
}

void menu_display_item_bathbody_room(struct bathbody_room * bathbody_room)
{
  printf("Item UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s, Bath&Body Brand: %s, Feature: %s, Room Desc: %s\n", bathbody_room->item.upc, bathbody_room->item.desc, bathbody_room->item.quantity, bathbody_room->item.purchase_price, bathbody_room->bb.bathbody_brand, bathbody_room->bb.feature, bathbody_room->room.desc);
}

void menu_display_storings(struct storings * storings, int * i_ptr)
{
  struct storing * storing;
  struct item * item;
  struct roomer * roomer;

  S_EACH(storing, storings)
  {
    printf("%d) Item (UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s) Stored in Room (%s)\n", *i_ptr, storing->item.upc, storing->item.desc, storing->item.quantity, storing->item.purchase_price, storing->room.desc);
    (*i_ptr)++;  
  }
}

void menu_display_listings(struct listings * listings, int * i_ptr)
{
  struct listing * listing;
  struct item * item;
  struct price * price;

  LIST_FOR_EACH(listing, struct listing, node, L_LIST(listings))
  {
    printf("%d) Item (UPC: %s, Description: %s, Quantity: %s, Purchase Price: %s) Listed with Price (Type: %s, Sell Price: %s)\n", *i_ptr, listing->item.upc, listing->item.desc, listing->item.quantity, listing->item.purchase_price, listing->price.type_of_price, listing->price.sell_price);
    (*i_ptr)++;  
  }
}
