import os,sys

import unittest

path = os.path.join(os.path.dirname(sys.path[0]))
sys.path.append(path)

from Components.grid import Grid,VISITED,NORTH,SOUTH,EAST,WEST
import logging


class Test_Grid(unittest.TestCase):
    def testint_set_data_and_get_data(self):
        fillval = 0b11111
        gg = [[fillval]*5 for _ in range(5)]
        grid = Grid(gg)
        grid.set_additional_data(0,0,125)
        self.assertEqual(grid.get_additional_data(0,0),125)
        grid.set_additional_data(0,0,0)
        self.assertEqual(grid.grid[0][0],fillval)
        

if __name__ == "__main__":
    unittest.main(verbosity=2)