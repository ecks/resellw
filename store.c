#include <stddef.h>
#include <stdbool.h>
#include <mysql.h>

#include "db.h"
#include "util.h"
#include "list.h"
#include "item.h"
#include "room.h"
#include "store.h"

int storing_add(char * iid, char * room_id)
{
  char buffer[BUF_LEN];
  int error;

  sprintf(buffer, "INSERT INTO Store (iid, room_id) VALUES (%s, %s)", iid, room_id);
  if((error = db_query(buffer)) == 1062)
  {
    printf("You cannot store an item in more than one Room...\n");
    return 1;   
  }
  return 0;
}

struct storings * get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct storings * storings;
  struct storing * storing;

  storings = calloc(1, sizeof(struct storings));
  list_init(&storings->storing_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * iid = row[0];
    char * room_id = row[1];

    storing = calloc(1, sizeof(struct storing));
    list_init(&storing->node);

    storing->item.iid = calloc(strlen(iid) + 1, sizeof(char)); // 1 extra for null terminating output
    storing->room.room_id = calloc(strlen(room_id) + 1, sizeof(char)); // 1 extra for null terminating output
 
    strncpy(storing->item.iid, iid, strlen(iid));
    strncpy(storing->room.room_id, room_id, strlen(room_id));

    storing->item.iid[strlen(iid)] = '\0';
    storing->room.room_id[strlen(room_id)] = '\0';

    list_push_back(&storings->storing_list, &storing->node);    
  }

  mysql_free_result(res);
  return storings;
}

struct storings * item_store_room_get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct storings * storings;
  struct storing * storing;

  storings = calloc(1, sizeof(struct storings));
  list_init(&storings->storing_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * room_id = row[0];

    char * iid = row[1];
    char * upc = row[2];
    char * desc = row[3];
    char * quantity = row[4];
    char * purchase_price = row[5];
    char * detail = row[6];

    char * room_desc = row[7];

    storing = calloc(1, sizeof(struct storing));

    list_init(&storing->node);
 
    storing->room.room_id = calloc(strlen(room_id) + 1, sizeof(char));

    storing->item.iid = calloc(strlen(iid) + 1, sizeof(char));
    storing->item.upc = calloc(strlen(upc) + 1, sizeof(char));
    storing->item.desc = calloc(strlen(desc) + 1, sizeof(char));
    storing->item.quantity = calloc(strlen(quantity) + 1, sizeof(char));
    storing->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char));

    storing->room.desc = calloc(strlen(room_desc) + 1, sizeof(char));
  
    strncpy(storing->room.room_id, room_id, strlen(room_id));

    strncpy(storing->item.iid, iid, strlen(iid));
    strncpy(storing->item.upc, upc, strlen(upc));
    strncpy(storing->item.desc, desc, strlen(desc));
    strncpy(storing->item.quantity, quantity, strlen(quantity));
    strncpy(storing->item.purchase_price, purchase_price, strlen(purchase_price));

    strncpy(storing->room.desc, room_desc, strlen(room_desc));

    storing->room.room_id[strlen(room_id)] = '\0';

    storing->item.iid[strlen(iid)] = '\0';
    storing->item.upc[strlen(upc)] = '\0';
    storing->item.desc[strlen(desc)] = '\0';
    storing->item.quantity[strlen(quantity)] = '\0';
    storing->item.purchase_price[strlen(purchase_price)] = '\0';

    storing->room.desc[strlen(desc)] = '\0';
  
    list_push_back(S_LIST(storings), NODE(storing));
  }

  return storings;
}

