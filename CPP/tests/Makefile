INCLUDE_DIR := -I../
CC := g++
BIN := ./bin

$(BIN):
	mkdir $(BIN)

$(BIN)/test_utility: test_utility.cpp $(BIN) ../Utility.h ../Structures.h
	$(CC) $(INCLUDE_DIR) test_utility.cpp -o $(BIN)/test_utility


$(BIN)/testing_structures: testing_structures.cpp $(BIN) ../Structures.h 
	$(CC) $(INCLUDE_DIR) testing_structures.cpp -o $(BIN)/testing_structures


compile: $(BIN)/test_utility $(BIN)/testing_structures
run: $(BIN)/test_utility $(BIN)/testing_structures
	$(BIN)/test_utility
	$(BIN)/testing_structures
