#include "draw.h"
#include "function_game.h"

Draw::Draw(const char* title, int width, int height)
{
	TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* icon = IMG_Load("icon.png");
    SDL_SetWindowIcon(window, icon);
}

Draw::~Draw()
{

}

void Draw::draw_label(const char * font, const int& size, SDL_Color color, const char * text, SDL_Renderer* renderer, SDL_Rect bg )
{
	TTF_Font * fonts = TTF_OpenFont(font, size);
	int texW = 0;
	int texH = 0;
	SDL_Surface * surface = TTF_RenderText_Blended(fonts, text, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { bg.x+(bg.w-texW)/2, bg.y+(bg.h-texH)/2, texW, texH };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(fonts);
}

void Draw::draw_grid(){
	int top = 200, left = 50, width_bg = 410;

	SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255);
	SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);

    _score={240,10,100,80};
    SDL_RenderFillRect(renderer, &_score);
    _high_score={360,10,100,80};
    SDL_RenderFillRect(renderer, &_high_score);

	draw_label("fonts.ttf", font_size_small, color_text , "SCORE" ,renderer,{240,10,100,50});
	draw_label("fonts.ttf", font_size_small, color_text, "BEST", renderer,{360,10,100,50});
	char buf[9];
	itoa(score, buf, 10);
	int len1 =strlen(buf);
    int fs_score;
    switch(len1)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            fs_score = 25;
            break;
        case 7:
            fs_score = 22;
            break;
        case 8:
            fs_score = 19;
            break;
        case 9:
            fs_score = 16;
            break;
    }
	draw_label("fonts.ttf", fs_score, color_score, buf,renderer,{240,40,100,50});

	char buffer[9];
	itoa(high_score, buffer, 10);
    int len2 =strlen(buffer);
    int fs_hscore;
    switch(len2)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            fs_hscore = 25;
            break;
        case 7:
            fs_hscore = 22;
            break;
        case 8:
            fs_hscore = 19;
            break;
        case 9:
            fs_hscore = 16;
            break;
    }
	draw_label("fonts.ttf", fs_hscore, color_score, buffer,renderer,{360,40,100,50});


	SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);

	background.x = left;
	background.y = top;
	background.w = width_bg;
	background.h = width_bg;
	SDL_RenderFillRect(renderer, &background);


	SDL_SetRenderDrawColor(renderer,245, 149, 99,255);

	_new_game={240,100,100,40};
    menu = {360,100,100,40};
	SDL_RenderFillRect(renderer, &_new_game);
    SDL_RenderFillRect(renderer, &menu);
	draw_label("fonts.ttf", 17, color_num_2, "NEW GAME", renderer, _new_game);
    draw_label("fonts.ttf", 17, color_num_2, "MENU", renderer, menu);
    SDL_SetRenderDrawColor(renderer,237,194,46,255);
    logo={50,10,180,180};
    SDL_RenderFillRect(renderer, &logo);

	draw_label("fonts.ttf", font_size_great, color_logo, "2048",renderer,logo);

    draw_label("fonts.ttf", font_size_teeny, color_background, "Join the numbers and get to the 2048 tile!", renderer,{240,140,230,60});

    int d,size_tile;

    switch(size_card)
    {
        case 4:
            d = 10;
            size_tile = 90;
            break;
        case 5:
            d = 5;
            size_tile = 76;
            break;
        case 6:
            d = 2;
            size_tile = 66;
            break;
        case 7:
            d = 4;
            size_tile = 54;
            break;
    }

	int _Step = d + size_tile;

	for (int i = 0; i < size_card; i++)
	{
		for (int j = 0; j < size_card; j++)
		{
			tile[i][j].x = left + d + j*_Step;
			tile[i][j].y = top + d + i*_Step;
			tile[i][j].w = size_tile;
			tile[i][j].h = size_tile;

			paint_tile(i, j, "", font_size_tiny, color_0, color_num_1);
		}
	}

	SDL_RenderPresent(renderer);
}


void Draw::update_score()
{
	SDL_Rect rect1 = {240,50,100,40};
	SDL_Rect rect2 = {360,50,100,40};
	SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
	SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);

