#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "item.h"

static struct items * get(char * buffer);

int item_add(char * upc, char * description, char * quantity, char * purchase_price, char * detail)
{
  char buffer[200];
  struct items * items;

  items = items_get(upc, description, quantity, purchase_price);
  if(list_empty(&items->item_list))
  {
    if(detail != NULL)
    {
      sprintf(buffer, "INSERT INTO Item (upc, description, quantity, purchase_price, detail) VALUES ('%s', '%s', %s, %s, '%s')", 
                      upc, description, quantity, purchase_price, detail);
    }
    else
    {
      sprintf(buffer, "INSERT INTO Item (upc, description, quantity, purchase_price) VALUES ('%s', '%s', %s, %s)", 
                      upc, description, quantity, purchase_price);
    }
    db_query(buffer); 
  }
  else
  {
    printf("A duplicate of an already item cannot be added\n");
    return -1;
  }

  return 0;
}

int item_electronics_add(char * upc, char * description, char * quantity, char * purchase_price, char * serial_number, char * electronic_type, char * model)
{
  char buffer[200];
  struct items * items;
  struct item * item;

  if(item_add(upc, description, quantity, purchase_price, "elec") < 0)
  {
    return -1;
  }

  item = item_get(upc, description, quantity, purchase_price);
  sprintf(buffer, "INSERT INTO Electronics (iid, serial_number, electronic_type, model) VALUES ('%s', '%s', '%s', '%s')", 
                  item->iid, serial_number, electronic_type, model);
  db_query(buffer); 

  return 0;
}

int item_clothing_add(char * upc, char * description, char * quantity, char * purchase_price, char * clothing_brand, char * size)
{
  char buffer[200];
  struct items * items;
  struct item * item;

  if(item_add(upc, description, quantity, purchase_price, "clothing") < 0)
  {
    return -1;
  }

  item = item_get(upc, description, quantity, purchase_price);
  sprintf(buffer, "INSERT INTO Clothing (iid, clothing_brand, size) VALUES ('%s', '%s', '%s')", 
                  item->iid, clothing_brand, size);
  db_query(buffer); 

  return 0;
}

int item_bathbody_add(char * upc, char * description, char * quantity, char * purchase_price, char * bathbody_brand, char * feature)
{
  char buffer[200];
  struct items * items;
  struct item * item;

  if(item_add(upc, description, quantity, purchase_price, "bathbody") < 0)
  {
    return -1;
  }

  item = item_get(upc, description, quantity, purchase_price);
  sprintf(buffer, "INSERT INTO BathBody (iid, bathbody_brand, feature) VALUES ('%s', '%s', '%s')", 
                  item->iid, bathbody_brand, feature);
  db_query(buffer); 

  return 0;
}

struct items * get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct items * items;
  struct item * item;

  items = calloc(1, sizeof(struct items));
  list_init(&items->item_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * iid = row[0];
    char * upc = row[1];
    char * desc = row[2];
    char * quantity = row[3];
    char * purchase_price = row[4];

    item = calloc(1, sizeof(struct item));
    list_init(&item->node);
    item->iid = calloc(strlen(iid) + 1, sizeof(char)); // 1 extra for null terminating output
    item->upc = calloc(strlen(upc) + 1, sizeof(char)); // 1 extra for null terminating output
    item->desc = calloc(strlen(desc) + 1, sizeof(char)); // 1 extra for null terminating output
    item->quantity = calloc(strlen(quantity) + 1, sizeof(char)); // 1 extra for null terminating output
    item->purchase_price = calloc(strlen(desc) + 1, sizeof(char)); // 1 extra for null terminating output

    strncpy(item->iid, iid, strlen(iid));
    strncpy(item->upc, upc, strlen(upc));
    strncpy(item->desc, desc, strlen(desc));
    strncpy(item->quantity, quantity, strlen(quantity));
    strncpy(item->purchase_price, purchase_price, strlen(purchase_price));

    item->iid[strlen(iid)] = '\0';
    item->upc[strlen(upc)] = '\0';
    item->desc[strlen(desc)] = '\0';
    item->quantity[strlen(quantity)] = '\0';
    item->purchase_price[strlen(purchase_price)] = '\0';

    list_push_back(&items->item_list, &item->node);    
  }

  mysql_free_result(res);
  return items;
}

