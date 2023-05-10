CXX		= g++
CLINK		= $(CXX)
CXXFLAGS	= -Wall -g -std=c++11 
OBJS		= ip.o port.o field.o string.o
RM 	     	= rm -f 
EXEC 		= firewall.exe

# linking operation
$(EXEC): main.o libfirewall.so libinput.so
	$(CXX) $(CXXFLAGS) main.o -o $(EXEC) -lfirewall -linput -L.

libfirewall.so: ip.o port.o field.o string.o
	$(CLINK) $(CXXFLAGS) -shared $(OBJS) -o libfirewall.so -L.

# compilation operation
main.o: main.cpp string.h field.h port.h ip.h input.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

ip.o: ip.cpp field.h string.h ip.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.h port.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

field.o: field.h field.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp
	
string.o: string.h string.cpp
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp


# Custom rule - we can invoke it manually by running "make clean"
clean:
	$(RM) -fr $(EXEC) *.o libfirewall.so
	
