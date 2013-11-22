CC = gcc
CXX = g++
CFLAGS = -m32 -I/usr/local/mysql/include/mysql -I./lib
LIBS = -L/usr/local/mysql/lib/mysql -lmysqlclient
EXECUTABLE = client admin
SRCS = menu.c item.c room.c price.c io.c store.c listing.c
OBJECTS = ${SRCS:.c=.o}
VPATH = ./lib

CFLAGS_CPPUTEST = -I/usa/hasenov/cpputest_lib/include
CFLAGS_LIBS = -L/usa/hasenov/cpputest_lib/lib -lstdc++ -lCppUTest -lCppUTestExt


all: ${EXECUTABLE}

client:
	${CC} ${CFLAGS} -o $@ client.c ${LIBS}

admin: admin.o ${OBJECTS}
	${CC} ${CFLAGS} -o $@ admin.o ${OBJECTS} ${LIBS}

test: all
	${CXX} $(CFLAGS_CPPUTEST) -o $@ tests/database_test_run.cpp tests/database_test.cpp $(CFLAGS_LIBS)

menu.o: menu.c
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

clean:
	rm -f *.o ${EXECUTABLE}