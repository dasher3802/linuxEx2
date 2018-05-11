#Makefile
.SUFFIXES : .c .o

CC = gcc
OBJECTS = upper.o useupper.o
TARGET = upper useupper
all : $(TARGET)

upper : upper.c
	$(CC) -o $@ $<

useupper : useupper.c
	$(CC) -o $@ $<

clean :
	$(RM) $(OBJECTS) $(TARGET)
