#include "Mazesolver.h"

template <uint8_t DIM>
void MazeSolver<DIM>::make_internal_map()
{
    for (int j = 1; j < (internal_grid.get_width() - 1); j++)
    {
        internal_grid.set_wall(
            {0, j}, {1, j});
        internal_grid.set_wall(
            {internal_grid.get_height() - 1, j},
            {internal_grid.get_height() - 2, j})
    }
    for (int i = 1; i < (internal_grid.get_height() - 1); i++)
    {
        internal_grid.set_wall(
                         {i, 0}, {i, 1})
            internal_grid.set_wall(
                {i, internal_grid.get_width() - 1},
                {i, internal_grid.get_width() - 2})
    }
}

template <uint8_t DIM>
ABS_DIRECTION MazeSolver<DIM>::abs_dir_from_rel(REL_DIRECTION rel)
{
    return get_rel_direction(orientation, rel);
}

template <uint8_t DIM>
REL_DIRECTION MazeSolver<DIM>::rel_from_abs(ABS_DIRECTION abs_dir)
{
    return get_rel_dir_from_two_abs(orientation, abs_dir);
}

template <uint8_t DIM>
void MazeSolver<DIM>::make_wall_in_relative_direction(REL_DIRECTION rel)
{
    Relative_Grid_Pos other_cell_delta = abs_dir_to_relative_pos(abs_dir_from_rel(rel));

    internal_grid.set_wall(
        pos,
        {pos.i + other_cell_delta.di, pos.j + other_cell_delta.dj};)
}

template <uint8_t DIM>
void MazeSolver<DIM>::move_internal(BASIC_COMMANDS com)
{
    switch (com)
    {
    case BASIC_COMMANDS::FORWARD:
        Relative_Grid_Pos delta = abs_dir_to_relative_pos(orientation);
        pos = {pos.i + delta.di, pos.j + delta.dj};
        break;
    case BASIC_COMMANDS::BACKWARD:
        Relative_Grid_Pos delta = abs_dir_to_relative_pos(opposite_direction(orientation));
        pos = {pos.i + delta.di, pos.j + delta.dj};
        break;
    case BASIC_COMMANDS::TURN_BACK:
        orientation = opposite_direction(orientation);
        break;
    case BASIC_COMMANDS::TURN_LEFT:
        orientation = left_direction(orientation);
        break;
    case BASIC_COMMANDS::TURN_RIGHT:
        orientation = right_direction(orientation);
    }
}
template <uint8_t DIM>
void MazeSolver<DIM>::move(BASIC_COMMANDS com)
{
    move_internal(com);
    interface->do_move(com);
}

template <uint8_t DIM>
bool MazeSolver<DIM>::set_center()
{
    if (!major_direction_intialized)
        return false;
    if (centers_intializes)
        return true;
    centers_intializes = true;
    Relative_Grid_Pos delta = {
        abs_dir_to_relative_pos(major_direction).di,
        1};
    if (delta.di == 0)
    {
        panic(PANICCODE::INVALID_MAJOR_DIRECTION);
    }
    int64_t start_i = DIM;
    int64_t start_j = 1;
    Grid_Pos base_center = {
        start_i + delta.di * (DIM / 2 - 1),
        start_j + delta.dj * (delta.diM / 2 - 1)};
    centers[0] = base_center;
    centers[1] = Grid_Pos{base_center.i, base_center.j + delta.dj};
    centers[2] = Grid_Pos{base_center.i + delta.di, base_center.j};
    centers[3] = Grid_Pos{base_center.i + delta.di, base_center.j + delta.dj} ;
    ABS_DIRECTION wall_dir = opposite_direction(major_direction);
    for (int k = 1; k < internal_grid.get_width() - 1; k++)
    {
        int64_t next_i = start_i + abs_dir_to_relative_pos(wall_dir).di;
        internal_grid.set_wall({start_i, k}, {next_i, k});
    }

    return true;
}