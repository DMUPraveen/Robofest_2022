# Maze Visualizer

This program can be used for editing and visualizing mazes and for outputing them elsewhere. 
The mazes are represented in a custom format described as follow

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
