#pragma once
#include <ge211.hxx>
#include <vector>
#include <brick.hxx>
#include <iostream>

class Grid {

public:

    //constructs a new Grid with the given dimensions
    explicit Grid(ge211::Dimensions dims);

    //returns the dimensions of the Grid for iterating
    ge211::Dimensions dimensions() const
    {return dims_;}

    //returns whether or not a position is in bounds for the Grid
    bool is_valid_position(ge211::Position) const;

    //returns the Brick_Type at the position, returning Brick_Type::none
    //if there is none
    Brick_Type get_brick_type(ge211::Position pos) const;

    //sets the Brick_Type at the position to be the Brick_Type specified by unit
    //if unit is Brick_Type::none, removes the unit at position pos from units_
    void set_brick_type(ge211::Position pos, Brick_Type unit);

    //TODO: Fix this output declaration
    //std::ostream& operator<<(std::ostream&, Grid const&);

private:

    ge211::Dimensions dims_;
    Brick_Type types_[10][20]; //TODO: Fix this if we have time?
};