#include <mysql.h>

#include "db.h"
#include "client_menu.h"

int main(int argc, char * argv[])
{
  db_init();
  client_menu();
  db_close();
}
