CC = gcc
CFLAGS = --std=c11 -pedantic -Wall -Wuninitialized -Wno-missing-braces -Wno-implicit-function-declaration
LIBRARIES = -lm
TESTBINARIES = 4_test
BINARIES = 4 $(TESTBINARIES)
HEADERS = $(wildcard *.h)

.PHONY: all clean compile test checkstyle

all: clean checkstyle compile test

compile: $(BINARIES)

4: vier_gewinnt.o vier_gewinnt_main.o
	$(CC) $(CFLAGS) $(LIBRARIES) $^ -o $@

4_test: vier_gewinnt.o vier_gewinnt_test.o
	$(CC) $(CFLAGS) $(LIBRARIES) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTBINARIES)
	for test in $(TESTBINARIES); do ./$$test; done

clean:
	rm -f $(BINARIES) *.o
	rm -rf .vscode/
	rm -rf .vscode
	rm -rf .vs

clean_games:
	rm -rf .sav

checkstyle:
	python3 cpplint.py --repository=. --filter=-runtime/int,-readability/casting,-runtime/threadsafe_fn,-build/include_subdir *.c *.h
