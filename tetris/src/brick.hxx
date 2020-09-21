#pragma once
#include <ge211.hxx>
#include <vector>
#include <iostream>

enum class Brick_Type {
    T,
    I,
    O,
    L,
    J,
    S,
    Z,
    none
};

class Brick {
public:

    Brick(Brick_Type, std::vector<ge211::Position>&);

    std::vector<ge211::Position> positions() const
    { return positions_; }

    Brick_Type type() const
    { return type_; }

    bool contains_position(ge211::Position) const;

    //TODO: Fix this output declaration
    //std::ostream& operator<<(std::ostream&, Brick);

private:
    std::vector<ge211::Position> positions_;
    Brick_Type type_;
};

//initializes a new brick of a given Brick_Type type to have
//the proper positions and return it
Brick initial_brick(Brick_Type);

Brick_Type random_type();

//returns a new brick with the same shape of the current brick
//rotated clockwise and counter-clockwise, respectively
//the new Brick can be considered invalid when collision-checked by the model
Brick rotate_brick_cw(Brick);
Brick rotate_brick_ccw(Brick);

//moves the brick right by an integer number of spaces (positive or
//negative)
//the new Brick can be considered invalid when collision-checked by the model
Brick move_right(Brick, int);

//moves the brick down by an integer number of spaces (should be positive
//only)
//the new Brick can be considered invalid when collision-checked by the model
Brick move_down(Brick, int);