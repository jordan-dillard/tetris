#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test")
{
    CHECK( 1 + 1 == 2 );
}

TEST_CASE("grid size generates correctly")
{
    Model m1 = Model();
    CHECK (m1.play_grid().dimensions() == ge211::Dimensions{10, 20});

    Model m2 = Model(15);
    CHECK (m1.play_grid().dimensions() == ge211::Dimensions{10, 20});
    //hard-coded size :)
}

TEST_CASE("bottom collision checking")
{
    Model m = Model();
    m.update_current_brick(initial_brick(Brick_Type::L));
    CHECK(m.in_bounds_(m.shadow()));
    //makes sure that next_ is initialized and set to current_ when that happens
    //makes sure that next_ stacks on top of current_ and cannot move below current_
    //makes sure that next_ is initialized and set to current_ when that happens
    //makes sure that when moved to a different column, current_ drops to the bottom of the grid
}

TEST_CASE("line is cleared")
{
    Model m = Model();
    //initialize the bottom line of the grid to be full
    m.tick();


}

TEST_CASE("Tetrimino hugs edges")
{
    Model m = Model();
    //makes sure that a tetrimino cannot move past the left and right edges of the grid
}

TEST_CASE("ticks correctly")
{
    Model m = Model();
    //check to make sure tetrimino generates at top, goes down with each tick, and hits the lowest possible position
    //also check to make sure next becomes current when the block is switching
}

TEST_CASE("Tetrimino generates at top edge")
{
    Model m = Model();
    m.update_current_brick(initial_brick(Brick_Type::J));
    CHECK(m.current_brick().positions()[0] == ge211::Position{4, 0});
    CHECK(m.current_brick().positions()[1] == ge211::Position{5, 0});
    CHECK(m.current_brick().positions()[2] == ge211::Position{3, 0});
    CHECK(m.current_brick().positions()[3] == ge211::Position{5, 1});
}

TEST_CASE("Tetrimino rotates")
{
    Model m = Model();
    //initialize current brick
    brick = rotate_brick_cw(brick);
    //check brick positions
    brick = rotate_brick_ccw(brick);
    //check original brick positions

    //also check for rotation not happening when a piece would go out of bounds as a result of rotation,
    //whether clockwise or counter-clockwise
}

TEST_CASE("hits top")
{
    Model m = Model();
    //also should check for hitting top and being full!
}

TEST_CASE("hard and soft dropping")
{
    Model m = Model();
    m.update_current_brick(initial_brick(Brick_Type::O));
    Brick brick = m.current_brick();
    CHECK(brick.positions()[0] == ge211::Position{4, 1});
    CHECK(brick.positions()[1] == ge211::Position{5, 1});
    CHECK(brick.positions()[2] == ge211::Position{4, 2});
    CHECK(brick.positions()[3] == ge211::Position{5, 2});
    brick = move_down(brick, 1);
    m.hard_drop();
    //check the brick's position to be at the bottom of the board
    //check that there is a new brick
    m.hard_drop();
    //the new brick's position should be on top of the old brick
}

TEST_CASE("holding")
{
    Model m = Model();
    CHECK(m.hold_brick() == Brick_Type::none);
    Brick_Type type_a = m.current_brick().type();
    Brick_Type type_b = m.next_brick();
    m.hold();
    CHECK(m.hold_brick() == type_a);
    CHECK(m.current_brick().type() == type_b);
    Brick_Type type_c = m.next_brick();
    m.hold();
    CHECK(m.hold_brick() == type_a);
    CHECK(m.current_brick().type() == type_b);
    CHECK(m.next_brick() == type_c);
    m.hard_drop();
    m.hold();
    CHECK(m.hold_brick() == type_c);
    CHECK(m.current_brick().type() == type_a);
}