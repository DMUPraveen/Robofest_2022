from Maze_Maker.main import mazmake
from MazeVis.main import output_grid
import os

TEMP_MAZE_FILE = "mazes\\\\current_testing_maze.json"
CYCLES = 20
OUTPUT_FILE = "test_output\\\\automated_test.txt"
def main():
    g = mazmake(14,CYCLES,False)
    output_grid(g.grid,TEMP_MAZE_FILE)
    print(   
    f"wsl python3 interactive_runner.py python.exe Control_Emulator.py {TEMP_MAZE_FILE} {OUTPUT_FILE} -- CPP/tests/bin/test_maze_solver"
    )
    os.system(
        
    f"wsl python3 interactive_runner.py python.exe Control_Emulator.py {TEMP_MAZE_FILE} {OUTPUT_FILE} -- CPP/tests/bin/test_maze_solver"
    )

if __name__ == "__main__":
    main()

    


