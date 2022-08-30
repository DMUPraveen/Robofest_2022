#ifndef UTILITY_HEADER
#define UTILITY_HEADER
#include "Structures.h"


ABS_DIRECTION opposite_direction(ABS_DIRECTION dir){

    return ABS_DIRECTION(
        (static_cast<uint8_t>(dir) +2) %4 
    );
}

ABS_DIRECTION left_direction(ABS_DIRECTION dir){
    return ABS_DIRECTION(
        (static_cast<uint8_t>(dir) +3)%4
    );
}

ABS_DIRECTION right_direction(ABS_DIRECTION dir){
    return ABS_DIRECTION(
        (static_cast<uint8_t>(dir) +1)%4
    );
}

ABS_DIRECTION get_rel_direction(ABS_DIRECTION dir, REL_DIRECTION reldir){
    switch (reldir)
    {
    case REL_DIRECTION::FRONT:
        return dir;
        break;
    case REL_DIRECTION::BACK:
        return opposite_direction(dir);
        break;
    case REL_DIRECTION::LEFT:
        return left_direction(dir);
        break;
    case REL_DIRECTION::RIGHT:
        return right_direction(dir);
        break;
    
    default:
        panic(PANICCODE::PANIC);
        return dir;
        break;
    }
}

Relative_Grid_Pos abs_dir_to_relative_pos(ABS_DIRECTION dir){
    switch(dir){
        case ABS_DIRECTION::NORTH:
            return Relative_Grid_Pos{-1,0};
            break;
        case ABS_DIRECTION::EAST:
            return Relative_Grid_Pos{0,1};
            break;
        case ABS_DIRECTION::SOUTH:
            return Relative_Grid_Pos{1,0};
            break;
        case ABS_DIRECTION::WEST:
            return Relative_Grid_Pos{0,-1};
            break;
    }
    panic(PANICCODE::PANIC);
    return Relative_Grid_Pos{0,0};
}

ABS_DIRECTION relative_grid_pos_to_abs(Relative_Grid_Pos rgp){
    if(rgp.di == 0){
        if(rgp.dj == 1){
            return ABS_DIRECTION::EAST;
        }
        if(rgp.dj == -1){
            return ABS_DIRECTION::WEST;
        }
    }
    if(rgp.dj == 0){
        if(rgp.di == 1){
            return ABS_DIRECTION::SOUTH;
        }
        if(rgp.di == -1){
            return ABS_DIRECTION::NORTH;
        }
    }
    panic(PANICCODE::INVALID_GRID_DIFF_OBJECT);
    return ABS_DIRECTION::NORTH;
}

#endif