#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/chessboard.h"
#include "../include/piece.h"
#include "../include/piece_annexe.h"
#include <tuple>
#include <cstdlib>
using namespace std;
#define min(a, b) (a < b ? 1 : 0)
#define max(a, b) (a > b ? 1 : 0)
#define CHECKNULL(op)      \
	do                     \
	{                      \
		if (op == nullptr) \
			raler(#op);    \
	} while (0)

void raler(char *msg)
{
	perror(msg);
	exit(1);
}

/* Main Fonctions */

void Chessboard::print() const
{
	string space5 = string(5, ' ');
	cout << endl;
	cout << "     a     b     c     d     e     f     g     h    " << endl;
	cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	for (int i(7); i >= 0; i--)
	{
		cout << i + 1 << " "; // numérotation ligne dans affichage
		for (int j(0); j < 8; j++)
		{
			cout << "|";
			if (chessboard[invert_posx(i)][j])
			{
				cout << "\u0020"; //U+0020 est un esapce utf-8 taille police
				chessboard[invert_posx(i)][j]->print();
				cout << "\u0020"; //<< ";
			}
			else
				cout << space5; // 2 ascii spaces
		}
		cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
		cout << endl;
	}
}

bool Chessboard::allow_to_move(Square origin, Square dest)
{
	bool ok_moove(false);
	Piece *piece_on_mvnt = create_piece(origin);
	if (piece_on_mvnt->get_is_pawn())
		ok_moove = allow_pawn(origin, dest, piece_on_mvnt);
	else if (piece_on_mvnt->get_is_rock())
		ok_moove = allow_rock(origin, dest, piece_on_mvnt);
	else if (piece_on_mvnt->get_is_bishop())
		ok_moove = allow_bishop(origin, dest, piece_on_mvnt);
	else if (piece_on_mvnt->get_is_queen())
		ok_moove = allow_queen(origin, dest, piece_on_mvnt);
	else if (piece_on_mvnt->movment_legal(origin, dest))
		ok_moove = true;
	return ok_moove;
}

bool Chessboard::deplacement(Square origin, Square dest, bool ok_moove)
{
	if (ok_moove)
	{
		bool was_mooved, is_white;
		tie(was_mooved, is_white) = move_piece(origin, dest);
		if (!this->check_check(is_white))
			return true;
		else
		{
			cancel_deplacement(origin, dest, !was_mooved);
			return false;
		}
	}
	return false;
}

bool Chessboard::check_check(bool player_is_white)
{
	int k_i, k_j;
	tie(k_i, k_j, ignore) = get_king(player_is_white);
	return enemy_can_check(player_is_white, k_i, k_j);
}

/* Allow Movment Function */

bool Chessboard::pawn_eat_smth(Square origin, Square dest, Piece *piece_on_mvnt)
{
	bool diag = diagonal_move_pawn(origin, dest, piece_on_mvnt->get_color());
	bool smth = (create_piece(dest)!= nullptr);
	return diag && smth && create_piece(origin)->get_is_pawn();
}

bool Chessboard::allow_pawn(Square origin, Square dest, Piece *piece_on_mvnt)
{
	bool ok_moove(false);
	if (piece_on_mvnt->movment_legal(origin, dest) &&
		this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] == NULL)
			ok_moove = true;
	else if (pawn_eat_smth(origin, dest, piece_on_mvnt))
		ok_moove = true;
	return ok_moove;
}

bool Chessboard::allow_rock(Square origin, Square dest, Piece *piece_on_mvnt)
{
	return piece_on_mvnt->movment_legal(origin, dest) && da_way_straight(origin, dest);
}

bool Chessboard::allow_bishop(Square origin, Square dest, Piece *piece_on_mvnt)
{
	return piece_on_mvnt->movment_legal(origin, dest) && nothing_in_da_way_diagonally(origin, dest);
}

bool Chessboard::allow_queen(Square origin, Square dest, Piece *piece_on_mvnt)
{
	return piece_on_mvnt->movment_legal(origin, dest) && da_way_queen(origin, dest);
}

/* Movment Functions */
tuple<bool, bool> Chessboard::move_piece(Square origin, Square dest)
{
	Piece *p = create_piece(origin);
	tuple<bool, bool> state_and_color(p->get_already_moved(), p->get_is_white());
	//cout << "on bouge " << this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]]->get_name() << endl;
	this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]] = nullptr; //pour delete
	p->set_pos(dest);
	p->piece_mooved();
	this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] = p;
	return state_and_color;
}

void Chessboard::cancel_deplacement(Square origin, Square dest, bool was_unmooved)
{
	Piece *piece_on_mvnt = create_piece(dest);
	this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] = nullptr; //pour delete
	piece_on_mvnt->set_pos(origin);
	if (was_unmooved)
		piece_on_mvnt->piece_unmooved();
	this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]] = piece_on_mvnt;
}

