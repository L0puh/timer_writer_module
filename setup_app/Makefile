CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = setup_app
OBJS = setup_app.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
