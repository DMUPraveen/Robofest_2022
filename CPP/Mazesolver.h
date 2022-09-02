#ifndef MAZESOLVER_HEADER
#define MAZESOLVER_HEADER
#include "Grid.h"

#define SAFETY_OFFSET 500 
struct RelWallState
{
    bool left = false;
    bool front = false;
    bool right = false;
};
class MazeSolver_Interface
{
public:
    virtual uint32_t get_dimensions() = 0;
    virtual void do_move(BASIC_COMMANDS c) = 0;
    virtual RelWallState query_wall_states() = 0;
};

struct Bfs_Node
{
    Grid_Pos node;
    int64_t distance=0;
    Bfs_Node(){};
    Bfs_Node(Grid_Pos node,int64_t distance)
        :node(node),distance(distance)
    {}
};

template <uint32_t DIM>
class MazeSolver
{
private:
    MazeSolver_Interface *interface = nullptr;
    Grid_Pos pos = {0, 0};
    ABS_DIRECTION orientation;
    ABS_DIRECTION major_direction;
    Grid<DIM * 2+1, DIM +2> internal_grid;
    bool centers_intializes = false;
    bool major_direction_intialized = false;
    Grid_Pos centers[4];
    int64_t bfs_count = 0;
    Queue<DIM * DIM + SAFETY_OFFSET, Bfs_Node> bfs_queue = Queue<DIM * DIM + SAFETY_OFFSET, Bfs_Node>();
    Stack<DIM * DIM + SAFETY_OFFSET, Grid_Pos> dfs_stack =  Stack<DIM * DIM + SAFETY_OFFSET, Grid_Pos>();

    void make_internal_map();
    ABS_DIRECTION abs_dir_from_rel(REL_DIRECTION);
    REL_DIRECTION rel_from_abs(ABS_DIRECTION);
    void make_wall_in_relative_direction(REL_DIRECTION);
    void move_internal(BASIC_COMMANDS);
    void move(BASIC_COMMANDS);
    bool set_center();
    void go_to(REL_DIRECTION);
    void go_to_pos(Grid_Pos);
    Grid_Pos get_relaitve_cell(REL_DIRECTION);
    bool is_bfs_visited(Grid_Pos);
    void set_bfs_visited(Grid_Pos);
    int64_t bfs(Grid_Pos);
    REL_DIRECTION get_best_path(RelWallState);
    void initialize_major_direction(ABS_DIRECTION);
    bool is_a_center(Grid_Pos);

public:
    MazeSolver(MazeSolver_Interface*);
 

    bool orient();

    bool search();

    Grid_Pos get_pos(){
        return pos;
    }
    void show_internal(){
        internal_grid.output_grid();
    }
};




//implementation

template <uint32_t DIM>
void MazeSolver<DIM>::make_internal_map()
{
    for (int j = 1; j < (internal_grid.get_width() - 1); j++)
    {
        internal_grid.set_wall(
            {0, j}, {1, j});
        internal_grid.set_wall(
            {internal_grid.get_height() - 1, j},
            {internal_grid.get_height() - 2, j});
    }
    for (int i = 1; i < (internal_grid.get_height() - 1); i++)
    {
        internal_grid.set_wall(
                         {i, 0}, {i, 1});
            internal_grid.set_wall(
                {i, internal_grid.get_width() - 1},
                {i, internal_grid.get_width() - 2});
    }
}

template <uint32_t DIM>
MazeSolver<DIM>::MazeSolver(MazeSolver_Interface *interface)
    : interface(interface)
{
    pos.i = DIM;
    pos.j = 1;

    orientation = ABS_DIRECTION::EAST;
    major_direction_intialized = false;
    centers_intializes = false;
    bfs_count = 0;
    make_internal_map();
}
template <uint32_t DIM>
ABS_DIRECTION MazeSolver<DIM>::abs_dir_from_rel(REL_DIRECTION rel)
{
    return get_rel_direction(orientation, rel);
}

template <uint32_t DIM>
REL_DIRECTION MazeSolver<DIM>::rel_from_abs(ABS_DIRECTION abs_dir)
{
    return get_rel_dir_from_two_abs(orientation, abs_dir);
}

template <uint32_t DIM>
void MazeSolver<DIM>::make_wall_in_relative_direction(REL_DIRECTION rel)
{
    Relative_Grid_Pos other_cell_delta = abs_dir_to_relative_pos(abs_dir_from_rel(rel));

    internal_grid.set_wall(
        pos,
        {pos.i + other_cell_delta.di, pos.j + other_cell_delta.dj});
}

