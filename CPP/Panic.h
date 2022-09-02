#ifndef PANIC_GAURD
#define PANIC_GAURD
#include <iostream>
enum class PANICCODE{
    PANIC,
    STACK_FULL,
    STACK_EMPTY,
    QUEUE_FULL,
    QUEUE_EMPTY,
    INVALID_GRID_DIFF_OBJECT,
    GRID_OUT_OF_BOUNDS,
    INVALID_MAJOR_DIRECTION,
    CENTER_INTIALIZATION_FAILED,
    NEED_TO_GO_BACK_BUT_STACK_EMPTY,
};


void panic(PANICCODE panic){
    std::cout << static_cast<int>(panic) << std::endl;
    throw (panic);
}
#endif