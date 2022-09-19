import os
from time import sleep
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame
import sys
import serial
import struct
from random import choice,randint
from Components.grid import Grid,NORTH,EAST,WEST,SOUTH
from Components.robot import DIRECTION_MAP,FORWARD,BACKWARD,TURN_BACK,TURN_LEFT,TURN_RIGHT,OPPOSITE_MAP,LEFT_MAP, RIGHT_MAP,Robot
from Graphic_Engine.Graphic_Engine import Graphic_Engine,calculate_origin
from MazeVis.main import get_grid

class QueryEnv:
    def __init__(self, grid: Grid, position, orientation):
        '''
        grid->the envrionment the robot will be navigating in
        position -> true position of the robot relative to the enviroment origin
        orientatrion->true orientation of the robot relative to north of the grid

        '''
        self.env = grid
        self.i = position[0]
        self.j = position[1]
        self.orientation = orientation

    def get_dimensions(self):
        return self.env.get_height()

    def _update_delta(self, move_direction):
        is_wall = self.env.get_bit(self.i, self.j, move_direction)
        if(not is_wall):
            di, dj = DIRECTION_MAP[move_direction]
            self.i, self.j = self.i+di, self.j+dj
            return
        raise Exception("Robot has requested an illegal move")

    def update(self, move):
        if(move == FORWARD):
            self._update_delta(self.orientation)
        if(move == BACKWARD):
            self._update_delta(OPPOSITE_MAP[self.orientation])
        if(move == TURN_BACK):
            self.orientation = OPPOSITE_MAP[self.orientation]
        if(move == TURN_LEFT):
            self.orientation = LEFT_MAP[self.orientation]
        if(move == TURN_RIGHT):
            self.orientation = RIGHT_MAP[self.orientation]

    def query(self):
        '''
        returns the state of the walls in the following order
        left ,front, right
        '''
        front = self.env.get_bit(self.i, self.j, self.orientation)
        right = self.env.get_bit(self.i, self.j, RIGHT_MAP[self.orientation])
        left = self.env.get_bit(self.i, self.j, LEFT_MAP[self.orientation])
        return left, front, right

    def query_dimensions(self):
        '''
        return the dimensions of the maze the robot is currently in
        '''
        return self.env.get_height()


def visualize(que:QueryEnv):
    BACKGROUND_COLOR = (255,255,255)
    SCREEN_SIZE = SCREEN_WIDTH, SCREEN_HEIGHT =1000,600
    screen = pygame.display.set_mode(SCREEN_SIZE)

    origin = calculate_origin(screen,que.env.get_wdith(),que.env.get_height())
    gfx = Graphic_Engine(screen,origin)
    Running = True 
    while(Running):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                Running =False
        
        screen.fill(BACKGROUND_COLOR)
        gfx.draw_grid(que.env)
        
        robot = Robot(que) 
        robot.i = que.i       
        robot.j = que.j
        robot.orientation = que.orientation

        gfx.draw_robot(robot)
        pygame.display.flip()

    pygame.quit()

command_map = {
    "FORWARD":FORWARD,
    "BACKWARD":BACKWARD,
    "TURN_BACK":TURN_BACK,
    "TURN_RIGHT":TURN_RIGHT,
    "TURN_LEFT":TURN_LEFT
}



orientation_string_map = {
    NORTH : "NORTH",
    SOUTH : "SOUTH",
    EAST : "EAST",
    WEST : "WEST"
}
f = lambda x : 1 if x>0 else 0

def main():
    grid = get_grid(sys.argv[1]) 
    position = (choice((0,13)),choice((0,13))) 
    orientation = choice((EAST,NORTH,SOUTH,WEST))
    position = (13,13)
    orientation = WEST
    que = QueryEnv(Grid(grid),position,orientation) 
    ser = serial.Serial(sys.argv[2],9600)
    sleep(1)
    def output(wall_list):
        a = 0
        for stat in wall_list:
            a = a << 1
            a += stat
        v = struct.pack('c',a)
    def input():
        return ser.readline().decode('utf-8')
    
    while True:
        visualize(que)
        command = input()
        if(command == "?"):
            output(tuple(f(i) for i in que.query()))
            print(" ".join(str(f(i)) for i in que.query()))
        elif(command == "end"):
            print(f"{[que.i,que.j]} with initial position {position} and orietntation {orientation_string_map[orientation]} --  OK\n")
            break
        else:
            try:
                que.update(command_map[command])
            except KeyError:
                raise Exception(f"{position},{orientation}")
            
    return 0


if __name__ == "__main__":
    main()