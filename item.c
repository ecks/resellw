#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "room.h"
#include "item.h"

static struct items * get(char * buffer);
static struct items * items_electronics_get_all(struct items * items);
static struct items * items_clothing_get_all(struct items * items);
static struct items * items_bathbody_get_all(struct items * items);

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
    char * detail = row[5];

    item = calloc(1, sizeof(struct item));
    list_init(&item->node);
    item->iid = calloc(strlen(iid) + 1, sizeof(char)); // 1 extra for null terminating output
    item->upc = calloc(strlen(upc) + 1, sizeof(char)); // 1 extra for null terminating output
    item->desc = calloc(strlen(desc) + 1, sizeof(char)); // 1 extra for null terminating output
    item->quantity = calloc(strlen(quantity) + 1, sizeof(char)); // 1 extra for null terminating output
    item->purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char)); // 1 extra for null terminating output

    if(detail != NULL)
      item->detail = calloc(strlen(detail) + 1, sizeof(char)); // 1 extra for null terminating output
    else
      item->detail = detail;

    strncpy(item->iid, iid, strlen(iid));
    strncpy(item->upc, upc, strlen(upc));
    strncpy(item->desc, desc, strlen(desc));
    strncpy(item->quantity, quantity, strlen(quantity));
    strncpy(item->purchase_price, purchase_price, strlen(purchase_price));

    if(detail != NULL)
      strncpy(item->detail, detail, strlen(detail));

    item->iid[strlen(iid)] = '\0';
    item->upc[strlen(upc)] = '\0';
    item->desc[strlen(desc)] = '\0';
    item->quantity[strlen(quantity)] = '\0';
    item->purchase_price[strlen(purchase_price)] = '\0';

    if(detail != NULL)
      item->detail[strlen(detail)] = '\0';

    list_push_back(&items->item_list, &item->node);    
  }

  mysql_free_result(res);
  return items;
}

struct items * elec_get(char * buffer, struct items * items_par)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct items * items;
  struct electronics * elec;

  if(items_par == NULL)
  {
    items = calloc(1, sizeof(struct items));
    list_init(&items->item_list);
  }
  else
  {
    items = items_par;
  }

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
    elec->item.detail = calloc(strlen(detail) + 1, sizeof(char));

    elec->elec.serial_number = calloc(strlen(serial_number) + 1, sizeof(char));
    elec->elec.electronic_type = calloc(strlen(electronic_type) + 1, sizeof(char));
    elec->elec.model = calloc(strlen(model) + 1, sizeof(char));
  
    strncpy(elec->item.iid, iid, strlen(iid));
    strncpy(elec->item.upc, upc, strlen(upc));
    strncpy(elec->item.desc, desc, strlen(desc));
    strncpy(elec->item.quantity, quantity, strlen(quantity));
    strncpy(elec->item.purchase_price, purchase_price, strlen(purchase_price));
    strncpy(elec->item.detail, detail, strlen(detail));

    strncpy(elec->elec.serial_number, serial_number, strlen(serial_number));
    strncpy(elec->elec.electronic_type, electronic_type, strlen(model));
    strncpy(elec->elec.model, model, strlen(model));

    elec->item.iid[strlen(iid)] = '\0';
    elec->item.upc[strlen(upc)] = '\0';
    elec->item.desc[strlen(desc)] = '\0';
    elec->item.quantity[strlen(quantity)] = '\0';
    elec->item.purchase_price[strlen(purchase_price)] = '\0';
    elec->item.detail[strlen(detail)] = '\0';

    elec->elec.serial_number[strlen(serial_number)] = '\0';
    elec->elec.electronic_type[strlen(electronic_type)] = '\0';
    elec->elec.model[strlen(model)] = '\0';
  
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

struct items * items_get_all_detailed()
{
  struct items * items;

  items = calloc(1, sizeof(struct items));
  list_init(&items->item_list);

  items_electronics_get_all(items);
  items_clothing_get_all(items);
  items_bathbody_get_all(items);

  return items;
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

struct items * items_get_iid(char * iid)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item where iid = '%s'", iid);

  return get(buffer);
}

// use this only if you are sure there is one item in the list
struct item * item_get_iid(char * iid)
{
  struct items * items;
  struct itemer * item;

  items = items_get_iid(iid);