/* Check Functions */
tuple<int, int, Piece *> Chessboard::get_king(bool player_color)
{
	tuple<int, int, Piece *> pos_k(0, 0, nullptr);
	for (int i = 0; i < 8; i++)
	{
		for (int j(0); j < 8; j++)
		{
			if (chessboard[i][j] &&
				chessboard[i][j]->get_is_white() == player_color)
			{
				if (chessboard[i][j]->get_is_king())
				{
					get<0>(pos_k) = i;
					get<1>(pos_k) = j;
					get<2>(pos_k) = this->chessboard[i][j];
				}
			}
		}
	}
	return pos_k;
}

bool Chessboard::enemy_can_check(bool player_is_white, int k_i, int k_j)
{
	for (int i(0); i < 8; i++)
	{
		for (int j(0); j < 8; j++)
		{
			if (chessboard[i][j] &&
				chessboard[i][j]->get_is_white() != player_is_white)
			{
				Square square_enemi(7 - i, j);
				Square square_king(7 - k_i, k_j);
				if (allow_to_move(square_enemi, square_king))
				{
					cout << "--------------------------------------" << endl;
					cout << "you are on check, sry bro" << endl;
					cout << chessboard[i][j]->get_name() << "on pos " << i << "," << j;
					cout << " can eat your ";
					cout << chessboard[k_i][k_j]->get_name() << "on pos " << k_i << "," << k_j << endl;
					cout << "--------------------------------------" << endl;
					return true;
				}
			}
		}
	}
	return false;
}


/* Others Functions */

void Chessboard::drop_piece(Piece *_piece)
{
	size_t i = _piece->get_pos().get_coord()[0];
	size_t j = _piece->get_pos().get_coord()[1];
	this->chessboard[i][j] = _piece;
}

Piece *Chessboard::create_piece(Square pos)
{
	return this->chessboard[invert_posx(pos.get_coord()[0])][pos.get_coord()[1]];
}

/* besoin pour la classe Game */
Piece *Chessboard::piece_on_cb(size_t i, size_t j) const
{
	return this->chessboard[i][j];
}

bool Chessboard ::nothing_in_da_way_diagonally(Square o, Square d)
{
	ssize_t incre0, incre1;
	if (origin_inf_to_dest(o, d, 0))
		incre0 = 1;
	else
		incre0 = -1;
	if (origin_inf_to_dest(o, d, 1))
		incre1 = 1;
	else
		incre1 = -1;

	ssize_t j = o.get_coord()[1] + incre1;
	for (size_t i = o.get_coord()[0] + incre0; i != d.get_coord()[0]; i += incre0)
	{
		Square test_piece = Square(i, j);
		if (this->chessboard[invert_posx(i)][test_piece.get_coord()[1]] != nullptr)
			return false;
		j += incre1;
	}
	return true;
}

bool Chessboard::da_way_straight(Square o, Square d)
{
	ssize_t dir = give_dir_straight(o, d);
	ssize_t incre = give_incre_for_dir_straight(o, d, dir);
	ssize_t j = o.get_coord()[!dir];
	for (size_t i = o.get_coord()[dir] + incre; i != d.get_coord()[dir]; i += incre)
	{
		if (dir == 0 && this->chessboard[invert_posx(i)][j] != nullptr)
			return false;
		else if (dir == 1 && this->chessboard[invert_posx(j)][i] != nullptr)
			return false;
	}
	return true;
}

bool Chessboard::da_way_queen(Square o, Square d)
{
	if (d.get_coord()[1] == o.get_coord()[1] || d.get_coord()[0] == o.get_coord()[0])
		return da_way_straight(o, d);
	return nothing_in_da_way_diagonally(o, d);
}

/* Roque Functions */

/*
Si reussi, renvoie <true, position ou la tour doit aller>, sinon <false, position du roi en létat 
ou il a été déplacé.
*/
tuple<bool, Square> Chessboard::da_way_straight_roque(Square o, Square d)
{
	int cpt = 0;
	tuple<bool, Square> result_rock_pos(false, Square(-1, -1));
	ssize_t dir = 1;
	ssize_t incre = give_incre_for_dir_straight(o, d, dir);
	ssize_t j = o.get_coord()[!dir];
	Square from = Square(o.get_coord()[0], o.get_coord()[1]);

	int thedist = abs(int(d.get_coord()[dir] - o.get_coord()[dir]));

	size_t i;
	for (i = o.get_coord()[dir] + incre; i != d.get_coord()[dir]; i += incre)
	{
		Square to = Square(j, i);
		if (this->chessboard[j][i] != nullptr)
			cout << "cant cross through " << this->chessboard[j][i]->get_name() << "" << endl;
		else
		{
			from.set_coord(invert_posx(from.get_coord()[0]), 0);
			to.set_coord(invert_posx(to.get_coord()[0]), 0);
			deplacement(from, to, true);
			cpt++;
			if (cpt == 2)
			{
				int grandrockdist = 0;
				if (thedist == 4)
					grandrockdist = incre;
				move_piece(Square(invert_posx(j), i + incre + grandrockdist), Square(invert_posx(j), i - incre));
				get<0>(result_rock_pos) = true;
				return result_rock_pos;
			}
			cancel_deplacement(from, to, 0);
			from.set_coord(invert_posx(from.get_coord()[0]), 0);
		}
	}

	if (cpt != thedist)
		this->chessboard[o.get_coord()[0]][o.get_coord()[1]]->piece_unmooved();
	return result_rock_pos;
}

