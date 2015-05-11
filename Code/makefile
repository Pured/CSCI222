#Type ./ass in console to run the program.

PROG = ass
OBJS = main.o Schedule.cpp TravelAgent.cpp ServiceItem.cpp route.cpp Aircraft.cpp Airport.cpp BookingManagerUI.cpp ServiceManagerUI.cpp FlightManagerUI.cpp ProfileManagerUI.cpp CustomerUI.o  \
				StaffUI.o GuestUI.o CustomerProfileController.o LoginController.o Staff.o Customer.o sqlite3.o
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
