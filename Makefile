CC = clang++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address -pthread
LFLAGS = 

EXEC = sort
OBJECTS = sort.o merge.o numgen.o arraygen.o
TEST_OBJECTS = test.o numgen.o arraygen.o

all: clean sort

sort: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean: tidy
	rm -f sort test

tidy:
	rm -f *.o

format:
	clang-format -i -style=file *.cpp *.h
