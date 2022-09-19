#include "Mazesolver.h"
const uint8_t DIM = 8;
const uint8_t COMMAND_STACK_SIZE = 10;
class Maze_Solver_Pico_Interface : public MazeSolver_Interface
{
    Queue<COMMAND_STACK_SIZE,BASIC_COMMANDS> command_stack;
public:
    uint32_t get_dimensions(){
        return DIM ;
    }

    void do_move(BASIC_COMMANDS c){
        command_stack.push(c);
    }
    RelWallState query_wall_states(){
        Serial.println("?");
        while (!Serial.available())
        {
            /* code */
        }
        uint8_t r = Serial.read();
        bool left = r&4;
        bool front = r&2;
        bool right = r&1;
        return RelWallState(left,front,right);
        
    }
};
void main_solver(){
    Maze_Solver_Pico_Interface interface = Maze_Solver_Pico_Interface();
    MazeSolver<DIM> solver = MazeSolver<DIM>(&interface);
    
    while(!solver.orient());
    while(!solver.search());
    Serial.println("end");

}

void setup()
{
    Serial.begin(9600);
    main_solver();
}

void loop()
{
    
}
