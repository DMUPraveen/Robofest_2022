INCLUDE_DIR := -I../
CC := g++
BIN := ./bin

$(BIN):
	mkdir $(BIN)

$(BIN)/test_utility: test_utility.cpp $(BIN) ../Utility.h ../Structures.h
	$(CC) $(INCLUDE_DIR) test_utility.cpp -o $(BIN)/test_utility


$(BIN)/testing_structures: testing_structures.cpp $(BIN) ../Structures.h 
	$(CC) $(INCLUDE_DIR) testing_structures.cpp -o $(BIN)/testing_structures




$(BIN)/test_maze_solver: test_maze_solver.cpp ../Mazesolver.h
	$(CC) $(INCLUDE_DIR) -o $(BIN)/test_maze_solver test_maze_solver.cpp 

compile: $(BIN)/test_utility $(BIN)/testing_structures

test_maze_solver: $(BIN)/test_maze_solver
	$(BIN)/test_maze_solver



run: $(BIN)/test_utility $(BIN)/testing_structures
	$(BIN)/test_utility
	$(BIN)/testing_structures

clean: $(BIN)
	rm $(BIN)/*