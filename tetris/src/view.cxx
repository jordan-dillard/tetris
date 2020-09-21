#include "view.hxx"

using namespace ge211;

View::View(Model const& model)
        : model_(model)
// You may want to add sprite initialization here
{ }

void View::draw(Sprite_set& set)
{
    for(int row = 0; row < model_.play_grid().dimensions().height; row++){
        for(int col = 0; col < model_.play_grid().dimensions().width; col++){
            Position pos = {col, row};
            Brick_Type type = model_.get_grid().get_brick_type(pos);
            //printf("%d\n", type);
            switch (type) {
                case Brick_Type::T :
                    set.add_sprite(T_brick_,
                            grid_to_display(ge211::Position {col, row}));
                    //printf("added T sprite\n");
                    break;
                case Brick_Type::I :
                    set.add_sprite(I_brick_,
                            grid_to_display(ge211::Position {col, row}));
                    //printf("added I sprite\n");
                    break;
                case Brick_Type::O :
                    set.add_sprite(O_brick_,
                            grid_to_display(ge211::Position {col, row}));
                    //printf("added O sprite\n");
                    break;
                case Brick_Type::L :
                    set.add_sprite(L_brick_,
                            grid_to_display(ge211::Position {col, row}));
                    //printf("added L sprite\n");
                    break;
                case Brick_Type::J :
                    set.add_sprite(J_brick_,
                            grid_to_display(ge211::Position {col, row}));
                    //printf("added J sprite\n");
                    break;
                case Brick_Type::S :
                    set.add_sprite(S_brick_,
                            grid_to_display(ge211::Position {col, row}));
                    //printf("added S sprite\n");
                    break;
                case Brick_Type::Z :
                    set.add_sprite(Z_brick_,
                            grid_to_display(ge211::Position {col, row}));
                    //printf("added Z sprite\n");
                    break;
                default: break;
            }
        }
    }
    for (ge211::Position p : model_.shadow().positions())
    {
        set.add_sprite(shadow_brick_, grid_to_display(p), -1);
    }

    Brick_Type type = model_.hold_brick();
    switch (type) {
        case Brick_Type::T :
            set.add_sprite(T_hold_, grid_to_display(ge211::Position{10, 7}));
            break;
        case Brick_Type::I :
            set.add_sprite(I_hold_, grid_to_display(ge211::Position{10, 7}));
            break;
        case Brick_Type::O :
            set.add_sprite(O_hold_, grid_to_display(ge211::Position{10, 6}));
            break;
        case Brick_Type::L :
            set.add_sprite(L_hold_, grid_to_display(ge211::Position{10, 7}));
            break;
        case Brick_Type::J :
            set.add_sprite(J_hold_, grid_to_display(ge211::Position{10, 7}));
            break;
        case Brick_Type::S :
            set.add_sprite(S_hold_, grid_to_display(ge211::Position{10, 7}));
            break;
        case Brick_Type::Z :
            set.add_sprite(Z_hold_, grid_to_display(ge211::Position{10, 7}));
            break;
        default:
            break;
    }

    type = model_.next_brick();
    switch (type) {
        case Brick_Type::T :
            set.add_sprite(T_hold_, grid_to_display(ge211::Position{10, 2}));
            break;
        case Brick_Type::I :
            set.add_sprite(I_hold_, grid_to_display(ge211::Position{10, 2}));
            break;
        case Brick_Type::O :
            set.add_sprite(O_hold_, grid_to_display(ge211::Position{10, 1}));
            break;
        case Brick_Type::L :
            set.add_sprite(L_hold_, grid_to_display(ge211::Position{10, 2}));
            break;
        case Brick_Type::J :
            set.add_sprite(J_hold_, grid_to_display(ge211::Position{10, 2}));
            break;
        case Brick_Type::S :
            set.add_sprite(S_hold_, grid_to_display(ge211::Position{10, 2}));
            break;
        case Brick_Type::Z :
            set.add_sprite(Z_hold_, grid_to_display(ge211::Position{10, 2}));
            break;
        default:
            break;
    }

    set.add_sprite(play_grid_block_, grid_to_display({0,0}), -2);

    set.add_sprite(window_block_, grid_to_display({10,1}), -2);
    set.add_sprite(window_block_, grid_to_display({10,6}), -2);

    set.add_sprite(hold_, grid_to_display({11, 5}), -1);
    set.add_sprite(next_, grid_to_display({11, 0}), -1);
    set_score_sprite();
    set.add_sprite(score_, grid_to_display({11, 10}), -1);
    set.add_sprite(score_num_, grid_to_display({11, 11}), -1);
}

void View::draw_lose(ge211::Sprite_set& set) {
    int center_x = initial_window_dimensions().width/2
            - lost_.dimensions().width/2;
    int center_y = initial_window_dimensions().height/2
            - lost_.dimensions().height/2;

    set.add_sprite(lost_, {center_x,center_y});
    set.add_sprite(score_, {center_x,center_y + 36});
    set.add_sprite(score_num_,
            {center_x + score_.dimensions().width,center_y + 36});


}

Dimensions View::initial_window_dimensions() const
{
    ge211::Dimensions dims = {(model_.play_grid().width + 4) * grid_size,
                              (model_.play_grid().height + 1) * grid_size};
    return dims;
}

std::string View::initial_window_title() const
{
    return "Tetris";
}

ge211::Position View::grid_to_display(ge211::Position grid_pos)
{
    return ge211::Position{grid_pos.x * grid_size, grid_pos.y * grid_size};
}

void View::set_score_sprite(){

    std::string score_string = std::to_string(model_.score());
    Font sans("sans.ttf", 20);
    score_num_ = Text_sprite::Builder(sans)
            .message(score_string)
            .build();
}