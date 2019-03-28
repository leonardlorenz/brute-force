SRC="./src/"
BIN="./bin/"

SRCFILES="$(SRC)bruteforce.c"

compile:
	clang $(SRCFILES) -o $(BIN)bruteforce

run:
	$(BIN)bruteforce $1 $2

debug:
	clang -g $(SRCFILES) -o $(BIN)bruteforce
	gdb $(BIN)bruteforce $(bin)password 6
