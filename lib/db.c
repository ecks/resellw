#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "db.h"

MYSQL * sock;
MYSQL mysql;

int db_init()
{
  char *db = "asenovh";
  char *usr = "asenovh";
  char *pwd = "0920";  // lol, now everybody on github can see my password

  char qbuffer[200];

  mysql_init(&mysql);
  if (!(sock = mysql_real_connect(&mysql,"localhost",usr,pwd,db,0,NULL,0))) 
  {
    fprintf(stderr,"Couldn't connect to engine!\n%s\n\n",mysql_error(&mysql));
    perror("");
    exit(1);
  }
  mysql.reconnect = 1;

  sprintf(qbuffer,"use %s", db);
  if(mysql_query(sock, qbuffer)) 
  {
    fprintf(stderr, "Query failed (%s)\n",mysql_error(sock));
    exit(1);
  }


  return 0;
}

int db_query(char * buffer)
{
  if(mysql_query(sock, buffer))
  {
    fprintf(stderr, "Query failed (%s)\n",mysql_error(sock));
    exit(1);
  }

  return 0;
}

MYSQL_RES * db_get_res()
{
  MYSQL_RES * res;
  if(!(res = mysql_store_result(sock))) 
  {
    fprintf(stderr,"Couldn't get result from %s\n",mysql_error(sock));
    exit(1);
  }

  return res;
}

MYSQL_RES * db_query_res(char * buffer)
{
  db_query(buffer);
  return db_get_res();
}

int db_close()
{
  mysql_close(sock);
  return 0;
}
