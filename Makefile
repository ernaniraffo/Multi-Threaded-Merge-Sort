CC = clang++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror
LFLAGS = 

EXEC = sort
OBJECTS = sort.o quick.o merge.o

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean: tidy
	rm -f $(EXEC)

tidy:
	rm -f $(OBJECTS)
