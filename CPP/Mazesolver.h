#ifndef MAZESOLVER_HEADER
#define MAZESOLVER_HEADER
#include "Structures.h"
#include "Utility.h" 
#include "Grid.h"

#define SAFETY_OFFSET 10
struct RelWallState{
    bool left = false;
    bool front = false;
    bool right = false;
};
class MazeSolver_Interface{
public:
    virtual uint8_t get_dimensions() = 0;
    virtual void do_move(BASIC_COMMANDS c) = 0;
    virtual RelWallState query_wall_states() = 0;
};

struct Bfs_Node{
    Grid_Pos node;
    int64_t distance;
};


template<uint8_t DIM>
class MazeSolver{
private:
    MazeSolver_Interface* interface = nullptr;
    Grid_Pos pos = {0,0};
    ABS_DIRECTION orientation;
    ABS_DIRECTION major_direction;
    Grid<DIM*2,DIM*2+1> internal_grid;
    bool centers_intializes = false;
    Grid_Pos centers[4];
    int64_t bfs_count = 0;
    auto bfs_queu = Queue<DIM*DIM+SAFETY_OFFSET,Bfs_Node>();
    auto dfs_stack = Stack<DIM*DIM+SAFETY_OFFSET,Bfs_Node>();


    void make_internal_map();
    ABS_DIRECTION abs_dir_from_rel(REL_DIRECTION);
    REL_DIRECTION rel_from_abs(ABS_DIRECTION);
    void make_wall_in_relative_direction(REL_DIRECTION);
    void move_internal(BASIC_COMMANDS);
    void move_interface(BASIC_COMMANDS);
    bool set_center();
    void go_to(REL_DIRECTION);
    void go_to_pos(Grid_Pos);
    void get_relaitve_cell(REL_DIRECTION);
    bool is_bfs_visited(Grid_Pos);
    void set_bfs_visited(Grid_Pos);
    int64_t bfs(Grid_Pos);
    REL_DIRECTION get_best_path(RelWallState)
    
public:
    MazeSolver(){
        pos.i = 1;
        pos.j = DIM;
        orientation = ABS_DIRECTION::EAST;
        make_internal_map(); // drawing the pelimenary walls
    }

    bool orient();
    




};


#endif