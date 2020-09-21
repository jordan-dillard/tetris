#include "brick.hxx"

Brick::Brick(Brick_Type type, std::vector<ge211::Position>& units)
        : positions_(units),
          type_(type)
{}

bool Brick::contains_position(ge211::Position pos) const
{
    for (ge211::Position brick_pos : positions_) {
        if (brick_pos == pos)
            return true;
    }
    return false;
}

Brick rotate_brick_ccw(Brick brick)
{
    ge211::Dimensions offset = {brick.positions()[0].x, brick.positions()[0].y};
    std::vector<ge211::Position> new_positions;
    for (ge211::Position pos : brick.positions()) {
        ge211::Position temp_pos  = pos.up_left_by(offset);
        temp_pos = {temp_pos.y, -1*temp_pos.x};
        new_positions.push_back(temp_pos.down_right_by(offset));
    }
    return Brick(brick.type(), new_positions);
}

Brick rotate_brick_cw(Brick brick)
{
    ge211::Dimensions offset = {brick.positions()[0].x, brick.positions()[0].y};
    std::vector<ge211::Position> new_positions;
    for (ge211::Position pos : brick.positions()) {
        ge211::Position temp_pos  = pos.up_left_by(offset);
        temp_pos = {-1*temp_pos.y, temp_pos.x};
        new_positions.push_back(temp_pos.down_right_by(offset));
    }
    return Brick(brick.type(), new_positions);
}

Brick move_down(Brick brick, int num_spaces)
{
    std::vector<ge211::Position> posns;
    for (ge211::Position pos : brick.positions()) {
        pos.y += num_spaces;
        posns.push_back(pos);
    }
    return Brick(brick.type(), posns);
}

Brick move_right(Brick brick, int num_spaces)
{
    std::vector<ge211::Position> posns;
    for (ge211::Position pos : brick.positions()) {
        pos.x += num_spaces;
        posns.push_back(pos);
    }
    return Brick(brick.type(), posns);
}

Brick initial_brick(Brick_Type type)
{
    std::vector<ge211::Position> positions;
    switch (type) {
        case Brick_Type::I: positions = {{4, 0}, {3, 0}, {5, 0}, {6, 0}};
            break;
        case Brick_Type::O: positions = {{4, 0}, {5, 0}, {4, 1}, {5, 1}};
            break;
        case Brick_Type::T: positions = {{4, 0}, {5, 0}, {3, 0}, {4, 1}};
            break;
        case Brick_Type::J: positions = {{4, 0}, {5, 0}, {3, 0}, {5, 1}};
            break;
        case Brick_Type::L: positions = {{4, 0}, {5, 0}, {3, 0}, {3, 1}};
            break;
        case Brick_Type::S: positions = {{5, 0}, {4, 0}, {5, 1}, {6, 1}};
            break;
        case Brick_Type::Z: positions = {{4, 0}, {5, 0}, {4, 1}, {3, 1}};
            break;
        default: positions = {};
            break;
    }
    Brick b = Brick(type, positions);
    return b;
}

Brick_Type random_type()
{
    int rand = std::rand() % 7;
    switch (rand) {
        case 0: return Brick_Type::I;
        case 1: return Brick_Type::O;
        case 2: return Brick_Type::T;
        case 3: return Brick_Type::L;
        case 4: return Brick_Type::J;
        case 5: return Brick_Type::S;
        case 6: return Brick_Type::Z;
        default: return Brick_Type::none;
    }

}