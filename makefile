CLAGS = -Wall -ansi -pedantic -Werror -g
OBJS = main.o map.o check.o laser.o enemy.o overlap.o refresh.o boundary.o direction.o linkedList.o instruction.o newSleep.o
CC = gcc
EXEC = laserTank

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) 
	
main.o: main.c map.h check.h laser.h enemy.h mirror.h overlap.h refresh.h boundary.h direction.h linkedList.h instruction.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h result.h
	$(CC) $(CFLAGS) -c map.c
	
check.o: check.c check.h 
	$(CC) $(CFLAGS) -c check.c

laser.o: laser.c laser.h map.h refresh.h newSleep.h 
	$(CC) $(CFLAGS) -c laser.c

enemy.o: enemy.c enemy.h map.h refresh.h newSleep.h
	$(CC) $(CFLAGS) -c enemy.c

overlap.o: overlap.c overlap.h 
	$(CC) $(CFLAGS) -c overlap.c
	
refresh.o: refresh.c refresh.h 
	$(CC) $(CFLAGS) -c refresh.c

boundary.o: boundary.c boundary.h 
	$(CC) $(CFLAGS) -c boundary.c

direction.o: direction.c direction.h
	$(CC) $(CFLAGS) -c direction.c 

linkedList.o: linkedList.c linkedList.h result.h
	$(CC) $(CFLAGS) -c linkedList.c
	
instruction.o: instruction.c instruction.h 
	$(CC) $(CFLAGS) -c instruction.c 
	
newSleep.o: newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

clean:
	rm -f $(OBJS) $(EXEC)
