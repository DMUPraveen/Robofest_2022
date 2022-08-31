#ifndef GRID_HEADER
#define GRID_HEADER

#include <stdint.h>
#include "Structures.h"
#include "Utility.h"

struct WallStates{
    bool walls = {0};
};


const uint8_t VISITED = 4;
const uint8_t ADDITIONAL_DATA = 5;

template<uint8_t R,uint8_t C>
class Grid{
private:
    uint64_t array[R][C] = {0};

    void set_wall_helper(Grid_Pos a, Grid_Pos b){
        auto dif = Relative_Grid_Pos{
            a.i -b.i,
            a.j -b.j
        }
        auto wall_direction = relative_grid_pos_to_abs(dif);
        array[a.i][a.j] |= (1 << wall_direction);

    }
public:
    uint8_t get_height(){
        return R;
    }
    uint8_t get_width(){
        return C;
    }
    WallStates get_walls(uint8_t i,uint8_t j){
        uint64_t chara = array[i][j];
        WallStates w;
        w[ABS_DIRECTION::NORTH] = bool(chara & (1UL << ABS_DIRECTION::NORTH));
        w[ABS_DIRECTION::EAST] = bool(chara & (1UL << ABS_DIRECTION::NORTH));
        w[ABS_DIRECTION::SOUTH] = bool(chara & (1UL << ABS_DIRECTION::NORTH));
        w[ABS_DIRECTION::WEST] = bool(chara & (1UL << ABS_DIRECTION::NORTH));
        return w;
    }
    bool get_bit(uint8_t i, uint8_t j,uint8_t data_bit){
        return array[i][j] & (1UL << data_bit);
    }
    bool visited(uint8_t i,uint8_t j){
        return self.grid[i][j] & (1UL << VISITED);
    }


    void set_wall(Grid_Pos a, Grid_Pos b){
        if !(0<=a.i && a.i <R && 0<=a.j && a.j<C) panic(PANICCODE::GRID_OUT_OF_BOUNDS);
        if !(0<=b.i && b.i <R && 0<=b.j && b.j<C) panic(PANICCODE::GRID_OUT_OF_BOUNDS);
        set_wall_helper(a,b);
        set_wall_helper(b,a);
    }

    void set_visited(uint8_t i, unint8_t j){
        array[i][j] |= (1UL << VISITED);
    }
    void set_additional_data(uint8_t i, unint8_t j,uint64_t data){
        array[i][j] &= ((1UL << ADDITIONAL_DATA)-1); //resest the existing data to zero
        array[i][j] |= data << ADDITIONAL_DATA ;
    }
    uint64_t get_additional_data(uint8_t i,uint8_t j){
        return array[i][j] >> ADDITIONAL_DATA;
    }

};




#endif