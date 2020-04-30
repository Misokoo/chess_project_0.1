#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/piece.h"
#include "../include/piece_annexe.h"
#include <cstdlib>
using namespace std;

/* Legal Movment */

bool Pawn::movment_legal(Square orig, Square dest)
{
  bool reponse(false);
  if (one_step_white(orig, dest))
    reponse = true;
  else if (one_step_black(orig, dest))
    reponse = true;
  else if (two_step_white(orig, dest))
    reponse = true;
  else if (two_step_black(orig, dest))
    reponse = true;
  return reponse;
}


bool Rock::movment_legal(Square orig, Square dest)
{
  return straight_move(orig, dest);
}


bool Bishops::movment_legal(const Square orig, Square dest)
{
  return diagonal_move(orig, dest);
}

bool Queen::movment_legal(const Square orig, Square dest)
{
  return (diagonal_move(orig, dest) || straight_move(orig, dest));
}

bool Knights::movment_legal(const Square o, Square d) 
{
  return knights_move_legit(o, d);
}

bool King::movment_legal(const Square o, Square d)
{
  return (king_move_straight(o, d) || king_move_diagonal(o, d) == 1);
}


/* Function for move authorization */

bool straight_move(Square o, Square d)
{
  bool result(false);
  if (same_row(o, d) && different_column(o, d))
    result = true;
  else if (same_colomn(o, d) && different_row(o, d))
    result = true;
  return result;
}

bool diagonal_move(Square o, Square d)
{
  return (dist_row(o, d) == dist_column(o, d));
}

bool diagonal_move_pawn(Square o, Square d, string color)
{
  bool result(false);
  if (diagonal_move(o, d) && color.compare("Black") == 0 &&
      (int)(d.get_coord()[0] - o.get_coord()[0]) == -1)
        result = true;
  else if (diagonal_move(o, d) && color.compare("White") == 0 &&
           (int)(d.get_coord()[0] - o.get_coord()[0]) == 1)
    result = true;
  return result;
}


/* Function for Specific move authorization */
bool Pawn::one_step_white(Square orig, Square dest) 
{
  bool color = this->get_color().compare("White") == 0;
  bool one_step = (dest.get_coord()[0] - orig.get_coord()[0]) == 1;
  bool no_horizontal_step = !(dest.get_coord()[1] - orig.get_coord()[1]);
  return color && one_step && no_horizontal_step;
}
bool Pawn::one_step_black(Square orig, Square dest)
{
  bool color = this->get_color().compare("Black") == 0;
  bool one_step = (int)(dest.get_coord()[0] - orig.get_coord()[0]) == -1;
  bool no_horizontal_step = !(dest.get_coord()[1] - orig.get_coord()[1]);
  return color && one_step && no_horizontal_step;
}
bool Pawn::two_step_white(Square orig, Square dest)
{
  bool color = this->get_color().compare("White") == 0;
  bool two_step = (dest.get_coord()[0] - orig.get_coord()[0]) == 2 ;
  bool no_horizontal_step = !(dest.get_coord()[1] - orig.get_coord()[1]);
  bool not_mooved = !this->get_already_moved();
  if(color && two_step && no_horizontal_step && not_mooved)
    this->can_be_passant();
  return color && two_step && no_horizontal_step && not_mooved;
}
bool Pawn::two_step_black(Square orig, Square dest)
{
  bool color = this->get_color().compare("Black") == 0;
  bool two_step = ((int)(dest.get_coord()[0] - orig.get_coord()[0]) == -2) ;
  bool no_horizontal_step = !(dest.get_coord()[1] - orig.get_coord()[1]);
  bool not_mooved = !this->get_already_moved();
  if (color && two_step && no_horizontal_step && not_mooved)
    this->can_be_passant();
  return color && two_step && no_horizontal_step && not_mooved;
}

bool Knights::knights_move_legit(Square o, Square d){
return ((dist_row(o,d) + dist_column(o,d)) == 3 && dist_row(o,d) < 3 && dist_column(o,d) < 3);
}

bool king_move_straight(Square o, Square d)
{
  bool move_row = (dist_value_row(o, d, 1) && dist_value_column(o, d, 0));
  bool move_column = (dist_value_row(o, d, 0) && dist_value_column(o, d, 1));
  return (move_row || move_column);
}

bool king_move_diagonal(Square o, Square d)
{
  return (dist_value_row(o, d, 1) && dist_value_column(o, d, 1));
}


/* Accesseurs */

void Piece::print() const
{
  cout << this->name;
}

string Piece::get_name() const
{
  return this->name;
}

string Piece::get_color() const
{
  return this->color;
}

bool Piece::get_is_white() const
{
  return this->is_white;
}

bool Piece::get_already_moved() const
{
  return this->already_moved;
}

bool Piece::get_is_pawn() const
{
  return this->is_pawn;
}

bool Piece::get_is_rock() const
{
  return this->is_rock;
}

bool Piece::get_is_bishop() const
{
  return this->is_bishop;
}

bool Piece::get_is_queen() const
{
  return this->is_queen;
}

bool Piece::get_is_king() const
{
  return this->is_king;
}

Square Piece::get_pos() const
{
  return this->pos;
}

void Piece::set_pos(Square &new_pos)
{
  this->pos.set_square(new_pos);
}


bool Piece::get_passant(){
  return this->pass_flag;
}


/* Annexes Functions */

void Piece::piece_mooved()
{
  this->already_moved = true;
}

void Piece::piece_unmooved()
{
  this->already_moved = false;
}

bool dist_value_row(Square o, Square d, int value)
{
  return (dist_row(o, d) == value) ? true : false;
}
bool dist_value_column(Square o, Square d, int value)
{
  return (dist_column(o, d) == value) ? true : false;
}

int dist_row(Square o, Square d)
{
  return abs((int)(d.get_coord()[0] - o.get_coord()[0]));
}

int dist_column(Square o, Square d)
{
  return abs((int)(d.get_coord()[1] - o.get_coord()[1]));
}

bool same_row(Square o, Square d)
{
  return (dist_row(o, d) == 0) ? true : false;
}

bool same_colomn(Square o, Square d)
{
  return (dist_column(o, d) == 0) ? true : false;
}

bool different_column(Square o, Square d)
{
  return (dist_column(o, d) != 0) ? true : false;
}
bool different_row(Square o, Square d)
{
  return (dist_row(o, d) != 0) ? true : false;
}

void Piece::unen_passant(){
  this->pass_flag = false;
}

void Piece::can_be_passant(){
  this->pass_flag = true;
}

int Piece::dir(){
  return (this->color.compare("Black") == 0) ? -1 : 1;
}
