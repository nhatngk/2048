#ifndef FUNCTION_GAME_H_
#define FUNCTION_GAME_H_

#include "draw.h"

class Game
{
public:
	Game();

	~Game();

    int random_number();

    void random_card();

    bool full_board();

    bool can_move();

	bool lose();

	void event_input();

	bool down();

	bool up();

	bool right();

	bool left();
};

#endif
