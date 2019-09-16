SRC=./src/
BIN=./bin/
DBG=./dbg/

SRCFILES="$(SRC)bruteforce.c"

compile:
	clang $(SRCFILES) -o $(BIN)bruteforce

run:
	$(BIN)bruteforce password.txt 6

debug:
	clang -g $(SRCFILES) -o $(DBG)bruteforce
	gdb $(DBG)bruteforce password.txt 6
