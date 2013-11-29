#include <mysql.h>

#include "db.h"
#include "admin_menu.h"

int main(int argc, char * argv[])
{
  db_init();
  admin_menu();
  db_close();
}