struct item_rooms * elec_store_room_get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct item_rooms * item_rooms;
  struct electronics_room * elec_room;

  item_rooms = calloc(1, sizeof(struct item_rooms));
  list_init(&item_rooms->item_room_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * room_id = row[0];

    char * iid = row[1];
    char * upc = row[2];
    char * desc = row[3];
    char * quantity = row[4];
    char * purchase_price = row[5];
    char * detail = row[6];

    char * serial_number = row[7];
    char * electronic_type = row[8];
    char * model = row[9];
 
    char * room_desc = row[10];

    elec_room = calloc(1, sizeof(struct electronics_room));

    list_init(&elec_room->node);
 
    elec_room->room.room_id = calloc(strlen(room_id) + 1, sizeof(char));

    elec_room->item.iid = calloc(strlen(iid) + 1, sizeof(char));
    elec_room->item.upc = calloc(strlen(upc) + 1, sizeof(char));
    elec_room->item.desc = calloc(strlen(desc) + 1, sizeof(char));
    elec_room->item.quantity = calloc(strlen(quantity) + 1, sizeof(char));
    elec_room->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char));
    elec_room->item.detail = calloc(strlen(detail) + 1, sizeof(char));

    elec_room->elec.serial_number = calloc(strlen(serial_number) + 1, sizeof(char));
    elec_room->elec.electronic_type = calloc(strlen(electronic_type) + 1, sizeof(char));
    elec_room->elec.model = calloc(strlen(model) + 1, sizeof(char));

    elec_room->room.desc = calloc(strlen(room_desc) + 1, sizeof(char));
  
    strncpy(elec_room->room.room_id, room_id, strlen(room_id));

    strncpy(elec_room->item.iid, iid, strlen(iid));
    strncpy(elec_room->item.upc, upc, strlen(upc));
    strncpy(elec_room->item.desc, desc, strlen(desc));
    strncpy(elec_room->item.quantity, quantity, strlen(quantity));
    strncpy(elec_room->item.purchase_price, purchase_price, strlen(purchase_price));
    strncpy(elec_room->item.detail, detail, strlen(detail));

    strncpy(elec_room->elec.serial_number, serial_number, strlen(serial_number));
    strncpy(elec_room->elec.electronic_type, electronic_type, strlen(model));
    strncpy(elec_room->elec.model, model, strlen(model));
    
    strncpy(elec_room->room.desc, room_desc, strlen(room_desc));

    elec_room->room.room_id[strlen(room_id)] = '\0';

    elec_room->item.iid[strlen(iid)] = '\0';
    elec_room->item.upc[strlen(upc)] = '\0';
    elec_room->item.desc[strlen(desc)] = '\0';
    elec_room->item.quantity[strlen(quantity)] = '\0';
    elec_room->item.purchase_price[strlen(purchase_price)] = '\0';
    elec_room->item.detail[strlen(detail)] = '\0';

    elec_room->elec.serial_number[strlen(serial_number)] = '\0';
    elec_room->elec.electronic_type[strlen(electronic_type)] = '\0';
    elec_room->elec.model[strlen(model)] = '\0';
    
    elec_room->room.desc[strlen(desc)] = '\0';
  
    list_push_back(&item_rooms->item_room_list, &elec_room->node);
  }

  return item_rooms;
}

