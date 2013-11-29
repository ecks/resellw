CC = gcc
CXX = g++
CFLAGS = -ggdb -m32 -I/usr/local/mysql/include/mysql -I. -I./lib
LIBS = -L/usr/local/mysql/lib/mysql -lmysqlclient
EXECUTABLE = client admin
SRCS = menu_common.c admin_menu.c client_menu.c item.c room.c price.c io.c list.c db.c store.c listing.c
OBJECTS = ${SRCS:.c=.o}
VPATH = ./lib

CFLAGS_CPPUTEST = -I/usa/hasenov/cpputest_lib/include ${CFLAGS}
LIBS_CPPUTEST = -L/usa/hasenov/cpputest_lib/lib -lstdc++ -lCppUTest -lCppUTestExt ${LIBS}


all: ${EXECUTABLE}

client: client.o ${OBJECTS}
	${CC} ${CFLAGS} -o $@ client.c ${OBJECTS} ${LIBS}

admin: admin.o ${OBJECTS}
	${CC} ${CFLAGS} -o $@ admin.o ${OBJECTS} ${LIBS}

test: all 
	${CXX} $(CFLAGS_CPPUTEST) -o $@ tests/database_test_run.cpp tests/database_test.cpp ${OBJECTS} $(LIBS_CPPUTEST)

menu_common.o: menu_common.c
	${CC} ${CFLAGS} -c $^

admin_menu.o: admin_menu.c
	${CC} ${CFLAGS} -c $^

client_menu.o: client_menu.c
	${CC} ${CFLAGS} -c $^

item.o: item.c
	${CC} ${CFLAGS} -c $^

room.o: room.c
	${CC} ${CFLAGS} -c $^

price.o: price.c
	${CC} ${CFLAGS} -c $^

store.o: store.c
	${CC} ${CFLAGS} -c $^

listing.o: listing.c
	${CC} ${CFLAGS} -c $^

io.o: io.c
	${CC} ${CFLAGS} -c $^

list.o: list.c
	${CC} ${CFLAGS} -c $^

db.o: db.c
	${CC} ${CFLAGS} -c $^

clean:
	rm -f *.o ${EXECUTABLE}
