#ifndef GRID_HEADER
#define GRID_HEADER

#include <stdint.h>
#include "Structures.h"
#include "Utility.h"

struct WallStates{
    bool walls[4] = {0};
};


const uint32_t VISITED = 4;
const uint32_t ADDITIONAL_DATA = 5;

template<uint32_t R,uint32_t C>
class Grid{
private:
    uint64_t array[R][C] = {0};

    void set_wall_helper(Grid_Pos a, Grid_Pos b){
        auto dif = Relative_Grid_Pos{
            b.i -a.i,
            b.j -a.j
        };
        auto wall_direction = relative_grid_pos_to_abs(dif);
        array[a.i][a.j] |= (1 << static_cast<int>(wall_direction));

    }
public:
    uint32_t get_height(){
        return R;
    }
    uint32_t get_width(){
        return C;
    }
    WallStates get_walls(uint32_t i,uint32_t j){
        uint64_t chara = array[i][j];
        WallStates w;
        w.walls[static_cast<int>(ABS_DIRECTION::NORTH)] = bool(chara & (1UL <<static_cast<int>(ABS_DIRECTION::NORTH)));
        w.walls[static_cast<int>(ABS_DIRECTION::EAST)] = bool(chara & (1UL <<static_cast<int>(ABS_DIRECTION::EAST)));
        w.walls[static_cast<int>(ABS_DIRECTION::SOUTH)] = bool(chara & (1UL <<static_cast<int>(ABS_DIRECTION::SOUTH)));
        w.walls[static_cast<int>(ABS_DIRECTION::WEST)] = bool(chara & (1UL <<static_cast<int>(ABS_DIRECTION::WEST)));
        return w;
    }
    bool get_bit(uint32_t i, uint32_t j,uint32_t data_bit){
        return array[i][j] & (1UL << data_bit);
    }
    bool visited(uint32_t i,uint32_t j){
        return array[i][j] & (1UL << VISITED);
    }


    void set_wall(Grid_Pos a, Grid_Pos b){
        if (!(0<=a.i && a.i <R && 0<=a.j && a.j<C)) panic(PANICCODE::GRID_OUT_OF_BOUNDS);
        if (!(0<=b.i && b.i <R && 0<=b.j && b.j<C)) panic(PANICCODE::GRID_OUT_OF_BOUNDS);
        set_wall_helper(a,b);
        set_wall_helper(b,a);
    }

    void set_visited(uint32_t i, uint32_t j){
        array[i][j] |= (1UL << VISITED);
    }
    void set_additional_data(uint32_t i, uint32_t j,uint64_t data){
        array[i][j] &= ((1UL << ADDITIONAL_DATA)-1); //resest the existing data to zero
        array[i][j] |= data << ADDITIONAL_DATA ;
    }
    uint64_t get_additional_data(uint32_t i,uint32_t j){
        return array[i][j] >> ADDITIONAL_DATA;
    }

    void output_grid(){
    }

};




#endif