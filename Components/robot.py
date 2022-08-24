from Components.grid import Grid,NORTH,SOUTH,EAST,WEST
from typing import Dict,Tuple



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

DIRECTION_MAP:Dict[int,Tuple[int,int]] = {
    SOUTH:(1,0),
    NORTH:(-1,0),
    EAST:(0,1),
    WEST:(0,-1),
}

REVERSE_DIRECTION_MAP = {val:key for key,val in DIRECTION_MAP.items()}


FORWARD = 0
BACKWARD= 1
TURN_RIGHT = 2
TURN_LEFT = 3
TURN_BACK = 4

FRONT = 0
LEFT = 1
RIGHT = 2
BACK = 3
class PanicException(Exception):
    pass

def panic(s):
    raise PanicException(s)

class Queue:
    def __init__(self,max_size):
        self.max_size = max_size
        self.array = [0]*(max_size+1)
        self.begin = 0
        self.end = 0
    def size(self):
        return (self.end - self.begin + len(self.array))%len(self.array)
    def empty(self):
        return self.size() == 0
    def full(self):
        return self.size() == self.max_size
    def push(self,x):
        if(self.full()):
            panic("Queue is full but trying to push")
        self.array[self.end] = x 
        self.end = (self.end+1)%len(self.array)
    def pop(self):
        if(self.empty()):
            panic("The Queue is empty but trying to pop")
        ret = self.array[self.begin]
        self.begin = (self.begin+1)%len(self.array)
        return ret
    def peek(self):
        if(self.empty()):
            panic("The Queue is empty but trying to peek")
        return self.array[self.begin]
    def clear(self):
        self.begin = 0
        self.end = 0
class Stack:
    def __init__(self,max_size):
        self.array = [0]*max_size
        self.end = 0 #points to the next element from the last element 
    def size(self):
        return self.end
    def empty(self):
        return self.size() == 0
    def full(self):
        return self.size() == len(self.array)
    def push(self,x):
        if(self.full()):
            panic("Pushing to an already full stack")
        self.array[self.end] = x
        self.end += 1
    def pop(self):
        if(self.empty()):
            panic("Popping from an already empty stack")
        self.end -=1
        return self.array[self.end]
    def peek(self):
        if(self.empty()):
            panic("Peeking from an already empty stack")
        return self.array[self.end-1]
    def clear(self):
        self.end = 0


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
            return 
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

class Bfs_Node:
    def __init__(self,node,distance):
        self.node = node
        self.distance = distance
