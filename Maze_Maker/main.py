import os
import sys

path = os.path.join(os.path.dirname(sys.path[0]))
sys.path.append(path)

from Components.grid import Grid, NORTH, SOUTH, EAST, WEST
from random import choice, randint
from MazeVis.main import get_test_grid, visually_edit_grid,output_grid
from Components.robot import DIRECTION_MAP


def get_neighbours(curent):
    i, j = curent
    dds = [(-1, 0), (1, 0), (0, 1), (0, -1)]
    nes = []
    for di, dj in dds:
        nes.append((i+di, j+dj))
    return nes


def dfs_make(grid: Grid):
    visited = set()
    stack = []
    current = (0, 0)
    visited.add(current)
    stack.append(current)

    def within(positions): return [position for position in positions if (
        0 <= position[0] < grid.get_height() and 0 <= position[1] < grid.get_wdith())]
    def notvisited(positions): return [
        position for position in positions if position not in visited]

    while(stack):
        current = stack[-1]

        nes = notvisited(within(get_neighbours(current)))
        if(nes):
            ne = choice(nes)
            grid.make_wall(current, ne)
            stack.append(ne)
            visited.add(ne)
        else:
            # no unvisited neighbours found popping from the stack
            stack.pop(-1)


def cycle_adder(acyclic_maze: Grid, number_of_walls_to_remove):
    count = 0
    while (count != number_of_walls_to_remove):
        i, j = (randint(1, acyclic_maze.get_height()-2),
                randint(1, acyclic_maze.get_wdith()-2))
        walls = [wall[0] for wall in zip(
            (NORTH, SOUTH, EAST, WEST), acyclic_maze.get_walls(i, j)) if wall[1]]
        if(walls):
            wall = choice(walls)
            (di, dj) = DIRECTION_MAP[wall]
            ne = (i+di, j+dj)
            acyclic_maze.make_wall((i,j),ne)
            count +=1


def mazmake(maze_size,cycles_to_add=0):
    grid = Grid(get_test_grid(maze_size, 0b01111))  # a grid with all four walls made
    dfs_make(grid)
    visually_edit_grid(grid)
    cycle_adder(grid,cycles_to_add)
    visually_edit_grid(grid)
    return grid

def main():
    dimensions_of_the_grid = int(input("Dimensions of the grid: "))
    number_of_cycles = int(input("Number of cycles: "))

    maze = mazmake(dimensions_of_the_grid,number_of_cycles)
    if(len(sys.argv) >1):
        file_name = sys.argv[1]
        output_grid(maze.grid,file_name)


if __name__ == "__main__":
    main()
