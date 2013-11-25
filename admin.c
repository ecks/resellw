#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>

#include "io.h"
#include "list.h"
#include "menu.h"
#include "item.h"
#include "room.h"
#include "price.h"
#include "store.h"
#include "listing.h"

int main(int argc, char * argv[])
{
  db_init();
  menu();
  db_close();
}
