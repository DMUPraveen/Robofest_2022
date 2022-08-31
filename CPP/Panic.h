#ifndef PANIC_GAURD
#define PANIC_GAURD
enum class PANICCODE{
    PANIC,
    STACK_FULL,
    STACK_EMPTY,
    QUEUE_FULL,
    QUEUE_EMPTY,
    INVALID_GRID_DIFF_OBJECT,
    GRID_OUT_OF_BOUNDS,
    INVALID_MAJOR_DIRECTION,
};


void panic(PANICCODE panic){
    throw (panic);
}
#endif