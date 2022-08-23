from Components.grid import Grid,NORTH,SOUTH,EAST,WEST
from typing import Dict,Tuple


DIRECTION_MAP:Dict[int,Tuple[int,int]] = {
    NORTH : (-1,0),
    SOUTH : (1,0),
    EAST : (0,1),
    WEST : (1,0),
}

OPPOSITE_MAP = {
    NORTH : SOUTH,
    SOUTH  : NORTH,
    WEST : EAST,
    EAST : WEST
}
LEFT_MAP = {
    NORTH : WEST,
    WEST : SOUTH,
    SOUTH : EAST,
    EAST : NORTH
}
RIGHT_MAP = {
      WEST:NORTH,
      SOUTH:WEST,
      EAST:SOUTH,
      NORTH:EAST,
}
FORWARD = 0
BACKWARD= 1
TURN_RIGHT = 2
TURN_LEFT = 3
TURN_BACK = 4
class QueryEnv:
    def __init__(self,grid:Grid,position,orientation):
        '''
        grid->the envrionment the robot will be navigating in
        position -> true position of the robot relative to the enviroment origin
        orientatrion->true orientation of the robot relative to north of the grid
        
        '''
        self.env = grid
        self.i = position[0]
        self.j = position[1] 
        self.orientation=orientation

    def get_dimensions(self):
        return self.env.get_height()
    def _update_delta(self,move_direction):
        is_wall = self.env.get_bit(self.i,self.j,move_direction)
        if(not is_wall):
            di,dj = DIRECTION_MAP[move_direction] 
            self.i,self.j = self.i+di,self.j+dj
        raise Exception("Robot has requested an illegal move")

    def update(self,move):
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
        front = self.env.get_bit(self.i,self.j,self.orientation)
        right = self.env.get_bit(self.i,self.j,RIGHT_MAP[self.orientation])
        left = self.env.get_bit(self.i,self.j,LEFT_MAP[self.orientation])
        return left,front,right
    def query_dimensions(self):
        '''
        return the dimensions of the maze the robot is currently in
        '''
        return self.env.get_height()
class Robot:
    def __init__(self,query_environment:QueryEnv):
        self.j = 0 
        self.i = self.query_environment.get_dimensions() -1
        self.orientation =EAST
        self.query_environment = query_environment
        self.second_major_direction = None 
        self.grid = self.make_internal_map()
        self.centers = None

    def make_internal_map(self):
        dim = self.query_environment.get_dimensions()
        grid = [[0]*dim for _ in range(dim*2-1)]
        return Grid(grid)

    def _move_internal(self,move):
        if(move == FORWARD):
            di,dj = DIRECTION_MAP[self.orientation]
            self.i += di
            self.j += dj
        if(move == BACKWARD):
            di,dj = DIRECTION_MAP[OPPOSITE_MAP[self.orientation]]
            self.i += di
            self.j += dj
        if(move == TURN_BACK):
            self.orientation = OPPOSITE_MAP[self.orientation]
        if(move == TURN_LEFT):
            self.orientation = LEFT_MAP[self.orientation] 
        if(move == TURN_RIGHT):
            self.orientation = RIGHT_MAP[self.orientation]

    def set_center(self):
        assert(self.second_major_direction is not None)
        dj = 1
        di = DIRECTION_MAP[self.second_major_direction][0] 
        assert(di !=0)
        center = (
            self.i+di*(self.query_environment.get_dimensions()//2-1),
            self.j+dj*(self.query_environment.get_dimensions()//2-1),
        )
        self.centers = (
            center,
            (center[0],center[1]+dj),
            (center[0]+di,center[1]),
            (center[0]+di,center[1]+dj)
        )
    def orient(self):
        while(not any((self.query_environment.query()))):
            self.query_environment.update(TURN_RIGHT)
        left,front,right = self.query_environment.query()
        if(front):
            pass
        elif(left):
            self.query_environment.update(TURN_LEFT)
        elif(right):
            self.query_environment.update(TURN_RIGHT)
        
        left,front,right = self.query_environment.query()
        if(left):
            self.second_major_direction = LEFT_MAP[self.orientation]
        if(right):
            self.second_major_direction = RIGHT_MAP[self.orientation]
        if(self.second_major_direction is not None):
            self.set_center()
    def find_center(self):

        if self.centers is not None and (self.i,self.j) in self.centers:
            return True 
          
        
        