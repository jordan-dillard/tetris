#pragma once
#include <ge211.hxx>
#include "model.hxx"


class View
{
public:
    explicit View(Model const&);

    void draw(ge211::Sprite_set& set);

    void draw_lose(ge211::Sprite_set& set);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    //ge211::Position display_to_board(ge211::Position);

    ge211::Position grid_to_display(ge211::Position);

    void set_score_sprite();

    int const grid_size = 36;

private:

    Model const& model_;

    ge211::Dimensions const square_dims_ = {grid_size, grid_size};

    ge211::Color const T_color_ = {255,0,255};
    ge211::Color const I_color_ = {0,255,255};
    ge211::Color const O_color_ = {255,255,0};
    ge211::Color const L_color_ = {255,165,0};
    ge211::Color const J_color_ = {0,0,255};
    ge211::Color const S_color_ = {0,255,0};
    ge211::Color const Z_color_ = {255, 0,0};
    ge211::Color const shadow_color_ = {128, 128, 128};
    ge211::Color const play_grid_color_ = {255, 255, 255};
    ge211::Color const window_color_ = {128, 128, 128};

    ge211::Rectangle_sprite const T_brick_{square_dims_, T_color_};
    ge211::Rectangle_sprite const I_brick_{square_dims_, I_color_};
    ge211::Rectangle_sprite const O_brick_{square_dims_, O_color_};
    ge211::Rectangle_sprite const L_brick_{square_dims_, L_color_};
    ge211::Rectangle_sprite const J_brick_{square_dims_, J_color_};
    ge211::Rectangle_sprite const S_brick_{square_dims_, S_color_};
    ge211::Rectangle_sprite const Z_brick_{square_dims_, Z_color_};
    ge211::Rectangle_sprite const shadow_brick_{square_dims_, shadow_color_};

    ge211::Image_sprite const T_hold_{"t_hold.svg.png"};
    ge211::Image_sprite const I_hold_{"i_hold.svg.png"};
    ge211::Image_sprite const O_hold_{"o_hold.svg.png"};
    ge211::Image_sprite const L_hold_{"l_hold.svg.png"};
    ge211::Image_sprite const J_hold_{"j_hold.svg.png"};
    ge211::Image_sprite const S_hold_{"s_hold.svg.png"};
    ge211::Image_sprite const Z_hold_{"z_hold.svg.png"};

    ge211::Rectangle_sprite const
           play_grid_block_{{model_.play_grid().dimensions()*grid_size},
                                                   play_grid_color_};
    ge211::Rectangle_sprite const window_block_{{36*4,36*4}, window_color_};

    ge211::Text_sprite const hold_{"HOLD:", ge211::Font("sans.ttf", 20)};
    ge211::Text_sprite const next_{"NEXT:", ge211::Font("sans.ttf", 20)};
    ge211::Text_sprite const score_{"SCORE: ", ge211::Font("sans.ttf", 20)};
    ge211::Text_sprite const lost_{"YOU LOST!", ge211::Font("sans.ttf", 30)};
    ge211::Text_sprite score_num_;
};