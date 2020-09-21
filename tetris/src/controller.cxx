#include "controller.hxx"

using namespace ge211;

Controller::Controller()
        : Controller(20)
{}

Controller::Controller(int height)
        : model_(height)
        , view_(model_)
        , audio_track_("type_a.wav")
{
    ge211::Mixer* mixer = get_mixer();
    ge211::Music_track type_a = ge211::Music_track(audio_track_, *mixer);
    mixer->play_music(type_a);
}

void Controller::draw(Sprite_set& sprites)
{
    if (model_.is_active())
        view_.draw(sprites);
    else {
        view_.draw_lose(sprites);
    }
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_frame(double)
{
    if (model_.is_active()) {
        if (upd_frames_ == 0) {
            model_.tick();
            //printf("upd_frames_ = 0\n");
        }
        upd_frames_ = (upd_frames_ + 1) % (61 - 2 * level_);
        if (upd_frames_ < 0)
            upd_frames_ = 0;
        if (model_.score() > (level_ * level_ * 25))
            level_++;
        if (get_mixer()->get_music_state() == ge211::Mixer::State::paused) {
            get_mixer()->rewind_music();
            get_mixer()->resume_music();
        }
        if (level_ > 9 && type_b_music) {
            type_b_music = false;
            get_mixer()->pause_music();
            audio_track_ = "type_b.wav";
            get_mixer()->rewind_music();
            get_mixer()->attach_music(ge211::Music_track("type_b.wav",
                    *get_mixer()));
            get_mixer()->resume_music();
        }
        if (level_ > 19 && type_c_music) {
            get_mixer()->pause_music();
            audio_track_ = "danger.wav";
            get_mixer()->rewind_music();
            get_mixer()->attach_music(ge211::Music_track("danger.wav",
                    *get_mixer()));
            get_mixer()->resume_music();
            type_c_music = false;
        }
    } else {
        if (!played_lose_tune) {
            get_mixer()->pause_music();
            get_mixer()->play_effect(ge211::Sound_effect("gameover.wav",
                    *get_mixer()));
            played_lose_tune = true;
        }
    }
}

void Controller::on_key(ge211::Key key)
{
    if (model_.is_active()) {
        if (key == key.up()) {
            model_.hard_drop();
        }
        if (key == key.left()) {
            Brick b = move_right(model_.current_brick(), -1);
            if (model_.can_move(b)) {
                //printf("can move left!\n");
                model_.update_grid(model_.current_brick().positions(), b);
                model_.update_current_brick(b);
            }
        }
        if (key == key.right()) {
            Brick b = move_right(model_.current_brick(), 1);
            if (model_.can_move(b)) {
                //printf("can move right!\n");
                model_.update_grid(model_.current_brick().positions(), b);
                model_.update_current_brick(b);
            }
        }
        if (key == key.down()) {
            Brick b = move_down(model_.current_brick(), 1);
            if (model_.can_move(b)) {
                //printf("can move down!\n");
                model_.update_grid(model_.current_brick().positions(), b);
                model_.update_current_brick(b);
            }
        }
        if (key == ge211::Key::code('w')) {
            model_.hold();
        }
        if (key == ge211::Key::code('a')) {
            Brick b = rotate_brick_ccw(model_.current_brick());
            if (model_.can_move(b)) {
                //printf("can rotate ccw!\n");
                model_.update_grid(model_.current_brick().positions(), b);
                model_.update_current_brick(b);
            }
        }
        if (key == ge211::Key::code('d')) {
            Brick b = rotate_brick_cw(model_.current_brick());
            if (model_.can_move(b)) {
                //printf("can rotate cw!\n");
                model_.update_grid(model_.current_brick().positions(), b);
                model_.update_current_brick(b);
            }
        }
    }
}