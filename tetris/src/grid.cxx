#include "grid.hxx"

Grid::Grid(ge211::Dimensions dimensions)
    : dims_(dimensions)
    {
        //Brick_Type types_[dims_.width][dims_.height];
        for (size_t r = 0; r < dims_.height; r++) {
            for (size_t c = 0; c < dims_.width; c++) {
                types_[c][r] = Brick_Type::none;
            }
        }
    }

bool Grid::is_valid_position(ge211::Position pos) const
{
    return pos.x >= 0 && pos.x < dims_.width
        && pos.y >= 0 && pos.y < dims_.height;
}

//returns the Brick_Type at the position, returning Brick_Type::none
//if there is none
Brick_Type Grid::get_brick_type(ge211::Position pos) const
{
    return types_[pos.x][pos.y];
}

//sets the Brick_Type at the position to be the Brick_Type specified by unit
//if unit is Brick_Type::none, removes the unit at position pos from units_
void Grid::set_brick_type(ge211::Position pos, Brick_Type unit)
{
    types_[pos.x][pos.y] = unit;
}