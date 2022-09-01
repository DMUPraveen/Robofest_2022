INCLUDE_DIR := -I../
CC := g++
BIN := ./bin

$(BIN):
	mkdir $(BIN)

$(BIN)/test_utility: test_utility.cpp $(BIN) ../Utility.h ../Structures.h
	$(CC) $(INCLUDE_DIR) test_utility.cpp -o $(BIN)/test_utility


$(BIN)/testing_structures: testing_structures.cpp $(BIN) ../Structures.h 
	$(CC) $(INCLUDE_DIR) testing_structures.cpp -o $(BIN)/testing_structures


$(BIN)/Mazesolver.o:  ../Structures.h ../Utility.h ../Mazesolver.h ../Mazesolver.cpp $(BIN)
	$(CC) $(INCLUDE_DIR) -c ../Mazesolver.cpp -o $(BIN)/Mazesolver.o 

$(BIN)/test_maze_solver.o: test_maze_solver.cpp $(BIN)/Mazesolver.o
	$(CC) $(INCLUDE_DIR) -c test_maze_solver.cpp -o $(BIN)/test_maze_solver.o

$(BIN)/test_maze_solver: $(BIN)/test_maze_solver.o $(BIN)/Mazesolver.o
	$(CC) -o $(BIN)/test_maze_solver $(BIN)/test_maze_solver.o $(BIN)/Mazesolver.o

compile: $(BIN)/test_utility $(BIN)/testing_structures

test_maze_solver: $(BIN)/test_maze_solver
	$(BIN)/test_maze_solver
run: $(BIN)/test_utility $(BIN)/testing_structures
	$(BIN)/test_utility
	$(BIN)/testing_structures
