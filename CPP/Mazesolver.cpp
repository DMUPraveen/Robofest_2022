#include "Mazesolver.h"

template<uint8_t DIM>
void MazeSolver<DIM>::make_internal_map(){
    for(int j=1;j<(internal_grid.get_width()-1);j++){
        internal_grid.set_wall(
            {0,j},{1,j}
        );
        internal_grid.set_wall(
            {internal_grid.get_height()-1,j},
            {internal_grid.get_height()-2,j}
        )
    }
    for(int i=1;i<(internal_grid.get_height()-1);i++){
        internal_grid.set_wall(
            {i,0},{i,1}
        )
        internal_grid.set_wall(
            {i,internal_grid.get_width()-1},
            {i,internal_grid.get_width()-2}
        )
    }
}

template<uint8_t DIM>
ABS_DIRECTION MazeSolver<DIM>::abs_dir_from_rel(REL_DIRECTION rel){
    return get_rel_direction(orientation,rel);
}

template<uint8_t DIM>
void MazeSolver<DIM>::make_wall_in_relative_direction(REL_DIRECTION rel){
    Relative_Grid_Pos other_cell_delta = abs_dir_to_relative_pos(abs_dir_from_rel(rel));

    internal_grid.set_wall(
        pos,
        {pos.i+other_cell_delta.di,pos.j+other_cell_delta.dj};
    )

}