char buf[9];
	itoa(score, buf, 10);
	int len1 =strlen(buf);
    int fs_score;
    switch(len1)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            fs_score = 25;
            break;
        case 7:
            fs_score = 22;
            break;
        case 8:
            fs_score = 19;
            break;
        case 9:
            fs_score = 16;
            break;
    }
	draw_label("fonts.ttf", fs_score, color_score, buf,renderer,{240,40,100,50});

	check_best_score();
	char buffer[9];
	itoa(high_score, buffer, 10);
	int len2 =strlen(buffer);
    int fs_hscore;
    switch(len2)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            fs_hscore = 25;
            break;
        case 7:
            fs_hscore = 22;
            break;
        case 8:
            fs_hscore = 19;
            break;
        case 9:
            fs_hscore = 16;
            break;
    }
	draw_label("fonts.ttf", fs_hscore, color_score, buffer, renderer,{360,40,100,50});
	SDL_RenderPresent(renderer);
}

void Draw::paint_tile(int& i, int& j, const char * text, int font_size, SDL_Color color_bg, SDL_Color color){
	SDL_SetRenderDrawColor(renderer,color_bg.r, color_bg.g, color_bg.b,255);
	SDL_RenderFillRect(renderer, &tile[i][j]);

	TTF_Font * fonts = TTF_OpenFont("fonts.ttf", font_size);
	SDL_Surface * surface = TTF_RenderText_Blended(fonts, text, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect srcRect;
	SDL_Rect desRect;

	SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
	srcRect.x = 0;
	srcRect.y =  0;


	desRect.w = srcRect.w;
	desRect.h = srcRect.h;

	desRect.x = tile[i][j].x+(tile[i][j].w-desRect.w)/2;
	desRect.y = tile[i][j].y+(tile[i][j].h-desRect.h)/2;

	SDL_RenderCopy(renderer, texture, NULL, &desRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(fonts);
	SDL_RenderPresent(renderer);
}

void Draw::render()
{
	Draw::update_score();
	for (int y=0; y<size_card; y++){
		for (int x=0; x<size_card; x++){
                if(size_card == 4)
                {
                    switch(cards[y][x])
                    {
                    case 2:
                        paint_tile(y, x, "2", font_size_big, color_2, color_num_1);
                        break;
                    case 4:
                        paint_tile(y, x, "4", font_size_big, color_4, color_num_1);
                        break;
                    case 8:
                        paint_tile(y, x, "8", font_size_big, color_8, color_num_2);
                        break;
                    case 16:
                        paint_tile(y, x, "16", font_size_big, color_16, color_num_2);
                        break;
                    case 32:
                        paint_tile(y, x, "32", font_size_big, color_32, color_num_2);
                        break;
                    case 64:
                        paint_tile(y, x, "64", font_size_big, color_64, color_num_2);
                        break;
                    case 128:
                        paint_tile(y, x, "128", font_size_medium, color_128, color_num_2);
                        break;
                    case 256:
                        paint_tile(y, x, "256", font_size_medium, color_256, color_num_2);
                        break;
                    case 512:
                        paint_tile(y, x, "512", font_size_medium, color_512, color_num_2);
                        break;
                    case 1024:
                        paint_tile(y, x, "1024", font_size_normal, color_1024, color_num_2);
                        break;
                    case 2048:
                        paint_tile(y, x, "2048", font_size_normal, color_2048, color_num_2);
                        break;
                    case 4096:
                        paint_tile(y, x, "4096", font_size_normal, color_great_than_2048, color_num_2);
                        break;
                    case 8192:
                        paint_tile(y, x, "8192", font_size_normal, color_great_than_2048, color_num_2);
                        break;
                    case 16384:
                        paint_tile(y, x, "16384", 27, color_great_than_2048, color_num_2);
                        break;
                    case 32768:
                        paint_tile(y, x, "32768", 27, color_great_than_2048, color_num_2);
                        break;
                    case 65536:
                        paint_tile(y, x, "65536", 27 , color_great_than_2048, color_num_2);
                        break;
                    default:
                        paint_tile(y, x, "", font_size_tiny, color_0, color_num_1);
                        break;
                    }
                }
                if(size_card == 5)
                {
                    switch(cards[y][x])
                    {
                    case 2:
                        paint_tile(y, x, "2", 42, color_2, color_num_1);
                        break;
                    case 4:
                        paint_tile(y, x, "4", 42, color_4, color_num_1);
                        break;
                    case 8:
                        paint_tile(y, x, "8", 42, color_8, color_num_2);
                        break;
                    case 16:
                        paint_tile(y, x, "16", 42, color_16, color_num_2);
                        break;
                    case 32:
                        paint_tile(y, x, "32", 42, color_32, color_num_2);
                        break;
                    case 64:
                        paint_tile(y, x, "64", 42, color_64, color_num_2);
                        break;
                    case 128:
                        paint_tile(y, x, "128", 38, color_128, color_num_2);
                        break;
                    case 256:
                        paint_tile(y, x, "256", 38, color_256, color_num_2);
                        break;
                    case 512:
                        paint_tile(y, x, "512", 38, color_512, color_num_2);
                        break;
                    case 1024:
                        paint_tile(y, x, "1024", 30, color_1024, color_num_2);
                        break;
                    case 2048:
                        paint_tile(y, x, "2048", 30, color_2048, color_num_2);
                        break;
                    case 4096:
                        paint_tile(y, x, "4096", 30, color_great_than_2048, color_num_2);
                        break;
                    case 8192:
                        paint_tile(y, x, "8192", 30, color_great_than_2048, color_num_2);
                        break;
                    case 16384:
                        paint_tile(y, x, "16384", 23, color_great_than_2048, color_num_2);
                        break;
                    case 32768:
                        paint_tile(y, x, "32768", 23, color_great_than_2048, color_num_2);
                        break;
                    case 65536:
                        paint_tile(y, x, "65536", 23, color_great_than_2048, color_num_2);
                        break;
                    default:
                        paint_tile(y, x, "", font_size_tiny, color_0, color_num_1);
                        break;
                    }
                }
                    if(size_card == 6)
                    {
                        switch(cards[y][x])
                        {
                        case 2:
                            paint_tile(y, x, "2", 37, color_2, color_num_1);
                            break;
                        case 4:
                            paint_tile(y, x, "4", 37, color_4, color_num_1);
                            break;
                        case 8:
                            paint_tile(y, x, "8", 37, color_8, color_num_2);
                            break;
                        case 16:
                            paint_tile(y, x, "16", 37, color_16, color_num_2);
                            break;
                        case 32:
                            paint_tile(y, x, "32", 37, color_32, color_num_2);
                            break;
                        case 64:
                            paint_tile(y, x, "64", 37, color_64, color_num_2);
                            break;
                        case 128:
                            paint_tile(y, x, "128", 33, color_128, color_num_2);
                            break;
                        case 256:
                            paint_tile(y, x, "256", 33, color_256, color_num_2);
                            break;
                        case 512:
                            paint_tile(y, x, "512", 33, color_512, color_num_2);
                            break;
                        case 1024:
                            paint_tile(y, x, "1024", 26, color_1024, color_num_2);
                            break;
                        case 2048:
                            paint_tile(y, x, "2048", 26, color_2048, color_num_2);
                            break;
                        case 4096:
                            paint_tile(y, x, "4096", 26, color_great_than_2048, color_num_2);
                            break;
                        case 8192:
                            paint_tile(y, x, "8192", 26, color_great_than_2048, color_num_2);
                            break;
                        case 16384:
                            paint_tile(y, x, "16384", 20, color_great_than_2048, color_num_2);
                            break;
                        case 32768:
                            paint_tile(y, x, "32768", 20, color_great_than_2048, color_num_2);
                            break;
                        case 65536:
                            paint_tile(y, x, "65536", 20, color_great_than_2048, color_num_2);
                            break;
                        default:
                            paint_tile(y, x, "", font_size_tiny, color_0, color_num_1);
                            break;
                    }
                }
                if(size_card == 7)
                    {
                        switch(cards[y][x])
                        {
                        case 2:
                            paint_tile(y, x, "2", 30, color_2, color_num_1);
                            break;
                        case 4:
                            paint_tile(y, x, "4", 30, color_4, color_num_1);
                            break;
                        case 8:
                            paint_tile(y, x, "8", 30, color_8, color_num_2);
                            break;
                        case 16:
                            paint_tile(y, x, "16", 30, color_16, color_num_2);
                            break;
                        case 32:
                            paint_tile(y, x, "32", 30, color_32, color_num_2);
                            break;
                        case 64:
                            paint_tile(y, x, "64", 30, color_64, color_num_2);
                            break;
                        case 128:
                            paint_tile(y, x, "128", 27, color_128, color_num_2);
                            break;
                        case 256:
                            paint_tile(y, x, "256", 27, color_256, color_num_2);
                            break;
                        case 512:
                            paint_tile(y, x, "512", 27, color_512, color_num_2);
                            break;
                        case 1024:
                            paint_tile(y, x, "1024", 21, color_1024, color_num_2);
                            break;
                        case 2048:
                            paint_tile(y, x, "2048", 21, color_2048, color_num_2);
                            break;
                        case 4096:
                            paint_tile(y, x, "4096", 21, color_great_than_2048, color_num_2);
                            break;
                        case 8192:
                            paint_tile(y, x, "8192", 21, color_great_than_2048, color_num_2);
                            break;
                        case 16384:
                            paint_tile(y, x, "16384", 16, color_great_than_2048, color_num_2);
                            break;
                        case 32768:
                            paint_tile(y, x, "32768", 16, color_great_than_2048, color_num_2);
                            break;
                        case 65536:
                            paint_tile(y, x, "65536", 16, color_great_than_2048, color_num_2);
                            break;
                        default:
                            paint_tile(y, x, "", font_size_tiny, color_0, color_num_1);
                            break;
                    }
                }
        }
    }
}

void Draw::handle_event_start()
{
	SDL_WaitEvent(&event);
		switch (event.type)
			{
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                        {
                            quit = true;
                        }
                        break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT){
                            int X=event.button.x;
                            int Y=event.button.y;
                            if (X>_new_game.x && X < _new_game.x + _new_game.w
                                && Y>  _new_game.y && Y < _new_game.y + _new_game.h)
                                {

                                    SDL_SetRenderDrawColor(renderer,0,0,255,255);
                                    SDL_RenderFillRect(renderer,&_new_game);
                                    draw_label("fonts.ttf", 50, color_text , "NEW GAME", renderer,_new_game);
                                    SDL_RenderPresent(renderer);
                                    SDL_Delay(100);
                                    Draw::new_game();
                                    is_in_menu = false;
                                    is_in_mode_options = false;
                                    is_in_game = true;
                                    is_in_game_over = false;
                                }

                            if(X>mode.x && X<mode.x + mode.w
                               && Y > mode.y && Y < mode.y + mode.h)
                            {
                                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                                SDL_RenderFillRect(renderer,&mode);
                                draw_label("fonts.ttf", 50, color_text , "MODE", renderer, mode);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(100);
                                Draw::mode_options();
                                is_in_menu = false;
                                is_in_mode_options = true;
                                is_in_game = false;
                                is_in_game_over = false;
                                pre_tab_menu = true;
                                pre_tab_game_over = false;
                            }

                            if (X>exit.x&& X < exit.x + exit.w
                                && Y>exit.y&& Y < exit.y + exit.h)
                            {
                                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                                SDL_RenderFillRect(renderer,&exit);
                                draw_label("fonts.ttf", 50, color_text , "EXIT", renderer, exit);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(100);
                                quit = true;
                            }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    int mouseX=event.motion.x;
                    int mouseY=event.motion.y;
                    if ((mouseX>_new_game.x && mouseX < _new_game.x + _new_game.w
                         && mouseY>_new_game.y && mouseY <_new_game.y + _new_game.h)
                        ||(mouseX>mode.x && mouseX < mode.x + mode.w
                           && mouseY>mode.y && mouseY < mode.y + mode.h)
                        ||(mouseX>exit.x && mouseX < exit.x + exit.w
                           && mouseY>exit.y && mouseY < exit.y + exit.h)){
                        SDL_Cursor* cursor;
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                        SDL_SetCursor(cursor);
                    }
                    else{
                        SDL_Cursor* cursor;
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                        SDL_SetCursor(cursor);
                    }
                    break;

		}
}
void Draw::handle_event_in_mode_otp()
{
	SDL_WaitEvent(&event);
		switch (event.type)
			{
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                        {
                            quit = true;
                        }
                        break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT){
                            int X=event.button.x;
                            int Y=event.button.y;
                            if (X>mode_size_4.x && X < mode_size_4.x + mode_size_4.w
                                && Y>  mode_size_4.y && Y < mode_size_4.y + mode_size_4.h)
                                {
                                    size_card = 4;
                                }

                            if (X>mode_size_5.x && X < mode_size_5.x + mode_size_5.w
                                && Y>  mode_size_5.y && Y < mode_size_5.y + mode_size_5.h)
                                {
                                    size_card = 5;
                                }

                           if (X>mode_size_6.x && X < mode_size_6.x + mode_size_6.w
                                && Y>  mode_size_6.y && Y < mode_size_6.y + mode_size_6.h)
                                {
                                    size_card = 6;
                                }
                            if (X>mode_size_7.x && X < mode_size_7.x + mode_size_7.w
                                && Y>  mode_size_7.y && Y < mode_size_7.y + mode_size_7.h)
                                {
                                    size_card = 7;
                                }
                            if (X>menu.x && X < menu.x + menu.w
                                && Y>  menu.y && Y < menu.y + menu.h)
                                {
                                    SDL_SetRenderDrawColor(renderer,0,0,255,255);
                                    SDL_RenderFillRect(renderer,&menu);
                                    draw_label("fonts.ttf", 50, color_text , "BACK", renderer, menu);
                                    SDL_RenderPresent(renderer);
                                    SDL_Delay(100);
                                    if(pre_tab_menu)
                                    {
                                        Draw::menu_tab();
                                        is_in_menu = true;
                                        is_in_mode_options = false;
                                        is_in_game = false;
                                        is_in_game_over = false;
                                    }
                                    else if(pre_tab_game_over)
                                    {

                                        Draw::game_over();
                                        is_in_menu = false;
                                        is_in_mode_options = false;
                                        is_in_game = false;
                                        is_in_game_over = true;
                                    }
                                }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    int mouseX=event.motion.x;
                    int mouseY=event.motion.y;
                    if ((mouseX>mode_size_4.x && mouseX < mode_size_4.x + mode_size_4.w
                         && mouseY>mode_size_4.y && mouseY <mode_size_4.y + mode_size_4.h)
                        ||(mouseX>mode_size_5.x && mouseX < mode_size_5.x + mode_size_5.w
                         && mouseY>mode_size_5.y && mouseY <mode_size_5.y + mode_size_5.h)
                         ||(mouseX>mode_size_6.x && mouseX < mode_size_6.x + mode_size_6.w
                         && mouseY>mode_size_6.y && mouseY <mode_size_6.y + mode_size_6.h)
                         ||(mouseX>mode_size_7.x && mouseX < mode_size_7.x + mode_size_7.w
                         && mouseY>mode_size_7.y && mouseY <mode_size_7.y + mode_size_7.h)
                         ||(mouseX>menu.x && mouseX < menu.x + menu.w
                         && mouseY>menu.y && mouseY <menu.y + menu.h)
                        ){
                        SDL_Cursor* cursor;
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                        SDL_SetCursor(cursor);
                    }
                    else{
                        SDL_Cursor* cursor;
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                        SDL_SetCursor(cursor);
                    }
                    break;

		}
}

void Draw::handle_event_in_game()
{
	SDL_WaitEvent(&event);
		switch (event.type)
			{
                 case SDL_WINDOWEVENT:
                        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                            {
                                quit = true;
                            }
                    break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button==SDL_BUTTON_LEFT)
                {
                    int X=event.button.x;
                    int Y=event.button.y;
                    if (X>_new_game.x && X < _new_game.x + _new_game.w
                        && Y>_new_game.y && Y < _new_game.y + _new_game.h)
                    {
                        Draw::new_game();
                        is_in_menu = false;
                        is_in_mode_options = false;
                        is_in_game = true;
                        is_in_game_over = false;
                    }
				}
				if (event.button.button==SDL_BUTTON_LEFT)
                {
                    int X=event.button.x;
                    int Y=event.button.y;
                    if (X>menu.x && X < menu.x + menu.w
                        && Y>menu.y && Y < menu.y + menu.h)
                    {
                        Draw::menu_tab();
                        is_in_menu = true;
                        is_in_mode_options = false;
                        is_in_game = false;
                        is_in_game_over = false;
                    }
				}
				break;
			case SDL_MOUSEMOTION:
				int mouseX=event.motion.x;
				int mouseY=event.motion.y;
				if ((mouseX>_new_game.x && mouseX < _new_game.x + _new_game.w
                    && mouseY>_new_game.y && mouseY < _new_game.y + _new_game.h)
                    ||(mouseX>menu.x && mouseX < menu.x + menu.w
                    && mouseY>menu.y && mouseY < menu.y + menu.h))
                {
					SDL_Cursor* cursor;
					cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
					SDL_SetCursor(cursor);
				}
				else
                {
					SDL_Cursor* cursor;
					cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
					SDL_SetCursor(cursor);
				}
				break;

		}
}

void Draw::handle_event_game_over()
{
	SDL_WaitEvent(&event);
		switch (event.type)
			{
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
                        {
                            quit = true;
                        }
                        break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT){
                            int X=event.button.x;
                            int Y=event.button.y;
                            if (X>_new_game.x && X < _new_game.x + _new_game.w
                                && Y>_new_game.y && Y < _new_game.y + _new_game.h)
                                {
                                    SDL_SetRenderDrawColor(renderer,0,0,255,255);
                                    SDL_RenderFillRect(renderer,&_new_game);
                                    draw_label("fonts.ttf", 50, color_text , "TRY AGAIN", renderer, _new_game);
                                    SDL_RenderPresent(renderer);
                                    SDL_Delay(100);
                                    Draw::new_game();
                                    is_in_menu = false;
                                    is_in_mode_options = false;
                                    is_in_game = true;
                                    is_in_game_over = false;
                                }
                            if(X>mode.x && X<mode.x + mode.w
                               && Y > mode.y && Y < mode.y + mode.h)
                            {
                                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                                SDL_RenderFillRect(renderer,&mode);
                                draw_label("fonts.ttf", 50, color_text , "MODE", renderer,mode);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(100);
                                Draw::mode_options();
                                is_in_menu = false;
                                is_in_mode_options = true;
                                is_in_game = false;
                                is_in_game_over = false;
                                pre_tab_game_over = true;
                                pre_tab_menu = false;
                            }
//                            if (X>menu.x && X < menu.x + menu.w
//                                && Y>  menu.y && Y < menu.y + menu.h)
//                                {
//                                    SDL_SetRenderDrawColor(renderer,0,0,255,255);
//                                    SDL_RenderFillRect(renderer,&menu);
//                                    draw_label("fonts.ttf", 50, color_text , "MENU", renderer,menu);
//                                    SDL_RenderPresent(renderer);
//                                    SDL_Delay(100);
//                                    Draw::menu_tab();
//                                    is_in_menu = true;
//                                    is_in_mode_options = false;
//                                    is_in_game = false;
//                                    is_in_game_over = false;
//                                }

                            if (X>exit.x && X < exit.x + exit.w
                                && Y>exit.y && Y < exit.y + exit.h)
                            {
                                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                                SDL_RenderFillRect(renderer,&exit);
                                draw_label("fonts.ttf", 50, color_text , "EXIT", renderer, exit);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(100);
                                    quit = true;
                            }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    int mouseX=event.motion.x;
                    int mouseY=event.motion.y;
                    if ((mouseX>_new_game.x && mouseX < _new_game.x + _new_game.w
                         && mouseY>_new_game.y && mouseY < _new_game.y + _new_game.h)
//                        ||(mouseX>menu.x && mouseX < menu.x + menu.w
//                            && mouseY>menu.y && mouseY < menu.y + menu.h)
                        ||(mouseX>mode.x && mouseX < mode.x + mode.w
                           && mouseY>mode.y && mouseY < mode.y + mode.h)
                        ||(mouseX>exit.x && mouseX < exit.x + exit.w
                            && mouseY>exit.y && mouseY < exit.y + exit.h)){
                        SDL_Cursor* cursor;
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                        SDL_SetCursor(cursor);
                    }
                    else{
                        SDL_Cursor* cursor;
                        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                        SDL_SetCursor(cursor);
                    }
                    break;

		}
}

void Draw::check_best_score()
{
	std::fstream f;
	f.open("score.txt", std::ios::in);

	if(f.is_open())
	{
		f >> high_score;
		f.close();
	}
}

void Draw::save_best_score()
{
	std::fstream f;
	if (score>high_score)
	{
		f.open("score.txt", std::ios::out);
		f << score;
		f.close();
	}
}

void Draw::new_game()
{
	score = 0;

	for (int y = 0; y < size_card; y++)
	{
		for(int x= 0; x < size_card; x++)
		{
			cards[y][x] = 0;
		}
	}
	draw_grid();
	Game* a;
	a = new Game();
}

void Draw::menu_tab()
{
    SDL_SetRenderDrawColor(renderer,  250, 248, 239, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer,237,194,46,255);
    logo={130,10,250,250};

    SDL_RenderFillRect(renderer, &logo);
    draw_label("fonts.ttf", 100, color_logo, "2048", renderer, logo);


    SDL_SetRenderDrawColor(renderer,187, 173, 160, 255);
    _new_game= {70,300,370,70};
    mode = {70,390,370,70};
    _high_score= {70,480,370,70};
    exit = {70,570,370,70};

    SDL_RenderFillRect(renderer,&_new_game);
    SDL_RenderFillRect(renderer,&mode);
    SDL_RenderFillRect(renderer,&_high_score);
    SDL_RenderFillRect(renderer,&exit);

    draw_label("fonts.ttf", 50, color_text , "NEW GAME", renderer,_new_game);
    draw_label("fonts.ttf", 50, color_text , "MODE", renderer,mode);
    draw_label("fonts.ttf", 25, color_text , "BEST SCORE", renderer,{70,480,370,40});
	char buf[9];
	itoa(high_score, buf, 10);
	draw_label("fonts.ttf", 30, color_score, buf, renderer,{70,510,370,40});
	draw_label("fonts.ttf", 50, color_text , "EXIT", renderer, exit);


    SDL_RenderPresent(renderer);
}

void Draw::game_over()
{
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
	SDL_RenderClear(renderer);


	draw_label("fonts.ttf",80,color_text,"Game Over!",renderer,{0,0,510,160});


	SDL_SetRenderDrawColor(renderer,200,200,200,255);

    _score = {70,160,370,80};
    _new_game = {70,270,370,80};
    mode ={70,380,370,80};
//    menu = {70,430,370,80};
    exit = {70,490,370,80};

    SDL_RenderFillRect(renderer,&_score);
    SDL_RenderFillRect(renderer,&_new_game);
    SDL_RenderFillRect(renderer,&mode);
//    SDL_RenderFillRect(renderer,&menu);
    SDL_RenderFillRect(renderer,&exit);

    draw_label("fonts.ttf", 30, color_text , "SCORE", renderer,{70,160,370,40});

	char buf[9];
	itoa(score, buf, 10);

	draw_label("fonts.ttf", 35, color_score, buf,  renderer,{70,200,370,40});

	draw_label("fonts.ttf", 50, color_text , "TRY AGAIN", renderer,_new_game);

	draw_label("fonts.ttf", 50, color_text , "MODE", renderer, mode);
//    draw_label("fonts.ttf", 50, color_text , "MENU", renderer, menu);
	draw_label("fonts.ttf", 50, color_text , "EXIT", renderer, exit);

	SDL_RenderPresent(renderer);
}

void Draw::mode_options()
{
    SDL_SetRenderDrawColor(renderer,  250, 248, 239, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer,237,194,46,255);
    logo={130,10,250,250};

    SDL_RenderFillRect(renderer, &logo);
    draw_label("fonts.ttf", 100, color_logo, "2048", renderer,logo);

    SDL_SetRenderDrawColor(renderer,200,200,200,255);
    mode_size_4 = {70,280,370,60};
    mode_size_5 = {70,355,370,60};
    mode_size_6 = {70,430,370,60};
    mode_size_7 = {70,505,370,60};
    menu = {70,580,370,60};
    SDL_RenderFillRect(renderer,&mode_size_4);
    SDL_RenderFillRect(renderer,&mode_size_5);
    SDL_RenderFillRect(renderer,&mode_size_6);
    SDL_RenderFillRect(renderer,&mode_size_7);
    SDL_RenderFillRect(renderer,&menu);

    SDL_SetRenderDrawColor(renderer,0,0,255,255);

    switch (size_card)
    {
        case 4:
            SDL_RenderFillRect(renderer,&mode_size_4);
            break;
        case 5:
            SDL_RenderFillRect(renderer,&mode_size_5);
            break;
        case 6:
            SDL_RenderFillRect(renderer,&mode_size_6);
            break;
        case 7:
            SDL_RenderFillRect(renderer,&mode_size_7);
            break;
    }
    draw_label("fonts.ttf", 50, color_text , "4X4", renderer,mode_size_4);
    draw_label("fonts.ttf", 50, color_text , "5X5",  renderer,mode_size_5);
    draw_label("fonts.ttf", 50, color_text , "6X6", renderer,mode_size_6);
    draw_label("fonts.ttf", 50, color_text , "7X7",  renderer,mode_size_7);
    draw_label("fonts.ttf", 50, color_text , "BACK", renderer,menu);

    SDL_RenderPresent(renderer);
}

void Draw::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}
