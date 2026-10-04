CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
OBJS = main.o utils.o employees.o budget.o suppliers.o assets.o reports.o

mfms: $(OBJS)
	$(CC) $(CFLAGS) -o mfms $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o mfms
