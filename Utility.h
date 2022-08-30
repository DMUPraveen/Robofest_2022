#include "Structures.h"


ABS_DIRECTION opoosite_direction(ABS_DIRECTION dir){

    return ABS_DIRECTION(
        (static_cast<uint8_t>(dir) +2) %4 
    );
}

ABS_DIRECTION left_direction(ABS_DIRECTION dir){
    return ABS_DIRECTION(
        (static_cast<uint8_t>(dir) +3)%4
    );
}