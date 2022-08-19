import sys, pygame
pygame.init()

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
def calculate_origin(grid_size):
    grid_length = grid_size*CELL_SIZE
    return (
        (SCREEN_WIDTH - grid_length)//2,
        (SCREEN_HEIGHT -  grid_length)//2
    )

def index_to_pixel(origin,i,j):
    x_0 ,y_0 = origin
    return (
        x_0 + i*CELL_SIZE,
        y_0 +j*CELL_SIZE
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

def draw_walls(corner_pos,chara,screen):
    northwall = bool(chara& (1<<3))
    southwall = bool(chara& (1<<2))
    eastwall = bool(chara& (1<<1))
    westwall = bool(chara& (1<<0))
    walls = [northwall,southwall,eastwall,westwall]
    wall_positions = [
        (index_to_pixel(corner_pos,0,0),index_to_pixel(corner_pos,1,0)),#northwall
        (index_to_pixel(corner_pos,0,1),index_to_pixel(corner_pos,1,1)),#southwall
        (index_to_pixel(corner_pos,1,0),index_to_pixel(corner_pos,1,1)),#eastwall
        (index_to_pixel(corner_pos,0,0),index_to_pixel(corner_pos,0,1))#westwall
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
    return [[chara]*n for _ in range(n)]

def main():
    screen = pygame.display.set_mode(SCREEN_SIZE)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: sys.exit()
        
        
        screen.fill(BACKGROUND_COLOR)
        test_grid = get_test_grid(16,0b01000)
        draw_grid(test_grid,screen) 
        pygame.display.flip()




if __name__ == "__main__":
    main()