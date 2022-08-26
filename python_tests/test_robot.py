import os,sys

path = os.path.join(os.path.dirname(sys.path[0]))
sys.path.append(path)

from Components.robot import Robot,QueryEnv
from Components.grid import Grid,NORTH,SOUTH,EAST,WEST
from Graphic_Engine.Graphic_Engine import Graphic_Engine,calculate_origin
from MazeVis.main import get_test_grid,visually_edit_grid,get_grid
import pygame                             
import logging
logging.basicConfig(level="INFO")



def visually_test_robot(robot:Robot):
    SIMULATE_NEXT_KEY = 'a'
    pygame.init()
    BACKGROUND_COLOR = (255,255,255)
    SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT =1000,600
    screen = pygame.display.set_mode(SCREEN_SIZE)

    origin = calculate_origin(screen,robot.grid.get_wdith(),robot.grid.get_height())
    Running = True
    gfx = Graphic_Engine(screen,origin)
    while Running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                Running =False
                break
            if event.type == pygame.KEYDOWN:
                if(event.unicode == SIMULATE_NEXT_KEY):
                    if(robot.search()):
                        logging.info(f"robot search is finished")
                    logging.info(f"robot bfs count is {robot.bfs_count}")
        
        
        screen.fill(BACKGROUND_COLOR)
        gfx.draw_grid(robot.grid)
        gfx.draw_robot(robot)
        pygame.display.flip()
    pygame.quit()
    

                             
                             
                             
def test_robot_orientation():
    grid = Grid(get_test_grid(6))
    visually_edit_grid(grid) 
    qeu = QueryEnv(grid,(0,0),EAST)

    robot = Robot(qeu)
    robot.orient()
    if(robot.centers is not None):
        for i,j in robot.centers:
            robot.grid.set_visited(i,j)
    visually_edit_grid(robot.grid)

def test_dfs(grid:Grid):

    qeu = QueryEnv(grid,(0,0),EAST)

    robot = Robot(qeu)
    robot.orient()
    visually_test_robot(robot)



def main():

    grid = get_test_grid(6)
    if(len(sys.argv) >1):
        inputfile = sys.argv[1]
        grid = get_grid(inputfile) 
    
    grid =Grid(grid)
    visually_edit_grid(grid) 
    test_dfs(grid)
    



if __name__ == "__main__":
    main()