struct item_rooms * cloth_store_room_get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct item_rooms * item_rooms;
  struct clothing_room * cloth_room;

  item_rooms = calloc(1, sizeof(struct item_rooms));
  list_init(&item_rooms->item_room_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * room_id = row[0];

    char * iid = row[1];
    char * upc = row[2];
    char * desc = row[3];
    char * quantity = row[4];
    char * purchase_price = row[5];
    char * detail = row[6];

    char * clothing_brand = row[7];
    char * size = row[8];
 
    char * room_desc = row[9];

    cloth_room = calloc(1, sizeof(struct clothing_room));

    list_init(&cloth_room->node);
 
    cloth_room->room.room_id = calloc(strlen(room_id) + 1, sizeof(char));

    cloth_room->item.iid = calloc(strlen(iid) + 1, sizeof(char));
    cloth_room->item.upc = calloc(strlen(upc) + 1, sizeof(char));
    cloth_room->item.desc = calloc(strlen(desc) + 1, sizeof(char));
    cloth_room->item.quantity = calloc(strlen(quantity) + 1, sizeof(char));
    cloth_room->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char));
    cloth_room->item.detail = calloc(strlen(detail) + 1, sizeof(char));

    cloth_room->cloth.clothing_brand = calloc(strlen(clothing_brand) + 1, sizeof(char));
    cloth_room->cloth.size = calloc(strlen(size) + 1, sizeof(char));

    cloth_room->room.desc = calloc(strlen(room_desc) + 1, sizeof(char));
  
    strncpy(cloth_room->room.room_id, room_id, strlen(room_id));

    strncpy(cloth_room->item.iid, iid, strlen(iid));
    strncpy(cloth_room->item.upc, upc, strlen(upc));
    strncpy(cloth_room->item.desc, desc, strlen(desc));
    strncpy(cloth_room->item.quantity, quantity, strlen(quantity));
    strncpy(cloth_room->item.purchase_price, purchase_price, strlen(purchase_price));
    strncpy(cloth_room->item.detail, detail, strlen(detail));

    strncpy(cloth_room->cloth.clothing_brand, clothing_brand, strlen(clothing_brand));
    strncpy(cloth_room->cloth.size, size, strlen(size));
    
    strncpy(cloth_room->room.desc, room_desc, strlen(room_desc));

    cloth_room->room.room_id[strlen(room_id)] = '\0';

    cloth_room->item.iid[strlen(iid)] = '\0';
    cloth_room->item.upc[strlen(upc)] = '\0';
    cloth_room->item.desc[strlen(desc)] = '\0';
    cloth_room->item.quantity[strlen(quantity)] = '\0';
    cloth_room->item.purchase_price[strlen(purchase_price)] = '\0';
    cloth_room->item.detail[strlen(detail)] = '\0';

    cloth_room->cloth.clothing_brand[strlen(clothing_brand)] = '\0';
    cloth_room->cloth.size[strlen(size)] = '\0';
    
    cloth_room->room.desc[strlen(desc)] = '\0';
  
    list_push_back(&item_rooms->item_room_list, &cloth_room->node);
  }

  return item_rooms;
}

struct item_rooms * bb_store_room_get(char * buffer)
{
  MYSQL_RES * res;
  MYSQL_ROW row;
  struct item_rooms * item_rooms;
  struct bathbody_room * bb_room;

  item_rooms = calloc(1, sizeof(struct item_rooms));
  list_init(&item_rooms->item_room_list);

