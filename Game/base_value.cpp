#include "base_value.h"
bool is_in_menu = true;
bool is_in_mode_options = false;
bool is_in_game = false;
bool is_in_game_over = false;
bool pre_tab_menu = false;
bool pre_tab_game_over = false;
int size_card = 4;
unsigned long long cards[7][7] = {0};
int width = 510;
int height = 650;
unsigned long long score = 0;
unsigned long long high_score = 0;
bool quit = false;

