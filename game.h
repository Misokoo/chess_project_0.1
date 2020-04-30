#ifndef GAME_HEADER
#define GAME_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "chessboard.h"
using namespace std;
class Game
{
protected:
	Chessboard *cb;
	bool player_white;

public:
	Game()
	{
		this->cb = new Chessboard();
		this->player_white = true;
	}

	/** @brief indicate which play has to play
     * @result true if white to play, false if black
     */
	bool white_to_play() const;

	/** @brief change the player to play
	 * switch arg play_white_to_play with complement of boolean
     */
	void change_player_to_play();

	/** @brief print chessboard and indicate if the player is on check
	 * call the print function from chessboard class
	 * and check_check() function
     */
	void print();

	/** @brief Main function, proceed to all mechanics of chess game
	 * check if the request is correct, if the moove is an
	 * "en passant" or roque moove, if the moove is allow and
	 * proceed if it is the case.
	 * Dispay if the moove is done with a indication message for
	 * the player.
	 * @result boolean, if the moove was done succesfully
     */
	bool hit();

	/** @brief call allow_to_move() and deplacement() functions
	 * from chessboard Class
     * @param origin origin of the piece to moove
	 * @param dest dest of the piece to moove
     */
	bool deplace(Square &origin, Square &dest);

	/** @brief check if the player didnt select an empty case 
	 * and if he didnt try to eat one of his owns pieces
     * @param origin origin of the piece to moove
	 * @param dest dest of the piece to moove
     */
	bool check_hit_regular(Square origin, Square dest);

	/** @brief call check_check() from Chessboard Class
     */
	bool test_if_check();

	/** @brief check the In data and recognize
	 * pattern for calling a roque moove
	 * @param my_hit the request of the hit from the player
	 * @result bolean, true if the player ask for a roque, false else
     */
	bool check_if_roque(string my_hit);

	/** @brief function that launch mecanic behinf roque moove
	 * call succed_roque() function
	 * @param my_hit the request of the hit from the player
	 * @result bolean, true if roque was done, false else.
     */
	bool proceed_roque(string my_hit);

	/** @brief function that launch functions to do
	 * a little or big rock depending of the param
	 * @param groroque indicate if the roque is big or little
	 * @result bolean, true if roque was done, false else.
     */
	bool succed_roque(bool groroque);

	/** @brief execute proceed_en_passant() function from 
	 * Chessboard Class
     * @param origin origin of the piece to moove
	 * @param dest dest of the piece to moove
	 * @result bolean, true if roque was done, false else.
     */
	bool check_en_passant(Square origin, Square dest);
};

#endif