// if item is NULL, we need to retrieve the item based on iid 
struct items * elec_get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct items * items;
  struct item * item;
  struct electronics * elec;

  items = calloc(1, sizeof(struct items));
  list_init(&items->item_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * iid = row[0];
    char * upc = row[1];
    char * desc = row[2];
    char * quantity = row[3];
    char * purchase_price = row[4];
    char * detail = row[5];

    char * serial_number = row[6];
    char * electronic_type = row[7];
    char * model = row[8];

    elec = calloc(1, sizeof(struct electronics));

    list_init(&elec->item.node);
 
    elec->item.iid = calloc(strlen(iid) + 1, sizeof(char));
    elec->item.upc = calloc(strlen(upc) + 1, sizeof(char));
    elec->item.desc = calloc(strlen(desc) + 1, sizeof(char));
    elec->item.quantity = calloc(strlen(quantity) + 1, sizeof(char));
    elec->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char));

    elec->serial_number = calloc(strlen(serial_number) + 1, sizeof(char));
    elec->electronic_type = calloc(strlen(electronic_type) + 1, sizeof(char));
    elec->model = calloc(strlen(model) + 1, sizeof(char));
  
    strncpy(elec->item.iid, iid, strlen(iid));
    strncpy(elec->item.upc, upc, strlen(upc));
    strncpy(elec->item.desc, desc, strlen(desc));
    strncpy(elec->item.quantity, quantity, strlen(quantity));
    strncpy(elec->item.purchase_price, purchase_price, strlen(purchase_price));

    strncpy(elec->serial_number, serial_number, strlen(serial_number));
    strncpy(elec->electronic_type, electronic_type, strlen(model));
    strncpy(elec->model, model, strlen(model));

    elec->item.iid[strlen(iid)] = '\0';
    elec->item.upc[strlen(upc)] = '\0';
    elec->item.desc[strlen(desc)] = '\0';
    elec->item.quantity[strlen(quantity)] = '\0';
    elec->item.purchase_price[strlen(purchase_price)] = '\0';

    elec->serial_number[strlen(serial_number)] = '\0';
    elec->electronic_type[strlen(electronic_type)] = '\0';
    elec->model[strlen(model)] = '\0';
  
    list_push_back(&items->item_list, &elec->item.node);
  }

  return items;
}

struct items * items_get_all()
{
  char buffer[BUF_LEN];
  sprintf(buffer, "SELECT * FROM Item");
  return get(buffer);
}

// TODO
struct items * items_get_all_detailed()
{
  return NULL;
}

struct items * items_get(char * upc, char * description, char * quantity, char *  purchase_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item where upc = '%s' and description = '%s' and quantity = %s and purchase_price = %s", upc, description, quantity, purchase_price);

  return get(buffer);
}

struct items * items_get_upc(char * upc)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item where upc = '%s'", upc);

  return get(buffer);
}

// use this only if you are sure there is one item in the list
struct item * item_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  struct items * items;
  struct item * item;

  items = items_get(upc, description, quantity, purchase_price);

  assert(list_size(I_LIST(items)) == 1);
  item = I_CONT(list_pop_front(&items->item_list));
  free(items);

  return item;
}

struct items * items_electronics_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join Electronics where upc = '%s' and description = '%s' and quantity = %s and purchase_price = %s", 
                  upc, description, quantity, purchase_price);
  return elec_get(buffer);
}

struct items * items_electronics_get_model(char * model)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join Electronics where model = '%s'", 
                  model);
  return elec_get(buffer);
}

struct electronics * item_electronics_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  struct items * items;
  struct electronics * elec;

  items = items_electronics_get(upc, description, quantity, purchase_price);

  assert(list_size(I_LIST(items)) == 1);
  elec = E_CONT(list_pop_front(&items->item_list));
  free(items);

  return elec;
}

int item_delete(struct item * item)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Item where iid = '%s'", item->iid);
  db_query(buffer); 
  return 0;
}


int items_delete(struct items * items)
{
  struct item * item;
  LIST_FOR_EACH(item, struct item, node, &items->item_list)
  {
    item_delete(item);
  }

  return 0;
}

int item_electronics_delete(struct electronics * elec)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Item where iid = '%s'", elec->item.iid);
  db_query(buffer); 

  sprintf(buffer, "DELETE FROM Electronics where iid = '%s'", elec->item.iid);
  db_query(buffer); 

  return 0;
}
