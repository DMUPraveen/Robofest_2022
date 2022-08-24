
import sys, pygame
import os
import json

path = os.path.join(os.path.dirname(sys.path[0]))
sys.path.append(path)
# p=irint(sys.path)
from Graphic_Engine.Graphic_Engine import Graphic_Engine,calculate_origin,pixel_to_index,index_to_pixel
from Components.grid import Grid

DEFAULT_OUTPUT_FILE = "maze.json"

CELL_SIZE = 30
UNVISITED_CELL_COLOR = (255,255,255)
VISITED_CELL_COLOR = (0,0,255)
BACKGROUND_COLOR = (255,255,255)
WEAK_BOARDER = (122,122,122)
THICK_BOARDER = (0,0,0) 
BOARDER_THICKNESS = 2
WALL_THICKNESS = 4

SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT =1000,600
'''
characteristic  = 5bit integer
xxxxx
last four bits indicate whether there is a wall in one of the four cardinal directions
1st bit indicats whether the cell has been visited yet or not
more bits can be used for extra information if necessary after the 5th bit but these bits are reseved

|  1  |  2  |  3  |  4  |  5  |
|-----|-----|-----|-----|-----|
|visit|north|south|east |west |
|-----|-----|-----|-----|-----|

if visited the bit will be set 
if there is a wall in the x direction the xth bit will be set
'''
NORTH_OFFSET = 3
SOUTH_OFFSET = 2
EAST_OFFSET = 1
WEST_OFFSET = 0

def get_test_grid(n,chara = 0):
    grid =  [[chara]*n for _ in range(n)]
    for j in range(len(grid[0])):
        grid[0][j] |= 1 << NORTH_OFFSET 
        # print(bin(grid[0][j]),end=",")
        grid[-1][j] |= 1 << SOUTH_OFFSET
    for k in range(len(grid)):
        grid[k][0] |= 1 << WEST_OFFSET 
        grid[k][-1] |= 1 << EAST_OFFSET 
        pass
    return grid
def get_grid(infile):
    if(infile is None):
        n = int(input("What should the dimension of the grid be?: "))
        return get_test_grid(n)
    
    with open(infile) as f:
        return json.loads(f.read())


def transform_grid(grid,tf):
    return [[tf(i) for i in row] for row in grid]
def output_grid(grid,outputfile=DEFAULT_OUTPUT_FILE):
    with open(DEFAULT_OUTPUT_FILE,"w+") as f:

        f.write(json.dumps(transform_grid(grid,lambda x:x)))

def parse_arguments(argv):
    outfile = DEFAULT_OUTPUT_FILE
    infile = None
    if(len(argv)>1):
        outfile = argv[1]
    if(len(argv) >2):
        infile = argv[2]
    return outfile,infile
def visually_edit_grid(grid:Grid):
    pygame.init()
    screen = pygame.display.set_mode(SCREEN_SIZE)
    last_clicked_location = None

    adjacent_cells = []
    origin = calculate_origin(screen,grid.get_height())
    Running = True
    gfx = Graphic_Engine(screen,origin)
    while Running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                Running =False
                break

            if event.type == pygame.MOUSEBUTTONDOWN:
                last_clicked_location = event.pos
            if event.type == pygame.MOUSEBUTTONUP:
                if(last_clicked_location is not None):
                    adjacent_cells.append(last_clicked_location)
                    last_clicked_location = None
        if len(adjacent_cells) >=2:
            # print(adjacent_cells)
            a,b = adjacent_cells[:2]
            adjacent_cells.clear()
            a,b = pixel_to_index(origin,*a),pixel_to_index(origin,*b)
            grid.make_wall(a,b)

        
        
        screen.fill(BACKGROUND_COLOR)
        gfx.draw_grid(grid)
        pygame.display.flip()
    pygame.quit()


def main():
    
    outfile, infile = parse_arguments(sys.argv)
    grid =  Grid(get_grid(infile))
    visually_edit_grid(grid)
    output_grid(grid.grid,outfile)



if __name__ == "__main__":
    main()