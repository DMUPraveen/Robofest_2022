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
};