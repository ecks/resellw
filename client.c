/* program testing connection to mysql 

/*To run the C code, use the commands:
/*setenv LD_LIBRARY_PATH /usr/local/mysql/lib/mysql
/*
/*gcc -m32 Cexample.c -I/usr/local/mysql/include/mysql -L/usr/local/mysql/lib/mysql -lmysqlclient
/*
/*./a.out


To compile:

gcc -m32 Cexample.c -I/usr/local/mysql/include/mysql 
           -L/usr/local/mysql/lib/mysql 
           -lmysqlclient

(The above should all be on one line.)

You will also need to execute the following line command:

setenv LD_LIBRARY_PATH /usr/local/mysql/lib/mysql

Documentation for the C API can be found at

http://dev.mysql.com/doc/refman/5.5/en/c.html

*/

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

int main(void) {
    MYSQL mysql, *sock;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *db = "asenovh";
    char *usr = "asenovh";
    char *pwd = "0920";

    char qbuffer[200];

    mysql_init(&mysql);
    if (!(sock = mysql_real_connect(&mysql,"localhost",usr,pwd,db,0,NULL,0))) {
        fprintf(stderr,"Couldn't connect to engine!\n%s\n\n",mysql_error(&mysql));
        perror("");
        exit(1);
    }
    mysql.reconnect = 1;

    sprintf(qbuffer,"show databases");
    printf(qbuffer);
    printf("\n");
    if(mysql_query(sock, qbuffer)) {
        fprintf(stderr, "Query failed (%s)\n",mysql_error(sock));
        exit(1);
    }
    if(!(res = mysql_store_result(sock))) {
        fprintf(stderr,"Couldn't get result from %s\n",mysql_error(sock));
        exit(1);
    }
    while (row = mysql_fetch_row(res)) {
        printf("Database: %s\n",row[0]);
    }
    mysql_free_result(res);

    sprintf(qbuffer,"use %s", db);
    printf(qbuffer);
    printf("\n");
    if(mysql_query(sock, qbuffer)) {
        fprintf(stderr, "Query failed (%s)\n",mysql_error(sock));
        exit(1);
    }

    sprintf(qbuffer,"create table test (a int, b char(5))");
    printf(qbuffer);
    printf("\n");
    if(mysql_query(sock, qbuffer)) {
        fprintf(stderr, "Query failed (%s)\n",mysql_error(sock));
        printf("Note from TA: Make sure your real programs can elegantly handle cases like this\n");
	//exit(1);
    }

    sprintf(qbuffer,"show tables");
    printf(qbuffer);
    printf("\n");
    if(mysql_query(sock, qbuffer)) {
        fprintf(stderr, "Query failed (%s)\n",mysql_error(sock));
        exit(1);
    }
    if(!(res = mysql_store_result(sock))) {
        fprintf(stderr,"Couldn't get result from %s\n",mysql_error(sock));
        exit(1);
    }
    while (row = mysql_fetch_row(res)) {
        printf("Table: %s\n",row[0]);
    }
    mysql_free_result(res);

    mysql_close(sock);
    exit(0);
}
