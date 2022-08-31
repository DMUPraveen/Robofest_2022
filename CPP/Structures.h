#ifndef STRUCTURES_HEADER
#define STRUCTURES_HEADER
#include <stdint.h>
#include "Panic.h"

template <uint8_t MAX_SIZE, typename T>
class Stack
{
private:
    int32_t end = 0;
    T array[MAX_SIZE];

public:
    int32_t size()
    {
        return end;
    }

    bool empty()
    {
        return size() == 0;
    }

    bool full()
    {
        return size() == MAX_SIZE;
    }

    void push(T x)
    {
        if (full())
        {
            panic(PANICCODE::STACK_FULL);
        }
        array[end] = x;
        end++;
    }

    T pop()
    {
        if (empty())
        {
            panic(PANICCODE::STACK_EMPTY);
        }
        end--;
        return array[end];
    }

    T peek()
    {
        if(empty())
        {
            panic(PANICCODE::STACK_EMPTY);
        }
        return array[end-1];
    }

    void clear(){
        end = 0;
    }
};

template<uint8_t MAX_SIZE,typename T>
class Queue{
private:
    T array[MAX_SIZE+1];
    int32_t begin = 0;
    int32_t end = 0;
    int32_t MOD = MAX_SIZE+1;
public:
    int32_t size(){
        return (end - begin + MOD) % MOD;
    }

    bool empty(){
        return size() == 0;
    }

    bool full(){
        return size() == MAX_SIZE;
    }

    void push(T x){
        if(full()){
            panic(PANICCODE::QUEUE_FULL);
        }
        array[end] = x;
        end = (end+1) % MOD;

    }

    T pop(){
        if(empty()){
            panic(PANICCODE::QUEUE_EMPTY);
        }
        T ret = array[begin];
        begin = (begin+1) %MOD;
        return ret;
    }

    T peek(){
        if(empty()){
            panic(PANICCODE::QUEUE_EMPTY);
        }
        return array[begin];

    }

    void clear(){
        begin = 0;
        end = 0;
    }
};

enum class ABS_DIRECTION{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
};

enum class REL_DIRECTION{
    FRONT = 0,
    LEFT = 1,
    RIGHT = 2,
    BACK = 3,
};

struct Grid_Pos{
    int32_t i=0;
    int32_t j=0;
        
};

struct Relative_Grid_Pos{
    int32_t di;
    int32_t dj;
};

enum class BASIC_COMMANDS{
    FORWARD,
    TURN_LEFT,
    TURN_RIGHT,
    TURN_BACK,
    BACKWARD
};

#endif