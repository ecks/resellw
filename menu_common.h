#ifndef MENU_COMMON_H
#define MENU_COMMON_H

extern void menu_display_rooms(struct rooms * rooms, int * i_ptr);
extern void menu_display_prices(struct prices * prices, int * i_ptr);
extern void menu_display_items(struct items * items, int * i_ptr);
extern void menu_display_items_detailed(struct items * items);
extern void menu_display_items_rooms_detailed(struct item_rooms *);
extern void menu_display_storings(struct storings * storings, int * i_ptr);
extern void menu_display_listings(struct listings * listings, int * i_ptr);

#endif
