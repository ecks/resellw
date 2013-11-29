#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "util.h"
#include "list.h"
#include "item.h"
#include "menu_common.h"

void menu_display_items(struct items * items)
{
  struct item * item;

  LIST_FOR_EACH(item, struct item, node, &items->item_list)
  {   
    printf("Item UPC: %s\n", item->upc);
    printf("Item Description: %s\n", item->desc);
    printf("Item Quantity: %s\n", item->quantity);
    printf("Item Purchase Price: %s\n", item->purchase_price);      
  }   
}

void menu_display_items_electronics(struct items * items)
{
  struct electronics * electronics;

  LIST_FOR_EACH(electronics, struct electronics, item.node, &items->item_list)
  {
    printf("Item UPC: %s\n", electronics->item.upc);
    printf("Item Description: %s\n", electronics->item.desc);
    printf("Item Quantity: %s\n", electronics->item.quantity);
    printf("Item Purchase Price: %s\n", electronics->item.purchase_price);
    printf("Item Serial Number: %s\n", electronics->serial_number);
    printf("Item Electronic Type: %s\n", electronics->electronic_type);
    printf("Item Model: %s\n", electronics->model);
  }
}
