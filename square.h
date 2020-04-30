#ifndef SQUARE_HEADER
#define SQUARE_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Square
{
protected:
  string coord_name;
  size_t coord[2];

public:
  Square(string coord)
  {
    char lettres[] = "abcdefgh";
    int num[] = {1, 2, 3, 4, 5, 6, 7, 8};
    char letter = coord.substr(0, 1)[0];
    int nb = atoi(coord.substr(1, 1).c_str());
    for (size_t i = 0; i < 8; i++)
    {
      if (letter == lettres[i])
      {
        this->coord[1] = i;
      }
      if (nb == num[i])
      {
        this->coord[0] = i;
      }
    }
    this->coord_name = coord;
  }

  Square(int _cordx, int _cordy)
  {
    this->coord[0] = _cordx;
    this->coord[1] = _cordy;
    string lettres = "abcdefgh";
    this->coord_name = lettres[_cordy];
    this->coord_name += std::to_string(_cordx + 1);
  }

  /** @brief getter, get the icon of the piece
	  * @result string, the icon
  */
  string to_string() const;

  /** @brief getter, coord with (x,y) format
	  * @result string, the icon
  */
  string coord_to_string() const;

  /** @brief getter, coord with a tab of 2 cases
	  * @result size_t*
  */
  const size_t *get_coord() const;

  /** @brief setter, set the new cooord with the param
   *  @param new_square
	  * @result size_t*
  */
  void set_square(Square new_square);

  /** @brief setter, set the coord idx with the value in param
   * idx 0 is for row, 1 for column
    * @param value value of new coord
    * @param idx the index
  */
  void set_coord(size_t value, size_t idx);
};

/** @brief inverse index of row
 * display of number of lines in chessboard and in the matrix 
 * are complementaire, so we have to change it
    * @param cordx index of the coord in the matrix
    * @result value of index in the chessboard
  */
size_t invert_posx(size_t _cordx);

/** @brief check the format of the player request
    * @result true if in the chessboard, false otherwise
  */
bool saisie_correcte(string const &cmd);

#endif
