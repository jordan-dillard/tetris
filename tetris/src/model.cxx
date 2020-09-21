#include "model.hxx"
#include <cmath>

Model::Model()
    : Model(20)
{}

Model::Model(int num_rows)
    : play_grid_({10, num_rows}),
      hold_brick_(Brick_Type::none)
{
    next_brick_ = random_type();

}

ge211::Rectangle Model::play_grid() const
{
    return ge211::Rectangle::from_top_left(ge211::Position{0, 0},
            play_grid_.dimensions());
}

void Model::hard_drop()
{
    update_grid(current_brick_.positions(), shadow());
    current_brick_ = shadow();
    clear_all_lines_();
    current_brick_ = initial_brick(next_brick_);
    update_grid(current_brick_.positions(), current_brick_);
    next_brick_ = random_type();
    can_hold_ = true;
}

Brick Model::shadow() const
{
    Brick temp_brick = current_brick_;
    while (can_move(temp_brick)) {
        temp_brick = move_down(temp_brick, 1);
    }
    return move_down(temp_brick, -1);
}

void Model::hold()
{
    if (can_hold_)
    {
        Brick_Type temp_type = hold_brick_;
        hold_brick_ = current_brick_.type();
        if (temp_type != Brick_Type::none) {
            Brick b = initial_brick(temp_type);
            update_grid(current_brick_.positions(), b);
            current_brick_ = b;
        }
        else {
            Brick b = initial_brick(next_brick_);
            update_grid(current_brick_.positions(), b);
            current_brick_ = b;
            next_brick_ = random_type();
        }
        can_hold_ = false;
    }
}

void Model::tick()
{
    if (is_active_) {
        update_grid(current_brick_.positions(), current_brick_);
        Brick temp_brick = move_down(current_brick_, 1);
        if (can_move(temp_brick)) {
            update_grid(current_brick_.positions(), temp_brick);
            current_brick_ = temp_brick;
        } else {
            clear_all_lines_();
            current_brick_ = initial_brick(next_brick_);
            if (can_move(current_brick_)) {
                update_grid(current_brick_.positions(), current_brick_);
                next_brick_ = random_type();
                can_hold_ = true;
            }
            else
                is_active_ = false;
        }
    }
}

void Model::clear_all_lines_()
{
    size_t num_cleared = 0;
    for (int i = 0; i < play_grid_.dimensions().height; i++) {
        if (line_is_filled_(i)) {
            clear_line_(i);
            num_cleared++;
        }
    }
    score_ += pow(3, num_cleared) * 10;
}

void Model::clear_line_(int row)
{
    //printf("made it to clear line %d\n", row);
    for (int i = 0; i < play_grid_.dimensions().width; i++) {
        //printf("clearing column %d\n", i);
        for (int j = row; j > 0; j--) {
            play_grid_.set_brick_type(ge211::Position{i, j},
                    play_grid_.get_brick_type(ge211::Position{i, j - 1}));
        }
        play_grid_.set_brick_type(ge211::Position{0, i}, Brick_Type::none);
    }
}

bool Model::line_is_filled_(int row)
{
    for (int i = 0; i < play_grid_.dimensions().width; i++) {
        if (play_grid_.get_brick_type(ge211::Position{i, row})
            == Brick_Type::none)
            return false;
    }
    return true;
}

bool Model::can_move(Brick& brick) const
{
    bool ret_statement = in_bounds_(brick) && collision_check_(brick);
    return ret_statement;
}

bool Model::collision_check_(Brick brick) const
{
    for (ge211::Position pos : brick.positions()) {
        if (play_grid_.get_brick_type(pos) != Brick_Type::none) {
            if (play_grid_.get_brick_type(pos) != current_brick_.type()
                || !current_brick_.contains_position(pos))
                return false;
        }
    }
    return true;
}

bool Model::in_bounds_(Brick brick) const
{
    for (ge211::Position pos : brick.positions()) {
        if (!play_grid_.is_valid_position(pos))
            return false;
    }
    return true;
}

void Model::update_current_brick(Brick brick)
{
        current_brick_ = brick;
}

void Model::update_grid(std::vector<ge211::Position> old_posns, Brick brick)
{
    for (ge211::Position pos : old_posns)
    {play_grid_.set_brick_type(pos, Brick_Type::none);}
    for (ge211::Position pos : brick.positions())
    {play_grid_.set_brick_type(pos, brick.type());}

}
