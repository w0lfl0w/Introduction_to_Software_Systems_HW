CC = gcc
CLINK = $(CC)
CFLAGS = -Wall -g -std=c99 
OBJS = grades.o 
RM = rm -f 

# linking operation
libgrades.so: $(OBJS)
	$(CLINK) -shared $(OBJS) -o libgrades.so -llinked-list -L.

# compilation
grades.o: grades.h grades.c 
	$(CC) $(CFLAGS) -c grades.c


# Custom rule - we can invoke it manually by running "make clean"
clean:
	$(RM) -fr *.o libgrades.so
	
