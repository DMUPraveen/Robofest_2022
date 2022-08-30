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