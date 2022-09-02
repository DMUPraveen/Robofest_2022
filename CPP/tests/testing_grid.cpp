#include "Mazesolver.h"

std::string move_to_str(BASIC_COMMANDS c){
    switch (c)
    {
    case BASIC_COMMANDS::FORWARD:
        return "FORWARD";
        break;
     
    case BASIC_COMMANDS::BACKWARD:
        return "BACKWARD";
        break;
    case BASIC_COMMANDS::TURN_BACK:
        return "TURN_BACK";
        break;
    case BASIC_COMMANDS::TURN_LEFT:
        return "TURN_LEFT";
        break;
    case BASIC_COMMANDS::TURN_RIGHT:
        return "TURN_RIGHT";
        break;
    default:
        break;
    }
    return "";

}
class maze_solver_debug: public MazeSolver_Interface
{
public:
    virtual uint8_t get_dimensions() {return 0;}
    virtual void do_move(BASIC_COMMANDS c) {
        std::cout << move_to_str(c) <<std::endl;
        
    }
    virtual RelWallState query_wall_states(){
        int left,front,right;
        std::cout <<"?" << std::endl;
        std::cin >> left>>front>>right;
        return RelWallState{left,front,right};
        
    }

};
int main(){
    auto que = maze_solver_debug();
    auto robot = MazeSolver<14>(&que);
    robot.show_internal();

    return 0;
}