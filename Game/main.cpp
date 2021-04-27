#include "function_game.h"

Game* ptr_game = nullptr;
Draw* ptr_draw = nullptr;

int main(int argc,char*argv[])
{
    srand(time(0));

    ptr_draw = new Draw("2048",width,height);

    ptr_game = new Game();

    ptr_draw->check_best_score();

    ptr_draw->menu_tab();

    while(!quit)
    {
        if(is_in_menu)
            {
                ptr_draw->menu_tab();
                ptr_draw->handle_event_start();
            }
        else if(is_in_mode_options)
            {
                ptr_draw->mode_options();
                ptr_draw->handle_event_in_mode_otp();
                if(is_in_mode_options)
                {
                    ptr_draw->mode_options();
                }
            }
        else if(is_in_game_over)
            {
                ptr_draw->game_over();
                ptr_draw->handle_event_game_over();
            }
        else if(ptr_game->lose()== true )
        {
                ptr_draw->game_over();
                ptr_draw->handle_event_game_over();
        }
         else if(is_in_game)
            {
                ptr_draw->handle_event_in_game();
                if(is_in_game)
                {
                ptr_game->event_input();
                ptr_draw->save_best_score();
                ptr_draw->render();
                }

            }
    }
    ptr_draw->close();

    return 0;
}
