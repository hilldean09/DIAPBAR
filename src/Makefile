
CC = g++
CFLAGS = -Wall -pedantic
OBJS = diapbar_core.o test_diapbar.o
EXECS = test_diapbar

testers : test_diapbar

test_diapbar : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test_diapbar

diapbar_core.o : diapbar_core.cpp diapbar_core.hpp
	$(CC) $(CFLAGS) -c diapbar_core.cpp

test_diapbar.o : test_diapbar.cpp diapbar.hpp
	$(CC) $(CFLAGS) -c test_diapbar.cpp

diapbar.hpp : diapbar.cpp

clean :
	rm $(OBJS) $(EXECS)


