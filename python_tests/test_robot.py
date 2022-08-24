import os,sys

path = os.path.join(os.path.dirname(sys.path[0]))
sys.path.append(path)

from Components.robot import Robot,QueryEnv
from Components.grid import Grid,NORTH,SOUTH,EAST,WEST
from Graphic_Engine import Graphic_Engine
from MazeVis.main import get_test_grid,visually_edit_grid
                             
                             
                             
                             
                             
def test_robot_orientation():
    grid = Grid(get_test_grid(5))
    visually_edit_grid(grid) 
    qeu = QueryEnv(grid,(0,0),WEST)
    robot = Robot(qeu)
    robot.orient()
    visually_edit_grid(robot.grid)





def main():

    test_robot_orientation()
    



if __name__ == "__main__":
    main()
