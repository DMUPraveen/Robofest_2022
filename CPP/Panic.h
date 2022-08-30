enum class PANICCODE{
    PANIC,
    STACK_FULL,
    STACK_EMPTY,
    QUEUE_FULL,
    QUEUE_EMPTY,
};


void panic(PANICCODE panic){
    throw (panic);
}