  res = db_query_res(buffer); 
  while (row = mysql_fetch_row(res)) 
  {
    char * room_id = row[0];

    char * iid = row[1];
    char * upc = row[2];
    char * desc = row[3];
    char * quantity = row[4];
    char * purchase_price = row[5];
    char * detail = row[6];

    char * bathbody_brand = row[7];
    char * feature = row[8];
 
    char * room_desc = row[9];

    bb_room = calloc(1, sizeof(struct clothing_room));

    list_init(&bb_room->node);
 
    bb_room->room.room_id = calloc(strlen(room_id) + 1, sizeof(char));

    bb_room->item.iid = calloc(strlen(iid) + 1, sizeof(char));
    bb_room->item.upc = calloc(strlen(upc) + 1, sizeof(char));
    bb_room->item.desc = calloc(strlen(desc) + 1, sizeof(char));
    bb_room->item.quantity = calloc(strlen(quantity) + 1, sizeof(char));
    bb_room->item.purchase_price = calloc(strlen(purchase_price) + 1, sizeof(char));
    bb_room->item.detail = calloc(strlen(detail) + 1, sizeof(char));

    bb_room->bb.bathbody_brand = calloc(strlen(bathbody_brand) + 1, sizeof(char));
    bb_room->bb.feature = calloc(strlen(feature) + 1, sizeof(char));

    bb_room->room.desc = calloc(strlen(room_desc) + 1, sizeof(char));
  
    strncpy(bb_room->room.room_id, room_id, strlen(room_id));

    strncpy(bb_room->item.iid, iid, strlen(iid));
    strncpy(bb_room->item.upc, upc, strlen(upc));
    strncpy(bb_room->item.desc, desc, strlen(desc));
    strncpy(bb_room->item.quantity, quantity, strlen(quantity));
    strncpy(bb_room->item.purchase_price, purchase_price, strlen(purchase_price));
    strncpy(bb_room->item.detail, detail, strlen(detail));

    strncpy(bb_room->bb.bathbody_brand, bathbody_brand, strlen(bathbody_brand));
    strncpy(bb_room->bb.feature, feature, strlen(feature));
    
    strncpy(bb_room->room.desc, room_desc, strlen(room_desc));

    bb_room->room.room_id[strlen(room_id)] = '\0';

    bb_room->item.iid[strlen(iid)] = '\0';
    bb_room->item.upc[strlen(upc)] = '\0';
    bb_room->item.desc[strlen(desc)] = '\0';
    bb_room->item.quantity[strlen(quantity)] = '\0';
    bb_room->item.purchase_price[strlen(purchase_price)] = '\0';
    bb_room->item.detail[strlen(detail)] = '\0';

    bb_room->bb.bathbody_brand[strlen(bathbody_brand)] = '\0';
    bb_room->bb.feature[strlen(feature)] = '\0';
    
    bb_room->room.desc[strlen(desc)] = '\0';
  
    list_push_back(&item_rooms->item_room_list, &bb_room->node);
  }

  return item_rooms;
}

struct storings * storings_get_all()
{
  char buffer[BUF_LEN];
  sprintf(buffer, "SELECT room_id,iid,upc,description,quantity,purchase_price,detail,room_description FROM Item natural join Store natural join Room");
  return item_store_room_get(buffer);
}

struct item_rooms * get_elec_model_storings(char * model)
{
  char buffer[BUF_LEN];
  sprintf(buffer, "SELECT room_id,iid,upc,description,quantity,purchase_price,detail,serial_number,electronic_type,model,room_description FROM Item natural join Electronics natural join Store natural join Room where model = '%s'", 
                  model);
  return elec_store_room_get(buffer);
}

struct item_rooms * get_cloth_brand_storings(char * clothing_brand)
{
  char buffer[BUF_LEN];
  sprintf(buffer, "SELECT room_id,iid,upc,description,quantity,purchase_price,detail,clothing_brand,size,room_description FROM Item natural join Clothing natural join Store natural join Room where clothing_brand = '%s'", 
                  clothing_brand);
  return cloth_store_room_get(buffer);
}

struct item_rooms * get_bb_brand_storings(char * bathbody_brand)
{
  char buffer[BUF_LEN];
  sprintf(buffer, "SELECT room_id,iid,upc,description,quantity,purchase_price,detail,bathbody_brand,feature,room_description FROM Item natural join BathBody natural join Store natural join Room where bathbody_brand = '%s'", 
                  bathbody_brand);
  return bb_store_room_get(buffer);
}

int storing_modify(struct storing * storing, char * iid, char * room_id)
{
  char buffer[BUF_LEN];
  int error;

  sprintf(buffer, "Update Store SET iid=%s, room_id=%s where iid = '%s'", iid, room_id, storing->item.iid);
  if((error = db_query(buffer)) == 1062)
  {
    printf("You cannot store an item in more than one Room...\n");
    return 1;   
  }
  return 0;
}

int storing_delete(struct storing * storing)
{
  char buffer[BUF_LEN];

  sprintf(buffer, "DELETE FROM Store where iid = '%s'", storing->item.iid);
  db_query(buffer); 
  return 0;
}


int storings_delete(struct storings * storings)
{
  struct storing * storing;
  LIST_FOR_EACH(storing, struct storing, node, &storings->storing_list)
  {
    storing_delete(storing);
  }

  return 0;
}
