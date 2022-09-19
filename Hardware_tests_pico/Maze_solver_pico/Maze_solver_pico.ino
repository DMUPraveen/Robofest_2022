#include "Mazesolver.h"
const uint8_t DIM = 8;
const uint8_t COMMAND_STACK_SIZE = 10;
class Maze_Solver_Pico_Interface : public MazeSolver_Interface
{

public:

    Queue<COMMAND_STACK_SIZE, BASIC_COMMANDS> command_stack;
    uint32_t get_dimensions()
    {
        return DIM;
    }

    void do_move(BASIC_COMMANDS c)
    {
        command_stack.push(c);
    }
    RelWallState query_wall_states()
    {
        Serial.println("?");
        while (!Serial.available())
        {
            /* code */
        }
        uint8_t r = Serial.read();
        bool left = r & 4;
        bool front = r & 2;
        bool right = r & 1;
        return RelWallState(left, front, right);
    }
};
void main_solver()
{
    Maze_Solver_Pico_Interface interface = Maze_Solver_Pico_Interface();
    MazeSolver<DIM> solver = MazeSolver<DIM>(&interface);

    while (!solver.orient())
        ;
    while (!solver.search())
    {
        while (!interface.command_stack.empty())
        {
            BASIC_COMMANDS c = interface.command_stack.pop();
            switch (c)
            {
            case BASIC_COMMANDS::FORWARD:
                Serial.println("FORWARD");
                break;

            case BASIC_COMMANDS::BACKWARD:
                Serial.println("BACKWARD");
                break;
            case BASIC_COMMANDS::TURN_BACK:
                Serial.println("TRUN_BACK");
                break;
            case BASIC_COMMANDS::TURN_LEFT:
                Serial.println("TURN_LEFT");
                break;
            case BASIC_COMMANDS::TURN_RIGHT:
                Serial.println("TURN_RIGHT");
                break;
            default:
                break;
            }
        }
    }
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
