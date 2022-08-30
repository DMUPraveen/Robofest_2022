INCLUDE_DIR := -I../
CC := g++
BIN := ./bin

$(BIN):
	mkdir $(BIN)

$(BIN)/test_utility: test_utility.cpp $(BIN) ../Utility.h ../Structures.h
	$(CC) $(INCLUDE_DIR) test_utility.cpp -o $(BIN)/test_utility
compile: $(BIN)/test_utility
run: $(BIN)/test_utility
	$(BIN)/test_utility