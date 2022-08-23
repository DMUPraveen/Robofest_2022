
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
NORTH  = 3
SOUTH = 2
EAST = 1
WEST = 0
VISITED = 4

class Grid:
    def __init__(self,grid):
        self.grid = grid
    def get_height(self):
        return len(self.grid)
    def get_wdith(self):
        return len(self.grid[0])
    def get_walls(self,i,j):
        '''
            returns the has wall state of the four cardinal directions in the following order 
            [northwall,southwall,eastwall,westwall]
        '''
        chara = self.grid[i][j]
        northwall = bool(chara& (1<<NORTH))
        southwall = bool(chara& (1<<SOUTH))
        eastwall = bool(chara& (1<<EAST))
        westwall = bool(chara& (1<<WEST))
        return [northwall,southwall,eastwall,westwall]
    def get_bit(self,i,j,data_bit):
        '''
        returns whether the bit ad data_bit position is set
        '''
        return self.grid[i][j] & (1 << data_bit)
    def visited(self,i,j):
        return self.grid[i][j] & (1 << VISITED) 
    
    
    def make_wall_helper(self,a,b):
        '''
        sets the wal
        '''
        WALL_MAP = {
            (-1,0):SOUTH,
            (1,0):NORTH,
            (0,-1):EAST,
            (0,1):WEST,
        }

        key = tuple(a[i] -b[i] for i in range(2))
        if key in WALL_MAP:
            self.grid[a[0]][a[1]] ^= 1 << WALL_MAP[key]

    def make_wall(self,a,b):
        if not(0<=a[0]<len(self.grid) and 0<=a[1]<len(self.grid[0])):
            return 
        if not(0<=b[0]<len(self.grid) and 0<=b[1]<len(self.grid[0])):
            return

        self.make_wall_helper(a,b)
        self.make_wall_helper(b,a)
