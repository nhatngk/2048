#ifndef BASEVALUE_H_
#define BASEVALUE_H_

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDl_image.h>


extern int width, height;
extern int size_card ;
extern unsigned long long cards[7][7];
extern unsigned long long score;
extern unsigned long long high_score;
extern bool is_in_mode_options;
extern bool is_in_menu;
extern bool is_in_game_over;
extern bool is_in_game;
extern bool pre_tab_menu;
extern bool pre_tab_game_over;
extern bool quit;

const int font_size_teeny=11;
const int font_size_tiny = 20;
const int font_size_small = 25;
const int font_size_normal = 35;
const int font_size_medium = 45;
const int font_size_big = 50;
const int font_size_great = 70;

const SDL_Color color_background = {187, 173, 160};
const SDL_Color color_text = {238,228,218};
const SDL_Color color_score = {249, 246, 242};
const SDL_Color color_logo = {249, 246, 242};
const SDL_Color color_num_1 = {119,110,101};
const SDL_Color color_num_2 = {249, 246, 242};
const SDL_Color color_0 = {205,193,180};
const SDL_Color color_2 = {238, 228, 218};
const SDL_Color color_4 = {237, 224, 200};
const SDL_Color color_8 = {242, 177, 121};
const SDL_Color color_16 = {245, 149, 99};
const SDL_Color color_32 = {246, 124, 95};
const SDL_Color color_64 = {246, 94, 59};
const SDL_Color color_128 = {237, 207, 114};
const SDL_Color color_256 = {237, 204, 97};
const SDL_Color color_512 = {237, 200, 80};
const SDL_Color color_1024 = {237, 197, 63};
const SDL_Color color_2048 = {237, 194, 46};
const SDL_Color color_great_than_2048 = {60, 58, 50};

#endif
