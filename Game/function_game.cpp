#include "base_value.h"
#include "function_game.h"
#include "draw.h"

Game::Game()
{
    random_card();
    random_card();
}

Game::~Game()
{

}

int Game::random_number()
{
    int r = rand()%100;
    if(r < 79)
    {
        return 2;
    }
    else return 4;
}

void Game::random_card()
{
    int x = rand()%size_card;
    int y = rand()%size_card;
    if(cards[y][x] == 0)
    {
        int num = random_number();
        cards[y][x] = num;
    }
    else
    {
        random_card();
    }
}

bool Game::full_board()
{
    for(int y=0; y<size_card; y++)
    {
        for(int x=0; x<size_card; x++)
        {
            if(cards[y][x] == 0)
            {
                return false;
            }
        }
    }
     return true;
}

bool Game::can_move()
{
    for(int y=0; y<size_card-1; y++)
    {
        for(int x=0; x<size_card; x++)
        {
            if(cards[y][x] == cards[y+1][x] || cards[y][x] == cards[y][x+1])
            {
                return true;
            }
        }
    }
    return false;
}

bool Game::lose()
{
    if(full_board() == true && can_move()== false)
    {
        is_in_menu = false;
        is_in_mode_options = false;
        is_in_game = false;
        is_in_game_over = true;
        return true;
    }
    else return false;
}

void Game::event_input()
{
    SDL_Event e;
    SDL_WaitEvent(&e);
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_w:
                up();
                break;

            case SDLK_DOWN :
            case SDLK_s:
                down();
                break;

            case SDLK_LEFT:
            case SDLK_a:
                left();
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                right();
                break;

            case SDLK_ESCAPE:
                quit = true;
                break;
            default:
                break;
        }
}

bool Game::up()
{
    bool can_do=false;

    for(int x=0; x<size_card; x++)
    {
        for(int y=0; y<size_card-1; y++)
        {
            for(int y1=y+1; y1<size_card; y1++)
            {
                if(cards[y1][x]>0)
                {
                    if(cards[y][x] == 0)
                    {
                        cards[y][x]=cards[y1][x];
                        cards[y1][x]=0;
                        can_do=true;
                        y--;
                    }
                    else if(cards[y][x]==cards[y1][x])
                    {
                        cards[y][x]*=2;
                        cards[y1][x]=0;
                        score+=cards[y][x];
                        can_do=true;
                    }
                    break;
                }

            }
        }
    }
    if(can_do)
    {
        random_card();
    }
    return can_do;
}

bool Game::down()
{
    bool can_do = false;

    for(int x=0;x<size_card;x++)
    {
        for(int y=size_card-1;y>0;y--)
        {
            for(int y1=y-1; y1>=0; y1--)
            {
                if(cards[y1][x]>0)
                {
                    if(cards[y][x]==0)
                    {
                        cards[y][x]=cards[y1][x];
                        cards[y1][x]=0;
                        can_do=true;
                        y++;
                    }
                    else if(cards[y][x]==cards[y1][x])
                    {
                        cards[y][x]*=2;
                        cards[y1][x]=0;
                        score+=cards[y][x];
                        can_do=true;
                    }
                    break;
                }
            }
        }
    }

    if(can_do)
    {
        random_card();
    }
    return can_do;
}

bool Game::left()
{
    bool can_do = false;
    for(int y=0; y < size_card; y++)
    {
        for(int x=0; x < size_card-1; x++)
        {
            for(int x1=x+1; x1 < size_card; x1++)
            {
                if(cards[y][x1]>0)
                {
                    if(cards[y][x]==0)
                    {
                        cards[y][x]=cards[y][x1];
                        cards[y][x1]=0;
                        can_do=true;
                        x--;
                    }
                    else if(cards[y][x]==cards[y][x1])
                    {
                        cards[y][x]*=2;
                        cards[y][x1]=0;
                        score+=cards[y][x];
                        can_do=true;
                    }
                    break;
                }
            }
        }
    }

     if(can_do)
    {
        random_card();
    }
    return can_do;
}

bool Game::right()
{
    bool can_do = false;

    for(int y=0;y<size_card;y++)
    {
        for(int x=size_card-1;x>0;x--)
        {
            for(int x1=x-1; x1>=0; x1--)
            {
                if(cards[y][x1]>0)
                {
                    if(cards[y][x]==0)
                    {
                        cards[y][x]=cards[y][x1];
                        cards[y][x1]=0;
                        can_do=true;
                        x++;
                    }
                    else if(cards[y][x]==cards[y][x1])
                    {
                        cards[y][x]*=2;
                        cards[y][x1]=0;
                        score+=cards[y][x];
                        can_do=true;
                    }
                    break;
                }
            }
        }
    }

     if(can_do)
    {
        random_card();
    }
    return can_do;
}
