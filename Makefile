CC = gcc
CFLAGS = -Wall
LDFLAGS = -L/usr/mysql
LDLIBS = -lmysqlclient

SRCS = main.c \
	update_employee.c \
	find_employee.c \
	delete_employee.c \
	insert_new_employee.c \
	read_all_employees.c \
	database_connection.c

OBJS = $(SRCS:.c=.o)
TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
