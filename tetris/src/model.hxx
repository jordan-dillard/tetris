#pragma once

#include <ge211.hxx>
#include <brick.hxx>
#include <grid.hxx>

//Model classes:


//State of the Model:
class Model {

public:

    //initializes a model to have 10 columns and num_rows rows
    Model(int num_rows);

    //initializes a model to have 10 columns and 20 rows
    Model();

    //returns the current brick
    Brick current_brick() const
    {return current_brick_;}

    //returns the brick held in the hold
    Brick_Type hold_brick() const
    {return hold_brick_;}

    //returns the brick that will come down next
    Brick_Type next_brick() const
    {return next_brick_;}

    Grid get_grid() const
    {return play_grid_;}

    int score() const
    {return score_;}

    //returns a Rectangle that can be used to iterate over the game grid
    ge211::Rectangle play_grid() const;


    //forcefully updates the game to place the current brick at the bottom
    //of its current column (as far as it can go) and turn the next brick
    //into the current brick
    void hard_drop();

    //returns the current brick's "shadow", the lowest position it can
    //reach in its current column without overlapping another piece or going
    //over the bottom
    Brick shadow() const;

    //switches the current brick with the brick in the hold if the player
    //can hold (determined by if the piece has already been switched out
    //for what was in the hold, i.e. you can't switch hold and current
    //back once they have been switched without changing the value of current)
    //if there is no piece in the hold, the current piece goes to the
    //hold and is replaced by the next piece
    void hold();

    //update the game by shifting the current brick down by one square and
    //turning the next brick into the current brick if the current brick
    //cannot move further down
    void tick();

    //updates the grid by setting all positions in the first position vector
    //argument to none, while setting the Brick's positions_ to brick_type_.
    void update_grid(std::vector<ge211::Position>, Brick);

    bool is_active() const
    {return is_active_;}

    //returns whether or not the given Brick can exist with its current
    //positions used for determining whether a hypothetical brick after
    //a move (rotation or translation)would be allowed to exist on the board
    bool can_move(Brick&) const;

    void update_current_brick(Brick);

private:

    Brick current_brick_ = initial_brick(random_type());
    Brick_Type hold_brick_;
    Brick_Type next_brick_;

    Grid play_grid_;
    int score_ = 0;
    bool can_hold_ = true;

    bool is_active_ = true;

    //clears all filled lines currently on the board and appropriately deals
    //with scoring
    void clear_all_lines_();

    //clears a single line at the integer row position and does not
    //affect scoring
    void clear_line_(int);

    //returns whether or not the line at int row_number is filled and able
    //to be cleared
    bool line_is_filled_(int);

    //checks to see if the Brick will collide with any other bricks
    //returns true if the Brick has no collisions with any other pieces
    //on the grid
    bool collision_check_(Brick) const;

    //checks to see if the Brick has all positions within the bounds of
    //the game grid
    //returns true if the Brick is in bounds
    bool in_bounds_(Brick) const;

    //creates a new random brick and initializes it to the next_brick_
    Brick new_brick_();
};