  assert(list_size(I_LIST(items)) == 1);
  itemer = I_CONT(list_pop_front(&items->item_list));
  free(items);

  return itemer->item;
}

struct items * items_electronics_get_all(struct items * items)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join Electronics");

  return elec_get(buffer, items);
}

struct items * items_electronics_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join Electronics where upc = '%s' and description = '%s' and quantity = %s and purchase_price = %s", 
                  upc, description, quantity, purchase_price);
  return elec_get(buffer, NULL);
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

struct items * cloth_get(char * buffer, struct items * items_par)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct items * items;
  struct item * item;
  struct clothing * cloth;

  if(items_par == NULL)
  {
    items = calloc(1, sizeof(struct items));
    list_init(&items->item_list);
  }
  else
  {
    items = items_par;
  }

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * iid = row[0];
    char * upc = row[1];
    char * desc = row[2];
    char * quantity = row[3];
    char * purchase_price = row[4];
    char * detail = row[5];

    char * clothing_brand = row[6];
    char * size = row[7];

    cloth = calloc(1, sizeof(struct clothing));

    list_init(&cloth->item.node);
 
    cloth->item.iid = calloc(strlen(iid) + 1, sizeof(char));
    cloth->item.upc = calloc(strlen(upc) + 1, sizeof(char));
    cloth->item.desc = calloc(strlen(desc) + 1, sizeof(char));
    cloth->item.quantity = calloc(strlen(quantity) + 1, sizeof(char));
    cloth->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char));
    cloth->item.detail = calloc(strlen(detail) + 1, sizeof(char));

    cloth->cloth.clothing_brand = calloc(strlen(clothing_brand) + 1, sizeof(char));
    cloth->cloth.size = calloc(strlen(size) + 1, sizeof(char));
  
    strncpy(cloth->item.iid, iid, strlen(iid));
    strncpy(cloth->item.upc, upc, strlen(upc));
    strncpy(cloth->item.desc, desc, strlen(desc));
    strncpy(cloth->item.quantity, quantity, strlen(quantity));
    strncpy(cloth->item.purchase_price, purchase_price, strlen(purchase_price));
    strncpy(cloth->item.detail, detail, strlen(detail));

    strncpy(cloth->cloth.clothing_brand, clothing_brand, strlen(clothing_brand));
    strncpy(cloth->cloth.size, size, strlen(size));

    cloth->item.iid[strlen(iid)] = '\0';
    cloth->item.upc[strlen(upc)] = '\0';
    cloth->item.desc[strlen(desc)] = '\0';
    cloth->item.quantity[strlen(quantity)] = '\0';
    cloth->item.purchase_price[strlen(purchase_price)] = '\0';
    cloth->item.detail[strlen(detail)] = '\0';

    cloth->cloth.clothing_brand[strlen(clothing_brand)] = '\0';
    cloth->cloth.size[strlen(size)] = '\0';
  
    list_push_back(&items->item_list, &cloth->item.node);
  }

  return items;
}

struct items * items_clothing_get_all(struct items * items)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join Clothing");

  return cloth_get(buffer, items);
}

struct items * items_clothing_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join Clothing where upc = '%s' and description = '%s' and quantity = %s and purchase_price = %s", 
                  upc, description, quantity, purchase_price);
  return cloth_get(buffer, NULL);
}

struct clothing * item_clothing_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  struct items * items;
  struct clothing * cloth;

  items = items_clothing_get(upc, description, quantity, purchase_price);

  assert(list_size(I_LIST(items)) == 1);
  cloth = C_CONT(list_pop_front(&items->item_list));
  free(items);

  return cloth;
}

