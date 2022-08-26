import os,sys

path = os.path.join(os.path.dirname(sys.path[0]))
sys.path.append(path)

from Components.grid import Grid
from MazeVis.main import get_test_grid,visually_edit_grid
from random import choice

def get_neighbours(curent):
    i,j = curent
    dds = [(-1,0),(1,0),(0,1),(0,-1)]
    nes = []
    for di,dj in dds:
        nes.append((i+di,j+dj))
    return nes
        
        

def dfs_make(grid:Grid):
    visited = set()
    stack = []
    current = (0,0)
    visited.add(current)
    stack.append(current)
    within = lambda positions : [position for position in positions if (0<=position[0]<grid.get_height() and 0<=position[1]<grid.get_wdith())]
    notvisited = lambda positions :[position for position in positions if position not in visited]
    
    while(stack):
        current = stack[-1] 

        nes = notvisited(within(get_neighbours(current)))
        if(nes):
            ne = choice(nes)
            grid.make_wall(current,ne)
            stack.append(ne)
            visited.add(ne)
        else:
            stack.pop(-1) #no unvisited neighbours found popping from the stack
            

def mazmake(n):
    grid = Grid(get_test_grid(n,0b01111))#a grid with all four walls made
    dfs_make(grid)
    visually_edit_grid(grid)




def main():
    mazmake(14)



if __name__ == "__main__":
    main()