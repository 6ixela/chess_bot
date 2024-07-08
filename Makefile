CC=gcc
CFLAGS=-Wextra -Wall
VPATH = src

TARGET_EXE = main
LDFLAGS= 
OBJS = main.o

all: $(TARGET_EXE)
$(TARGET_EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: $(TARGET_EXE)

clean:
	$(RM) $(OBJS) $(TARGET_EXE)