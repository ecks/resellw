CC = gcc
CXX = g++
CFLAGS = -m32 -I/usr/local/mysql/include/mysql
LIBS = -L/usr/local/mysql/lib/mysql -lmysqlclient
EXECUTABLE = client

CFLAGS_CPPUTEST = -I/usa/hasenov/cpputest_lib/include
CFLAGS_LIBS = -L/usa/hasenov/cpputest_lib/lib -lstdc++ -lCppUTest -lCppUTestExt


all: ${EXECUTABLE}

client:
	${CC} ${CFLAGS} -o $@ client.c ${LIBS}

test: all
	${CXX} $(CFLAGS_CPPUTEST) -o $@ tests/database_test_run.cpp tests/database_test.cpp $(CFLAGS_LIBS)