tuple<Piece *, Piece *> Chessboard::get_Rock_roque(bool player_color)
{
	Piece *king;
	tie(ignore, ignore, king) = get_king(player_color);
	tuple<Piece *, Piece *> near_far_king(nullptr, nullptr);
	for (int i = 0; i < 8; i++)
	{
		for (int j(0); j < 8; j++)
		{
			if (chessboard[i][j] &&
				chessboard[i][j]->get_is_white() == player_color)
			{
				if (chessboard[i][j]->get_is_rock())
				{
					if (condition_roque(king, chessboard[i][j], 3))
					{
						get<0>(near_far_king) = chessboard[i][j];
					}
					else if (condition_roque(king, chessboard[i][j], 4))
					{
						get<1>(near_far_king) = chessboard[i][j];
					}
				}
			}
		}
	}
	return near_far_king;
}

bool condition_roque(Piece *king, Piece *rock, int dist)
{
	bool distance = (dist_column(king->get_pos(), rock->get_pos()) == dist);
	bool static_king = !king->get_already_moved();
	bool static_rock = !rock->get_already_moved();
	return (distance && static_king && static_rock);
}

bool Chessboard::moove_rock_roque(Square o, Square d)
{
	bool result = false;
	Square pos(-1, -1);
	tie(result, pos) = da_way_straight_roque(o, d);
	return result;
}

/* En Passant Functions */

void Chessboard::reinitialized_en_passant(bool color)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j(0); j < 8; j++)
		{
			if (piece_not_empty_and_color(chessboard[i][j], color))
			{
				if (chessboard[i][j]->get_is_pawn())
				{
					chessboard[i][j]->unen_passant();
				}
			}
		}
	}
}

bool Chessboard::proceed_en_passant(Square origin, Square dest)
{
	if (!check_if_pawn_diagonal_empty(origin, dest))
		return false;
	if (get_neighbour_pawn_enemy(origin, dest) == nullptr)
		return false;
	bool deplacement_ok = deplacement(origin, dest, true);
	if (deplacement_ok)
		remove_neighbour(dest);
	return true;
}

bool Chessboard::check_if_pawn_diagonal_empty(Square origin, Square dest)
{
	Piece *piece_on_mvnt = create_piece(origin);
	return (diagonal_move_pawn(origin, dest, piece_on_mvnt->get_color()) &&
			this->chessboard[invert_posx(dest.get_coord()[0])][dest.get_coord()[1]] == NULL &&
			this->chessboard[invert_posx(origin.get_coord()[0])][origin.get_coord()[1]]->get_is_pawn());
}

Piece *Chessboard::get_neighbour_pawn_enemy(Square origin, Square dest)
{
	int thedir = create_piece(origin)->dir();
	Piece *neighbour = this->chessboard[invert_posx(dest.get_coord()[0]) + thedir][dest.get_coord()[1]];
	if(neighbour == nullptr)
		return nullptr;
	Piece *current_piece = create_piece(origin);
	if (condition_en_passant(neighbour, current_piece))
		return neighbour;
	return nullptr;
}

bool Chessboard::condition_en_passant(Piece *neighbour, Piece *current_piece)
{
	bool color = neighbour->get_is_white() != current_piece->get_is_white();
	return (neighbour != nullptr && neighbour->get_is_pawn() && color && neighbour->get_passant());
}

void Chessboard::remove_neighbour(Square dest)
{
	int thedir = create_piece(dest)->dir();
	this->chessboard[invert_posx(dest.get_coord()[0]) + thedir][dest.get_coord()[1]] = nullptr;
}

/* Fonction annexe */

bool Chessboard::piece_not_empty_and_color(Piece *piece, bool color)
{
	return (piece && piece->get_is_white() == color) ? true : false;
}

ssize_t origin_inf_to_dest(Square o, Square d, int num_coord)
{
	return min(o.get_coord()[num_coord], d.get_coord()[num_coord]);
}

int give_dir_straight(Square o, Square d)
{
	return (d.get_coord()[1] == o.get_coord()[1]) ? 0 : 1;
}

int give_incre_for_dir_straight(Square o, Square d, int dir)
{
	return (origin_inf_to_dest(o, d, dir)) ? 1 : -1;
}
