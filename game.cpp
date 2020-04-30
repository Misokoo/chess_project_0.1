#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/game.h"
#include "../include/square.h"
using namespace std;


void Game::print()
{
	this->cb->print();
	string player_color[] = {"Black", "White"};
	test_if_check();
	cout << " player " << player_color[this->player_white] << " to play" << endl;
}

bool Game::deplace(Square &origin, Square &dest)
{
	bool ok_moove = this->cb->allow_to_move(origin, dest);
	bool result = this->cb->deplacement(origin, dest, ok_moove);
	if (!result)
		cout << "moove not allowed" << endl;
	return result;
}

bool Game::white_to_play() const
{
	return this->player_white;
}

void Game::change_player_to_play()
{
	this->player_white = !this->player_white;
}

bool Game::check_hit_regular(Square origin, Square dest)
{
	bool reponse(true);
	string player_color[] = {"Black", "White"};
	if (this->cb->create_piece(origin) == NULL)
	{
		cout << "the case you selected is empty" << endl;
		return false;
	}

	if (player_white != cb->create_piece(origin)->get_is_white())
		return false;
	if (cb->create_piece(dest) != NULL &&
	player_white == cb->create_piece(dest)->get_is_white())
	{
		cout << "you tried to eat one of your own pieces" << endl;
		return false;
	}
	return reponse;
}

bool Game::test_if_check()
{
	return this->cb->check_check(this->player_white);
}

bool Game::hit()
{
	bool test = false;
	string my_hit;
	cin >> my_hit;
	if (my_hit == "/quit")
	{
		cout << "you've asked for the end of the game" << endl;
		return true;
	}
	if ((test = check_if_roque(my_hit)) == true)
	{
		if (proceed_roque(my_hit))
		{
			cout << "coup bien joué, on change de personne" << endl;
			change_player_to_play();
			this->cb->reinitialized_en_passant(this->player_white);
		}
	}
	Square origin(my_hit.substr(0, 2));
	Square dest(my_hit.substr(2, 2));
	cout << origin.to_string() << dest.to_string() << endl;
	if (!test && saisie_correcte(my_hit) && check_hit_regular(origin, dest) && check_en_passant(origin, dest))
	{
		cout << "EN PASSANT REUSSI EAYAAAAAAAAA" << endl;
		cout << "coup bien joué, on change de personne" << endl;
		change_player_to_play();
		this->cb->reinitialized_en_passant(this->player_white);
	}
	else
	{
		if (!test && saisie_correcte(my_hit) && check_hit_regular(origin, dest))
		{
			if (this->deplace(origin, dest))
			{
				cout << "coup bien joué, on change de personne" << endl;
				change_player_to_play();
				this->cb->reinitialized_en_passant(this->player_white);
			}
		}
	}
	return false;
}

bool Game::check_if_roque(string my_hit)
{
	if (my_hit == "O-O-O" || my_hit == "O-O")
		return true;
	return false;
}

bool Game::proceed_roque(string my_hit)
{
	if (my_hit == "O-O-O")
		return succed_roque(true);
	else if (my_hit == "O-O")
		return succed_roque(false);
	return false;
}

bool Game::succed_roque(bool groroque)
{
	Piece *king;
	Piece *rock = nullptr;
	if (groroque)
		tie(ignore, rock) = cb->get_Rock_roque(this->white_to_play());
	else
		tie(rock, ignore) = cb->get_Rock_roque(this->white_to_play());
	if(rock == nullptr)
	{
		cout << "roque impossible" << endl;
		return false;
	}
	int i, j;
	tie(i, j, king) = cb->get_king(this->white_to_play());
	Square king_pos = Square(i, j);
	bool result = cb->moove_rock_roque(king_pos, rock->get_pos());
	return result;
}

bool Game::check_en_passant(Square origin, Square dest)
{
	return this->cb->proceed_en_passant(origin, dest);
}