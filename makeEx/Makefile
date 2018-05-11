#치환

		
OBJECTS = main.o print.o input.o
SRCS = $(OBJECTS:.o=.c)

CFLAGS = -g
TARGET = main
CC = gcc

#치환된 값은 $()를 이용
$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

#$< 현재 목표 파일(TARGET)보다 더 최근에 갱신된 파일명으로
#첫번째 종속물의 이름
.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(TARGET) $(OBJECTS) core

main.o : main.c
print.o : print.c
input.o : input.c

