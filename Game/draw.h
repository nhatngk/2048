#ifndef DRAW_H_
#define DRAW_H_

#include "base_value.h"

class Draw
{
    public:
        SDL_Renderer* renderer;

        SDL_Window* window;

        SDL_Event event;

        SDL_Rect background;

        SDL_Rect _new_game;

        SDL_Rect mode;

        SDL_Rect logo;

        SDL_Rect menu;

        SDL_Rect _score;

        SDL_Rect _high_score;

        SDL_Rect exit;

        SDL_Rect tile[7][7];

        SDL_Rect mode_size_4;

        SDL_Rect mode_size_5;

        SDL_Rect mode_size_6;

        SDL_Rect mode_size_7;


        Draw(const char* title, int width, int height);

        ~Draw();
        void draw_label(const char * font, const int& size, SDL_Color color, const char * text, SDL_Renderer* renderer,SDL_Rect bg);

        void paint_tile(int& i, int& j, const char * text, const int font_size, SDL_Color color_bg, SDL_Color color);

        void update_score();

        void draw_grid();

        void handle_event_start();

        void mode_options();

        void handle_event_in_mode_otp();

        void handle_event_in_game();

        void handle_event_game_over();

        void render();

        void check_best_score();

        void save_best_score();

        void menu_tab();

        void game_over();

        void new_game();

        void close();
};

#endif
