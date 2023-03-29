CC = clang++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address -pthread
LFLAGS = 

EXEC = sort
OBJECTS = sort.o merge.o

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean: tidy
	rm -f $(EXEC)

tidy:
	rm -f $(OBJECTS)

format:
	clang-format -i -style=file *.cpp *.h
