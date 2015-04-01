#Type ./ass in console to run the program.

PROG = ass
OBJS = main.o classes.o database.o flights.o permissions.o userInterface.o
CC = g++
CFLAGS = -ansi -pedantic -Wall

$(PROG) : $(OBJS) 
	$(CC) $(LFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -rf $(OBJS)

realclean:
	rm -rf $(PROG) $(OBJS) core

#default rule for cpp to .o
%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
