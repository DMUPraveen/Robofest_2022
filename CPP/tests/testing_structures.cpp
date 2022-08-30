#include <iostream>
#include "Structures.h"
using namespace std;
void assertTrue(bool condition, string test_name){
    if(condition){
        cout << test_name <<" -- OK" << endl ;
    }
    else{
        cout <<test_name <<" -- FAILED" <<endl;
    }
}

void testing_Stack(){
    auto s = Stack<10,int>();
    assertTrue(s.empty(),"Intially Empty");
    s.push(5);
    assertTrue(s.size()==1,"Size when one is pushed");
    for(int i=0;i<9;i++){
        s.push(i);
    }
    assertTrue(s.full(),"Asserting Fulness");
    assertTrue(s.pop()==8,"Checking the popping action");
    for(int i=0;i<9;i++){
        s.pop();
    }
    assertTrue(s.empty(),"Empty after everything is removed again");
    for(int i=0;i<4;i++){
        s.push(i);
    }
    s.clear();
    assertTrue(s.empty(),"Empty after clear");
    s.push(1);
    assertTrue(s.size()==1,"Size when one is pushed");
    for(int i=0;i<9;i++){
        s.push(i);
    }
    assertTrue(s.full(),"Asserting Fulness");
    assertTrue(s.pop()==8,"Checking the popping action");
    for(int i=0;i<9;i++){
        s.pop();
    }
    assertTrue(s.empty(),"Empty after everything is removed again");
    

}


void testing_the_queue(){
    auto q = Queue<7,int> ();
    assertTrue(q.empty(),"Asserting intially empty queue");
    q.push(52);
    q.push(63);
    assertTrue(q.size() == 2,"Asserting q size");
    assertTrue(q.pop() == 52,"Poping the first element");
    q.push(75);
    q.push(69);
    assertTrue(q.size() == 3,"Asserting the size");
    assertTrue(q.pop() == 63,"Asserting poping again");
    for(int i=0;i<5;i++){
        q.push(i);
    }
    assertTrue(q.full(),"Asserting fulness");
    assertTrue(q.pop() == 75,"Asserting popping again");
    for(int i=0;i<6;i++){
        q.pop();
    }
    assertTrue(q.empty(),"Asserting emptyness");
    q.push(55);q.push(83);
    q.clear();
    assertTrue(true,"Clearing the queue");
    assertTrue(q.empty(),"Asserting intially empty queue");
    q.push(52);
    q.push(63);
    assertTrue(q.size() == 2,"Asserting q size");
    assertTrue(q.pop() == 52,"Poping the first element");
    q.push(75);
    q.push(69);
    assertTrue(q.size() == 3,"Asserting the size");
    assertTrue(q.pop() == 63,"Asserting poping again");
    for(int i=0;i<5;i++){
        q.push(i);
    }
    assertTrue(q.full(),"Asserting fulness");
    assertTrue(q.pop() == 75,"Asserting popping again");
    for(int i=0;i<6;i++){
        q.pop();
    }
    assertTrue(q.empty(),"Asserting emptyness");

}



int main(){

    testing_Stack();
    testing_the_queue();
    return 0;
}