template <uint32_t DIM>
void MazeSolver<DIM>::move_internal(BASIC_COMMANDS com)
{
    Relative_Grid_Pos delta = {0,0};
    switch (com)
    {
    case BASIC_COMMANDS::FORWARD:
        delta = abs_dir_to_relative_pos(orientation);
        pos = {pos.i + delta.di, pos.j + delta.dj};
        break;
    case BASIC_COMMANDS::BACKWARD:
        delta = abs_dir_to_relative_pos(opposite_direction(orientation));
        pos = {pos.i + delta.di, pos.j + delta.dj};
        break;
    case BASIC_COMMANDS::TURN_BACK:
        orientation = opposite_direction(orientation);
        break;
    case BASIC_COMMANDS::TURN_LEFT:
        orientation = left_direction(orientation);
        break;
    case BASIC_COMMANDS::TURN_RIGHT:
        orientation = right_direction(orientation);
        break;
    }
}
template <uint32_t DIM>
void MazeSolver<DIM>::move(BASIC_COMMANDS com)
{
    move_internal(com);
    interface->do_move(com);
}

template <uint32_t DIM>
bool MazeSolver<DIM>::set_center()
{
    if (!major_direction_intialized)
        return false;
    if (centers_intializes)
        return true;
    centers_intializes = true;
    Relative_Grid_Pos delta = {
        abs_dir_to_relative_pos(major_direction).di,
        1};
    if (delta.di == 0)
    {
        panic(PANICCODE::INVALID_MAJOR_DIRECTION);
    }
    int64_t start_i = DIM;
    int64_t start_j = 1;
    Grid_Pos base_center = {
        start_i + delta.di * (DIM / 2 - 1),
        start_j + delta.dj * (DIM / 2 - 1)};
    centers[0] = base_center;
    centers[1] = Grid_Pos{base_center.i, base_center.j + delta.dj};
    centers[2] = Grid_Pos{base_center.i + delta.di, base_center.j};
    centers[3] = Grid_Pos{base_center.i + delta.di, base_center.j + delta.dj};
    ABS_DIRECTION wall_dir = opposite_direction(major_direction);
    for (int k = 1; k < internal_grid.get_width() - 1; k++)
    {
        int64_t next_i = start_i + abs_dir_to_relative_pos(wall_dir).di;
        internal_grid.set_wall({start_i, k}, {next_i, k});
    }

    return true;
}

template <uint32_t DIM>
void MazeSolver<DIM>::go_to(REL_DIRECTION rel_dir)
{
    switch (rel_dir)
    {
    case REL_DIRECTION::BACK:
        move(BASIC_COMMANDS::TURN_BACK);
        move(BASIC_COMMANDS::FORWARD);
        break;
    case REL_DIRECTION::RIGHT:
        move(BASIC_COMMANDS::TURN_RIGHT);
        move(BASIC_COMMANDS::FORWARD);
        break;
    case REL_DIRECTION::LEFT:
        move(BASIC_COMMANDS::TURN_LEFT);
        move(BASIC_COMMANDS::FORWARD);
        break;
    case REL_DIRECTION::FRONT:
        move(BASIC_COMMANDS::FORWARD);
        break;
    }
}

template <uint32_t DIM>
void MazeSolver<DIM>::go_to_pos(Grid_Pos destination)
{
    Relative_Grid_Pos delta = {
        destination.i - pos.i,
        destination.j - pos.j};
    REL_DIRECTION relative_direction_to_go = rel_from_abs(relative_grid_pos_to_abs(delta));
    go_to(relative_direction_to_go);
}

template <uint32_t DIM>
Grid_Pos MazeSolver<DIM>::get_relaitve_cell(REL_DIRECTION rel)
{
    ABS_DIRECTION abs_dir = abs_dir_from_rel(rel);
    Relative_Grid_Pos delta = abs_dir_to_relative_pos(abs_dir);
    return Grid_Pos{pos.i + delta.di, pos.j + delta.dj};
}

template <uint32_t DIM>
bool MazeSolver<DIM>::is_bfs_visited(Grid_Pos position)
{
    return internal_grid.get_additional_data(position.i, position.j) == bfs_count;
}

template <uint32_t DIM>
void MazeSolver<DIM>::set_bfs_visited(Grid_Pos position)
{
    internal_grid.set_additional_data(position.i,position.j,bfs_count);
}


template <uint32_t DIM>
void MazeSolver<DIM>::initialize_major_direction(ABS_DIRECTION major_dir){
    this->major_direction = major_dir;
    major_direction_intialized = true;
}
template <uint32_t DIM>
bool MazeSolver<DIM>::orient()
{
    RelWallState wall_states = interface->query_wall_states();
    //walls on all sides
    if (wall_states.front  && wall_states.left && wall_states.right){
        interface->do_move(BASIC_COMMANDS::TURN_RIGHT);
        return false;
    }
    //wall on front but there is an opening to the left or the right
    if(wall_states.front){
        if(!wall_states.left){
            interface->do_move(BASIC_COMMANDS::TURN_LEFT);
            return false;
        }
        if(!wall_states.right){
            interface->do_move(BASIC_COMMANDS::TURN_RIGHT);
            return false;
        }

    }

    //there is no wall in the front
    if(!wall_states.left){
        initialize_major_direction(abs_dir_from_rel(REL_DIRECTION::LEFT));
    }
    else{
        make_wall_in_relative_direction(REL_DIRECTION::LEFT);
    }

    if(!wall_states.right){
        initialize_major_direction(abs_dir_from_rel(REL_DIRECTION::RIGHT));
    }
    else{
        make_wall_in_relative_direction(REL_DIRECTION::RIGHT);
    }

    if(major_direction_intialized){
        set_center();
    }
    return true;

}