class Robot:
    def __init__(self,query_environment:QueryEnv):
        self.query_environment = query_environment
        self.j = 1 
        self.i = self.query_environment.get_dimensions() 
        self.orientation =EAST
        self.second_major_direction = None 
        self.grid = self.make_internal_map()
        self.centers = None
        self.bfs_count = 0
        self.bfs_queue = Queue(self.query_environment.get_dimensions()*2)
        self.dfs_stack = Stack(self.query_environment.get_dimensions()**2)
        
    def make_internal_map(self):
        dim = self.query_environment.get_dimensions()
        grid = [[0]*(dim+2) for _ in range(dim*2+1)]
        return Grid(grid)

    def relative_ro_absolute(self,rel_dir):
        if(rel_dir == FRONT):
            return self.orientation
        if(rel_dir == BACK):
            return OPPOSITE_MAP[self.orientation]
        if(rel_dir == LEFT):
            return LEFT_MAP[self.orientation]
        if(rel_dir == RIGHT):
            return RIGHT_MAP[self.orientation]
        assert(False)

    def make_wall_rel_direction(self,rel_direction): 
        orientation = self.relative_ro_absolute(rel_direction)
        
        a = (self.i,self.j)
        di,dj = DIRECTION_MAP[orientation]
        b = (self.i+di,self.j+dj)
        if(not self.grid.set_wall(a,b)):

            panic("make wall in out of bound places")
    
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

    def move(self,move):
        self._move_internal(move)
        self.query_environment.update(move)

    def set_center(self):
        assert(self.second_major_direction is not None)
        dj = 1
        di = DIRECTION_MAP[self.second_major_direction][0] 
        assert(di !=0)
        start_i = self.query_environment.get_dimensions()
        start_j = 1
        center = (
            start_i+di*(self.query_environment.get_dimensions()//2-1),
            start_j+dj*(self.query_environment.get_dimensions()//2-1),
        )
        self.centers = (
            center,
            (center[0],center[1]+dj),
            (center[0]+di,center[1]),
            (center[0]+di,center[1]+dj)
        )

    def orient(self):
        while(not any((not i for i in self.query_environment.query()))):
            self.query_environment.update(TURN_RIGHT)
        left,front,right = self.query_environment.query()
        if(not front):
            pass
        elif(not left):
            self.query_environment.update(TURN_LEFT)
        elif(not right):
            self.query_environment.update(TURN_RIGHT)
        self.make_wall_rel_direction(BACK)
         
        left,front,right = self.query_environment.query()
        if(not left):
            self.second_major_direction = LEFT_MAP[self.orientation]
        else:
            self.make_wall_rel_direction(LEFT)
        if(not right):
            self.second_major_direction = RIGHT_MAP[self.orientation]
        else:
            self.make_wall_rel_direction(RIGHT)
        if(self.second_major_direction is not None):
            self.set_center()
        
    def bfs(self,start_node):
        '''
        returns whether the center can be reached plausibly given the current information without going over currently known paths
        if the center is unreachable in such a manner then -1 is returned
        otherwise the minimum possible distance to the center given the current information is returned
        incomplete as of yet
        '''
        assert(False)
        self.bfs_queue.clear()        
        self.bfs_count += 1
        self.bfs_queue.push(Bfs_Node(start_node,0))
        while (not self.bfs_queue.empty()):
            current_node:Bfs_Node = self.bfs_queue.pop()
            node,distance = current_node.node,current_node.distance
            

        else: #center was never reached
            return -1 #meaning the center is unreachable 

    def go_to(self,rel_direction):
        if(rel_direction == BACK):
            self.move(TURN_BACK)
            self.move(FORWARD)
        if(rel_direction == RIGHT):
            self.move(TURN_RIGHT)
            self.move(FORWARD)
        if(rel_direction == LEFT):
            self.move(TURN_LEFT)
            self.move(FORWARD)
        if(rel_direction == FRONT):
            self.move(FORWARD)
         
    def position(self):
        return self.i,self.j
    
    def abs_to_rel(self,abs_dir):
        if(abs_dir == self.orientation):
            return FRONT
        if(abs_dir == OPPOSITE_MAP[self.orientation]):
            return BACK
        if(abs_dir == LEFT_MAP[self.orientation]):
            return LEFT
        if(abs_dir == RIGHT_MAP[self.orientation]):
            return RIGHT
        
        panic("absolute direction cannot be resolved to relative direction")
    def go_to_pos(self,i,j):

        dif = ((i - self.i),(j - self.j))
        if(dif not in REVERSE_DIRECTION_MAP):
            panic("The cell that needs to be gone to is not adjacent to the current cell")
        abs_direction =  REVERSE_DIRECTION_MAP[dif]  
        rel_direction = self.abs_to_rel(abs_direction)
        self.go_to(rel_direction)

    def get_cell(self,rel_direction):
        abs_dir = self.relative_ro_absolute(rel_direction)
        di,dj = DIRECTION_MAP[abs_dir]
        return (self.i+di,self.j+dj)

        

    def search(self):
        self.grid.set_visited(*self.position()) 
        left,front,right = self.query_environment.query()
        for  dire,has_wall in zip([LEFT,FRONT,RIGHT],(left,front,right)):
            if(has_wall):
                self.make_wall_rel_direction(dire)
            else:
                if(dire != FRONT and self.second_major_direction is None):
                    print("Setting centers",self.second_major_direction,self.centers)
                    self.second_major_direction = self.relative_ro_absolute(dire)
                    self.set_center()
                    print(self.centers)

        
        if self.centers is not None and (self.i,self.j) in self.centers:
            return True 
        
        
        for  dire,has_wall in zip([LEFT,FRONT,RIGHT],(left,front,right)):
            if(not has_wall and not self.grid.visited(*self.get_cell(dire))):
                self.dfs_stack.push(self.position())
                self.go_to(dire)
                return False
        
        if(self.dfs_stack.empty()):
            panic("need to go back to previous node but the stack is empty")
        self.go_to_pos(*self.dfs_stack.pop())
        return False
        
          
        
        