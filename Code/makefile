#Type ./ass in console to run the program.

PROG = ass
OBJS = main.o ScheduleController.o Schedule.o TravelAgent.o ServiceItem.o Route.o Aircraft.o Airport.o BookingManagerUI.o BookingManagerController.o ServiceManagerUI.o ServiceManagerController.o FlightManagerUI.o FlightManagerController.o ProfileManagerUI.o ProfileManagerController.o CustomerUI.o StaffUI.o GuestUI.o CustomerProfileController.o LoginController.o Staff.o Customer.o sqlite3.o TravelAgentUI.o 
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
