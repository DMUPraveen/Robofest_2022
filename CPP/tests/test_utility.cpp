#include "Utility.h"
#include <iostream>
using namespace std;

string get_direction(ABS_DIRECTION dir){
    switch (dir)
    {
    case ABS_DIRECTION::NORTH:
        return "NORTH" ;
        break;
    case ABS_DIRECTION::SOUTH:
        return "SOUTH" ;
        break;
    case ABS_DIRECTION::EAST:
        return "EAST" ;
        break;
    case ABS_DIRECTION::WEST:
        return "WEST" ;
        break;
    
    default:
        return "UNKNOWN";
    }
}

int main(){
    for(int i=0;i<4;i++){
        auto dir = ABS_DIRECTION(i);
        cout << "--------" << endl;
        cout << get_direction(dir) << endl;
        cout << "LEFT " << get_direction(left_direction(dir)) << endl;
        // cout << "RIGHT " << get_direction(righ(dir)) << endl;
        cout << "OPPOSITE " << get_direction(opoosite_direction(dir)) << endl;
        cout << "--------" << endl;
    }
    return 0;
}