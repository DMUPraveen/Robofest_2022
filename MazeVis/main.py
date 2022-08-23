import sys, pygame
import json

OUTPUT_FILE = "maze.json"

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
def calculate_origin(grid_size):
    grid_length = grid_size*CELL_SIZE
    return (
        (SCREEN_WIDTH - grid_length)//2,
        (SCREEN_HEIGHT -  grid_length)//2
    )

def index_to_pixel(origin,i,j):
    x_0 ,y_0 = origin
    return (
        x_0 + j*CELL_SIZE,
        y_0 +i*CELL_SIZE,
    )
def draw_cell(corner_pos,chara,screen):
    '''
    draws a squre cell of at position i,j with the characatereistc chara
    '''
    visited = bool(chara& (1<<4))

    
    cell_color = VISITED_CELL_COLOR if visited else UNVISITED_CELL_COLOR
   
    #draw the filled cell
    pygame.draw.rect(screen,cell_color,(*index_to_pixel(corner_pos,0,0),CELL_SIZE,CELL_SIZE)) 

    #draw weak boarders for clarity
    pygame.draw.rect(screen,WEAK_BOARDER,(*index_to_pixel(corner_pos,0,0),CELL_SIZE,CELL_SIZE),BOARDER_THICKNESS) 

def make_wall_helper(grid,a,b):
    '''
    sets the wal
    '''
    WALL_MAP = {
        (-1,0):SOUTH_OFFSET,
        (1,0):NORTH_OFFSET,
        (0,-1):EAST_OFFSET,
        (0,1):WEST_OFFSET
    }

    key = tuple(a[i] -b[i] for i in range(2))
    if key in WALL_MAP:
        grid[a[0]][a[1]] ^= 1 << WALL_MAP[key]

def make_wall(grid,a,b):
    if not(0<=a[0]<len(grid) and 0<=a[1]<len(grid[0])):
        return 
    if not(0<=b[0]<len(grid) and 0<=b[1]<len(grid[0])):
        return

    make_wall_helper(grid,a,b)
    make_wall_helper(grid,b,a)


def pixel_to_index(origin,x,y):
    i = (x - origin[0])//CELL_SIZE
    j = (y - origin[1])//CELL_SIZE
    return (j,i)



def draw_walls(corner_pos,chara,screen):
    northwall = bool(chara& (1<<3))
    southwall = bool(chara& (1<<2))
    eastwall = bool(chara& (1<<1))
    westwall = bool(chara& (1<<0))
    walls = [northwall,southwall,eastwall,westwall]
    wall_positions = [
        (index_to_pixel(corner_pos,0,0),index_to_pixel(corner_pos,0,1)),#northwall
        (index_to_pixel(corner_pos,1,0),index_to_pixel(corner_pos,1,1)),#southwall
        (index_to_pixel(corner_pos,0,1),index_to_pixel(corner_pos,1,1)),#eastwall
        (index_to_pixel(corner_pos,0,0),index_to_pixel(corner_pos,1,0))#westwall
    ]
    for wall,(s,e) in zip(walls,wall_positions):
        if(wall):
            pygame.draw.line(screen,THICK_BOARDER,s,e,WALL_THICKNESS)



def draw_grid(grid,screen):
    origin = calculate_origin(len(grid))
    itop = lambda x,y : index_to_pixel(origin,x,y)
    for i,row in enumerate(grid):
        for j,chara in enumerate(row):
            draw_cell(itop(i,j),chara,screen)
    for i,row in enumerate(grid):
        for j,chara in enumerate(row):
            draw_walls(itop(i,j),chara,screen)


def get_test_grid(n,chara = 0):
    grid =  [[chara]*n for _ in range(n)]
    for j in range(len(grid[0])):
        grid[0][j] |= 1 << NORTH_OFFSET 
        print(bin(grid[0][j]),end=",")
        grid[-1][j] |= 1 << SOUTH_OFFSET
    for k in range(len(grid)):
        grid[k][0] |= 1 << WEST_OFFSET 
        grid[k][-1] |= 1 << EAST_OFFSET 
        pass
    return grid

def transform_grid(grid,tf):
    return [[tf(i) for i in row] for row in grid]
def output_grid(grid):
    with open(OUTPUT_FILE,"w+") as f:

        f.write(json.dumps(transform_grid(grid,bin)))

def main():

    pygame.init()
    screen = pygame.display.set_mode(SCREEN_SIZE)
    grid = get_test_grid(2,0b00000)
    last_clicked_location = None
    adjacent_cells = []
    origin = calculate_origin(len(grid))
    Running = True
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
            print(adjacent_cells)
            a,b = adjacent_cells[:2]
            adjacent_cells.clear()
            a,b = pixel_to_index(origin,*a),pixel_to_index(origin,*b)
            make_wall(grid,a,b)  


        
        
        screen.fill(BACKGROUND_COLOR)
        draw_grid(grid,screen) 
        pygame.display.flip()

    output_grid(grid)



if __name__ == "__main__":
    main()