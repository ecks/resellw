#ifndef DB_H
#define DB_H

extern int db_init();
extern int db_close();
extern int db_query(char * buffer);
extern MYSQL_RES * db_query_res(char * buffer);

#endif