struct items * bathbody_get(char * buffer, struct items * items_par)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct items * items;
  struct item * item;
  struct bathbody * bb;

  if(items_par == NULL)
  {
    items = calloc(1, sizeof(struct items));
    list_init(&items->item_list);
  }
  else
  {
    items = items_par;
  }

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * iid = row[0];
    char * upc = row[1];
    char * desc = row[2];
    char * quantity = row[3];
    char * purchase_price = row[4];
    char * detail = row[5];

    char * bathbody_brand = row[6];
    char * feature = row[7];

    bb = calloc(1, sizeof(struct bathbody));

    list_init(&bb->item.node);
 
    bb->item.iid = calloc(strlen(iid) + 1, sizeof(char));
    bb->item.upc = calloc(strlen(upc) + 1, sizeof(char));
    bb->item.desc = calloc(strlen(desc) + 1, sizeof(char));
    bb->item.quantity = calloc(strlen(quantity) + 1, sizeof(char));
    bb->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char));
    bb->item.detail = calloc(strlen(detail) + 1, sizeof(char));

    bb->bb.bathbody_brand = calloc(strlen(bathbody_brand) + 1, sizeof(char));
    bb->bb.feature = calloc(strlen(feature) + 1, sizeof(char));
  
    strncpy(bb->item.iid, iid, strlen(iid));
    strncpy(bb->item.upc, upc, strlen(upc));
    strncpy(bb->item.desc, desc, strlen(desc));
    strncpy(bb->item.quantity, quantity, strlen(quantity));
    strncpy(bb->item.purchase_price, purchase_price, strlen(purchase_price));
    strncpy(bb->item.detail, detail, strlen(detail));

    strncpy(bb->bb.bathbody_brand, bathbody_brand, strlen(bathbody_brand));
    strncpy(bb->bb.feature, feature, strlen(feature));

    bb->item.iid[strlen(iid)] = '\0';
    bb->item.upc[strlen(upc)] = '\0';
    bb->item.desc[strlen(desc)] = '\0';
    bb->item.quantity[strlen(quantity)] = '\0';
    bb->item.purchase_price[strlen(purchase_price)] = '\0';
    bb->item.detail[strlen(detail)] = '\0';

    bb->bb.bathbody_brand[strlen(bathbody_brand)] = '\0';
    bb->bb.feature[strlen(feature)] = '\0';
  
    list_push_back(&items->item_list, &bb->item.node);
  }

  return items;
}

struct items * items_bathbody_get_all(struct items * items)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join BathBody");

  return bathbody_get(buffer, items);
}

struct items * items_bathbody_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  char buffer[200];
  sprintf(buffer, "SELECT * FROM Item natural join BathBody where upc = '%s' and description = '%s' and quantity = %s and purchase_price = %s", 
                  upc, description, quantity, purchase_price);
  return bathbody_get(buffer, NULL);
}

struct bathbody * item_bathbody_get(char * upc, char * description, char * quantity, char * purchase_price)
{
  struct items * items;
  struct bathbody * bathbody;

  items = items_bathbody_get(upc, description, quantity, purchase_price);

  assert(list_size(I_LIST(items)) == 1);
  bathbody = B_CONT(list_pop_front(&items->item_list));
  free(items);

  return bathbody;
}

int item_modify(struct item * item, char * column, char * value)
{
  char buffer[200];
  sprintf(buffer, "UPDATE Item SET %s='%s' WHERE iid=%s", column, value, item->iid);
  db_query(buffer);
  return 0;
}

int item_elec_modify(struct item * item, char * column, char * value)
{
  char buffer[200];
  sprintf(buffer, "UPDATE Electronics SET %s='%s' WHERE iid=%s", column, value, item->iid);
  db_query(buffer);
  return 0;
}

int item_clothing_modify(struct item * item, char * column, char * value)
{
  char buffer[200];
  sprintf(buffer, "UPDATE Clothing SET %s='%s' WHERE iid=%s", column, value, item->iid);
  db_query(buffer);
  return 0;
}

int item_bathbody_modify(struct item * item, char * column, char * value)
{
  char buffer[200];
  sprintf(buffer, "UPDATE BathBody SET %s='%s' WHERE iid=%s", column, value, item->iid);
  db_query(buffer);
  return 0;
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

int item_clothing_delete(struct clothing * cloth)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Item where iid = '%s'", cloth->item.iid);
  db_query(buffer); 

  sprintf(buffer, "DELETE FROM Clothing where iid = '%s'", cloth->item.iid);
  db_query(buffer); 

  return 0;
}

int item_bathbody_delete(struct bathbody * bathbody)
{
  char buffer[200];

  sprintf(buffer, "DELETE FROM Item where iid = '%s'", bathbody->item.iid);
  db_query(buffer); 

  sprintf(buffer, "DELETE FROM BathBody where iid = '%s'", bathbody->item.iid);
  db_query(buffer); 

  return 0;
}
