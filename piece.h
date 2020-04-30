#ifndef PIECE_HEADER
#define PIECE_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/square.h"


using namespace std;
bool diagonal_move(Square o, Square d);
bool diagonal_move_pawn(Square o, Square d, string color);

class Piece
{
protected:
  string name;
  string color;
  bool is_white;
  bool already_moved;
  Square pos;
  bool is_pawn;
  bool is_rock;
  bool is_bishop;
  bool is_queen;
  bool is_king;
  bool pass_flag;

public:
  /** @brief virtual function, decide if the movment is legal
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true if movment is legal, false otherwise.
  */
  virtual bool movment_legal(Square orig, Square dest) = 0;

  /** @brief set the flag en_passant to true
  */
  virtual void can_be_passant();

  /** @brief set the flash en_passant to false
  */
  virtual void unen_passant();
  Piece(string c, string n, Square po, bool pn) : name(n), color(c), pos(po)
  {
    this->is_white = false;
    this->already_moved = false;
    this->is_rock = false;
    this->is_bishop = false;
    this->is_rock = false;
    this->is_king = false;
    this->is_pawn = pn;
    string blanc = "White";
    if (this->color.compare("White") == 0)
      this->is_white = true;

    if (n.compare(" \u265C ") == 0 || n.compare(" \u2656 ") == 0)
      this->is_rock = true;

    if (n.compare(" \u2657 ") == 0 || n.compare(" \u265D ") == 0)
      this->is_bishop = true;

    if (n.compare(" \u2655 ") == 0 || n.compare(" \u265B ") == 0)
      this->is_queen = true;

    if (n.compare(" \u265A ") == 0 || n.compare(" \u2654 ") == 0)
      this->is_king = true;
  }

  Piece(string _color, string n, Square po) : name(n), color(_color), pos(po)
  {
    this->is_white = false;
    this->already_moved = false;
    string blanc = "White";
    if (this->color.compare("White") == 0)
    {
      this->is_white = true;
    }
  }

  /** @brief getter, give the icon of the piece
	  * @result string, code for the icone.
  */
  string get_name() const;

  /** @brief getter, give the color name of the piece
	  * @result string, color of the piece.
  */
  string get_color() const;

  /** @brief getter, give the Square of the piece
	  * @result Square Square of the icone.
  */
  Square get_pos() const;

  /** @brief getter, give the color of the piece
	  * @result boolean, true if the piece is white, 0 if black
  */
  bool get_is_white() const;

  /** @brief getter, precise if the piece already mooved 
	  * @result boolean, true if already moved, false otherwise
  */
  bool get_already_moved() const;

  /** @brief getter, precise if the piece is a pawn
	  * @result boolean, true if pawn, false otherwise
  */
  bool get_is_pawn() const;

  /** @brief getter, precise if the piece is a rock
	  * @result boolean, true if rock, false otherwise
  */
  bool get_is_rock() const;

  /** @brief getter, precise if the piece is a bishop
	  * @result boolean, true if bishop, false otherwise
  */
  bool get_is_bishop() const;

  /** @brief getter, precise if the piece is a queen
	  * @result boolean, true if queen, false otherwise
  */
  bool get_is_queen() const;

  /** @brief getter, precise if the piece is a king
	  * @result boolean, true if king, false otherwise
  */
  bool get_is_king() const;

  /** @brief set the flag already_moove to true
  */
  void piece_mooved();

  /** @brief set the flag already_moove to false
  */
  void piece_unmooved();

  /** @brief display the icon of the piece to cout
  */
  void print() const;

  /** @brief set the pos with new_pos param
     * @param new_pos teh new pos of the piece
  */
  void set_pos(Square &new_pos);

  /** @brief give the way of the direction
	  * @result int, -1 if black, 1 if white
  */
  int dir();

  /** @brief getter, precise the en passant flag
	  * @result boolean, en passant flag
  */
  bool get_passant();
};

class Pawn : public Piece
{
public:
  Pawn(string _color, string n, Square po) : Piece(_color, n, po, true)
  {
    pass_flag = false;
  }
  /** @brief decide if the rock movment is legal
   * call one_step_white(), one_step_black() 
   * two_step_white() , two_step_black() 
   * functions
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true if pawn movment is legal, false otherwise.
  */
  bool movment_legal(Square orig, Square dest);
  bool one_step_white(Square orig, Square dest);
  bool one_step_black(Square orig, Square dest);
  bool two_step_white(Square orig, Square dest);
  bool two_step_black(Square orig, Square dest);
};

class Rock : public Piece
{
public:
  Rock(string _color, string n, Square _pos) : Piece(_color, n, _pos, false) {}
  /** @brief decide if the rock movment is legal
   * call straight_move() function
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true if rock movment is legal, false otherwise.
  */
  bool movment_legal(Square orig, Square dest);
};

class Bishops : public Piece
{
public:
  Bishops(string _color, string n, Square _pos) : Piece(_color, n, _pos, false) {}
  /** @brief decide if the bishop movment is legal
   * call diagonal_move() function
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true if bishop movment is legal, false otherwise.
  */
  bool movment_legal(const Square orig, Square dest);
};

class Knights : public Piece
{
public:
  Knights(string _color, string n, Square _pos) : Piece(_color, n, _pos, false) {}

  /** @brief decide if the bishop movment is legal
   * check if abs value of depalcement is egal to 3 and
   * each movment in one direction < 3
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true if bishop movment is legit, false otherwise.
  */
  bool knights_move_legit(Square o, Square d);

  /** @brief decide if the bishop movment is legal
   * call knights_move_legit() function
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true if bishop movment is legal, false otherwise.
  */
  bool movment_legal(const Square orig, Square dest);
};

class Queen : public Piece
{
public:
  Queen(string _color, string n, Square _pos) : Piece(_color, n, _pos, false) {}

  /** @brief decide if queen movment is legal
   * call diagonal_move() and straight_move() functions
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true queen movment is legal, false otherwise.
  */
  bool movment_legal(const Square orig, Square dest);
};

class King : public Piece
{
public:
  King(string _color, string n, Square _pos) : Piece(_color, n, _pos, false) {}

  /** @brief decide if the bishop movment is legal
   * call king_move_straight() and king_move_diagonal() functions
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true king movment is legal, false otherwise.
  */
  bool movment_legal(const Square orig, Square dest);
};

int dist_row(Square o, Square d);
int dist_column(Square o, Square d);
bool same_row(Square o, Square d);
bool same_colomn(Square o, Square d);
bool different_column(Square o, Square d);
bool different_row(Square o, Square d);
bool diagonal_move(Square o, Square d);

/** @brief indicate if the movment is a diagone move from a pawn
 * use diagonal_move() function and the color 
 * with the way of directions
    * @param o origin of the piece
    * @param d destination of the move of the piece
    * @param color name of the color
	  * @result bolean, true if diagonal move pawn, false otherwise.
  */
bool diagonal_move_pawn(Square o, Square d, string color);

/** @brief indicate if the move is straight
 * use same_row() and different_column()
 * or different_row() and same_column() functions
    * @param orig origin of the piece
    * @param dest destination of the move of the piece
	  * @result bolean, true movment straight, false otherwise.
  */
bool straight_move(Square o, Square d);
#endif
