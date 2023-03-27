CC = clang++
CFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsanitize=address -pthread
LFLAGS = 

EXEC = sort
OBJECTS = sort.o merge.o threads.o

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean: tidy
	rm -f $(EXEC)

tidy:
	rm -f $(OBJECTS)

writeup: writeup.tex
	pdflatex writeup.tex

cleantex: tidytex
	rm -f writeup.pdf

tidytex:
	rm -f time-eps-converted-to.pdf *.log *.aux

format:
	clang-format -i -style=file *.cpp *.h
