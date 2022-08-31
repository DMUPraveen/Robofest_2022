#include "Utility.h"
#include <iostream>
using namespace std;

void assertTrue(bool condition, string test_name){
    if(condition){
        cout << test_name <<" -- OK" << endl ;
    }
    else{
        cout <<test_name <<" -- FAILED" <<endl;
    }
}

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
        cout << "RIGHT " << get_direction(right_direction(dir)) << endl;
        cout << "OPPOSITE " << get_direction(opposite_direction(dir)) << endl;
        cout << "--------" << endl;
    }
    for(int i=0;i<4;i++){
        auto dir = ABS_DIRECTION(i);
        cout << "--------" << endl;
        cout << get_direction(dir) << endl;
        cout << "FRONT " << get_direction(get_rel_direction(dir,REL_DIRECTION::FRONT)) << endl;
        assertTrue(get_rel_dir_from_two_abs(dir,get_rel_direction(dir,REL_DIRECTION::FRONT))==REL_DIRECTION::FRONT,"Front is Correct");
        cout << "LEFT " << get_direction(get_rel_direction(dir,REL_DIRECTION::LEFT)) << endl;
        assertTrue(get_rel_dir_from_two_abs(dir,get_rel_direction(dir,REL_DIRECTION::LEFT))==REL_DIRECTION::LEFT,"left is Correct");
        cout << "RIGHT " << get_direction(get_rel_direction(dir,REL_DIRECTION::RIGHT)) << endl;
        assertTrue(get_rel_dir_from_two_abs(dir,get_rel_direction(dir,REL_DIRECTION::RIGHT))==REL_DIRECTION::RIGHT,"right is Correct");
        cout << "OPPOSITE " << get_direction(get_rel_direction(dir,REL_DIRECTION::BACK)) << endl;
        assertTrue(get_rel_dir_from_two_abs(dir,get_rel_direction(dir,REL_DIRECTION::BACK))==REL_DIRECTION::BACK,"back is Correct");
        cout << "--------" << endl;
    }
    return 0;
}