#pragma once

#include "model.hxx"
#include "view.hxx"

// The main game class for Tetris.
class Controller : public ge211::Abstract_game
{
public:
    // Constructs a game with a 20-row by 10-column grid
    explicit Controller();

    // // Constructs a game with an height-row by 10-column grid
    //
    // ERRORS:
    //  - Throws `ge211::Client_logic_error` if either dimension is less
    //    than 2 or greater than 8.
    Controller(int height);

// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //

    // TODO: Add any input handlers you need, e.g.:
    //  - on_mouse_up for mouse clicks,
    //  - on_mouse_move for mouse tracking, or
    //  - on_frame for animation (?).

    void on_key(ge211::Key) override;

    void on_frame(double) override;

    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;



private:
    Model            model_;
    View             view_;
    int              upd_frames_ = 0;
    int              level_ = 1;
    std::string      audio_track_;
    bool type_b_music = true;
    bool type_c_music = true;
    bool played_lose_tune = false;

    // TODO: Add any UI state you need, e.g.:
    //  - the position of the mouse, or
    //  - the position of a keyboard-controller cursor.

};