template<uint32_t DIM>
bool MazeSolver<DIM>::is_a_center(Grid_Pos position){
    for(int i=0;i<4;i++){
        if(position.i == centers[i].i && position.j == centers[i].j){
            return true;
        }
    }

    return false;
}

template<uint32_t DIM>
int64_t MazeSolver<DIM>::bfs(Grid_Pos start){

    if(internal_grid.visited(start.i,start.j)){
        return -1;
    }
    bfs_count +=1;
    bfs_queue.clear();
    set_bfs_visited(start);
    bfs_queue.push(Bfs_Node(start,0));
    while (!bfs_queue.empty()){
        Bfs_Node current = bfs_queue.pop();
        if(is_a_center(current.node)){
            return current.distance;
        }
        WallStates wall_states = internal_grid.get_walls(current.node.i,current.node.j);
        for(int i=0;i<4;i++){
            ABS_DIRECTION dire = ABS_DIRECTION(i);
            bool wall = wall_states.walls[i];
            if(!wall){
                Relative_Grid_Pos delta = abs_dir_to_relative_pos(dire);
                Grid_Pos next_cell = {
                    current.node.i+delta.di,
                    current.node.j+delta.dj,
                };
                if(!internal_grid.visited(next_cell.i,next_cell.j) && !is_bfs_visited(next_cell)){
                    set_bfs_visited(next_cell);
                    bfs_queue.push(Bfs_Node(next_cell,current.distance+1));
                }
            }
        }

    }
    return -1;
    
}

template<uint32_t DIM>
REL_DIRECTION MazeSolver<DIM>::get_best_path(RelWallState rel_wall_states){
    REL_DIRECTION best = REL_DIRECTION::BACK;
    int64_t best_distance = DIM*DIM+SAFETY_OFFSET;

    REL_DIRECTION dirs[3] = {REL_DIRECTION::LEFT,REL_DIRECTION::FRONT,REL_DIRECTION::RIGHT};
    bool states[3] = {rel_wall_states.left,rel_wall_states.front,rel_wall_states.right};
    if(!centers_intializes) {
        for(int i=0;i<3;i++){
            bool wall = states[i];
            REL_DIRECTION dir = dirs[i];
            Grid_Pos position = get_relaitve_cell(dir);
            if(!wall and !internal_grid.visited(position.i,position.j)){
                best = dir;
            }
        }
        return best;

    }
    for(int i=0;i<3;i++){
        bool wall = states[i];
        REL_DIRECTION dir = dirs[i];
        Grid_Pos position = get_relaitve_cell(dir);
        if(!wall and !internal_grid.visited(position.i,position.j)){
            // Grid_Pos cell = get_relaitve_cell(position);
            int64_t distance = bfs(position);
            if(!(distance == -1) && distance < best_distance){
                best_distance = distance;
                best = dir;
            }



        }
    }
    return best;


}


template<uint32_t DIM>
bool MazeSolver<DIM>::search(){
    internal_grid.set_visited(pos.i,pos.j);
    RelWallState  rel_wall_states= interface->query_wall_states();
    REL_DIRECTION dirs[3] = {REL_DIRECTION::LEFT,REL_DIRECTION::FRONT,REL_DIRECTION::RIGHT};
    bool states[3] = {rel_wall_states.left,rel_wall_states.front,rel_wall_states.right};
    for(int i=0;i<3;i++){
        bool has_wall = states[i];
        REL_DIRECTION dire = dirs[i];
        if(has_wall){
            make_wall_in_relative_direction(dire);
        }
        else{
            if(dire!= REL_DIRECTION::FRONT && !major_direction_intialized){
                //setting the centers
                initialize_major_direction(abs_dir_from_rel(dire));
                if(!set_center()){
                    panic(PANICCODE::CENTER_INTIALIZATION_FAILED);
                }
            }
        }
        

    }
    if(centers_intializes && is_a_center(this->pos)){
        return true;
    }

    REL_DIRECTION best_direction = get_best_path(rel_wall_states);
    if(best_direction !=REL_DIRECTION::BACK){
        dfs_stack.push(pos);
        go_to(best_direction);
        return false;
    }

    if(dfs_stack.empty()){
        panic(PANICCODE::NEED_TO_GO_BACK_BUT_STACK_EMPTY);
    }
    go_to_pos(dfs_stack.pop());
    return false;

    
    
}
#endif