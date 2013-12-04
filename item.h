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
  char * detail;
};

struct itemer
{
  struct list node;
  struct item item;
};

struct elec
{
  char * serial_number;
  char * electronic_type;
  char * model;
};

struct electronics
{
  struct list node;
  struct item item;
  struct elec elec;
};

struct cloth
{
  char * clothing_brand;
  char * size;
};

struct clothing
{
  struct list node;
  struct item item;
  struct cloth cloth;
};

struct bb
{
  char * bathbody_brand;
  char * feature;
};

struct bathbody
{
  struct list node;
  struct item item;
  struct bb bb;
};

#define I_LIST(ptr) (&ptr->item_list)

#define I_CONT(ptr) (CONTAINER_OF(ptr, struct itemer, node))
#define E_CONT(ptr) (CONTAINER_OF(ptr, struct electronics, node))
#define C_CONT(ptr) (CONTAINER_OF(ptr, struct clothing, node))
#define B_CONT(ptr) (CONTAINER_OF(ptr, struct bathbody, node))

#define I_EACH(itemer, items) LIST_FOR_EACH(itemer, struct itemer, node, I_LIST(items))
//#define E_EACH(itemer, items) LIST_FOR_EACH(itemer, struct electronics, node, I_LIST(rooms))
//#define C_EACH(itemer, items) LIST_FOR_EACH(itemer, struct itemer, node, I_LIST(rooms))
//#define B_EACH(itemer, items) LIST_FOR_EACH(itemer, struct itemer, node, I_LIST(rooms))

extern int item_add(char * upc, char * description, char * quantity, char * purchase_price, char * detail);
extern int item_electronics_add(char * upc, char * description, char * quantity, char * purchase_price, char * serial_number, char * electronic_type, char * model);
extern int item_clothing_add(char * upc, char * description, char * quantity, char * purchase_price, char * clothing_brand, char * size);
extern int item_bathbody_add(char * upc, char * description, char * quantity, char * purchase_price, char * bathbody_brand, char * feature);

extern struct items * items_get_all();
extern struct items * items_get_all_detailed();
extern struct items * items_get_upc(char * upc);
extern struct items * items_get(char * upc, char * description, char * quantity, char * purchase_price);
extern struct item * item_get(char * upc, char * description, char * quantity, char * purchase_price);
extern struct items * items_get_iid(char * iid);
extern struct item * item_get_iid(char * iid);


extern struct electronics * item_electronics_get(char * upc, char * description, char * quantity, char * purchase_price);
struct clothing * item_clothing_get(char * upc, char * description, char * quantity, char * purchase_price);

struct bathbody * item_bathbody_get(char * upc, char * description, char * quantity, char * purchase_price);

extern int item_modify(struct item * item, char * column, char * value);
extern int item_elec_modify(struct item * item, char * column, char * value);
extern int item_clothing_modify(struct item * item, char * column, char * value);
extern int item_bathbody_modify(struct item * item, char * column, char * value);

extern int item_delete(struct item * item);
extern int item_electronics_delete(struct electronics * elec);
extern int item_clothing_delete(struct clothing * cloth);
extern int item_bathbody_delete(struct bathbody * bathbody);
extern int items_delete(struct items * items);

#endif
