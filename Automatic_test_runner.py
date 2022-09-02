from Maze_Maker.main import mazmake
from MazeVis.main import output_grid
import os
import sys

TEMP_MAZE_FILE = "mazes\\\\current_testing_maze.json"
CYCLES = 50 
OUTPUT_FILE = "test_output\\\\automated_test.txt"
def main():
    iterations = int(input("How may iterations to run? "))
    with open(OUTPUT_FILE.replace("\\\\","\\"),"w+") as f:
        pass

    for _ in range(iterations):
        g = mazmake(14,CYCLES,False)
        output_grid(g.grid,TEMP_MAZE_FILE)
        # print(   
        # f"wsl python3 interactive_runner.py python.exe Control_Emulator.py {TEMP_MAZE_FILE} {OUTPUT_FILE} -- CPP/tests/bin/test_maze_solver"
        # )
        os.system(
            
        f"wsl python3 interactive_runner.py python.exe Control_Emulator.py {TEMP_MAZE_FILE} {OUTPUT_FILE} -- CPP/tests/bin/test_maze_solver"
        )

if __name__ == "__main__":
    main()

    


