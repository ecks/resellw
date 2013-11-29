#ifndef ITEM_H
#define ITEM_H

struct items
{
  struct list item_list;
};

struct item
{
  char * iid;
  char * upc;
  char * desc;
  char * quantity;
  char * purchase_price;
  struct list node;
};

struct electronics
{
  struct item item;
  char * serial_number;
  char * electronic_type;
  char * model;
};

struct clothing
{
  struct item item;
  char * clothing_brand;
  char * size;
};

struct bathbody
{
  struct item item;
  char * bathbody_brand;
  char * feature;
};

#define I_LIST(ptr) (&ptr->item_list)

#define I_CONT(ptr) (CONTAINER_OF(ptr, struct item, node))
#define E_CONT(ptr) (CONTAINER_OF(ptr, struct electronics, item.node))

extern int item_add(char * upc, char * description, char * quantity, char * purchase_price, char * detail);
extern int item_electronics_add(char * upc, char * description, char * quantity, char * purchase_price, char * serial_number, char * electronic_type, char * model);
extern int item_clothing_add(char * upc, char * description, char * quantity, char * purchase_price, char * clothing_brand, char * size);
extern int item_bathbody_add(char * upc, char * description, char * quantity, char * purchase_price, char * bathbody_brand, char * feature);

extern struct items * items_get_all();
extern struct items * items_get_all_detailed();
extern struct items * items_get_upc(char * upc);
extern struct items * items_get(char * upc, char * description, char * quantity, char * purchase_price);
extern struct item * item_get(char * upc, char * description, char * quantity, char * purchase_price);
extern struct electronics * item_electronics_get(char * upc, char * description, char * quantity, char * purchase_price);
extern struct items * items_electronics_get_model(char * model);

extern int item_delete(struct item * item);
extern int item_electronics_delete(struct electronics * elec);
extern int items_delete(struct items * items);

#endif
