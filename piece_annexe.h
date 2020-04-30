#ifndef ANNEXE_FCT
#define ANNEXE_FCT 1
/*piece */

/** @brief indicate if the distance between row from o and
 * d is equal t value
* @param o origin of the moove
* @param d destination of the moove
* @param value the value we test
* @result bolean, true if the value is accurate
*/
bool dist_value_row(Square o, Square d, int value);


/** @brief indicate if the distance between column from o and
 * d is equal t value
* @param o origin of the moove
* @param d destination of the moove
* @param value the value we test
* @result bolean, true if the value is accurate
*/
bool dist_value_column(Square o, Square d, int value);


/** @brief indicate the distance between row from o and d 
* @param o origin of the moove
* @param d destination of the moove
* @param value the value we test
* @result integer, the value
*/
int dist_row(Square o, Square d);

/** @brief indicate the distance between column from o and d 
* @param o origin of the moove
* @param d destination of the moove
* @param value the value we test
* @result integer, the value
*/
int dist_column(Square o, Square d);


/** @brief indicate the Square o and d are in the same row
* @param o origin of the moove
* @param d destination of the moov
* @result boolean, true if same rows, false else
*/
bool same_row(Square o, Square d);

/** @brief indicate the Square o and d are in the same column
* @param o origin of the moove
* @param d destination of the moov
* @result boolean, true if same columns, false else
*/
bool same_colomn(Square o, Square d);

/** @brief indicate the Square o and d are in diffent columns
* @param o origin of the moove
* @param d destination of the moov
* @result boolean, true if different columns, false else
*/
bool different_column(Square o, Square d);

/** @brief indicate the Square o and d are in diffent row
* @param o origin of the moove
* @param d destination of the moove
* @result boolean, true if different rows, false else
*/
bool different_row(Square o, Square d);

/** @brief indicate if the moove from o to d is diagonal
 * check if the distance between row and colum are egal
 * if it is the case then the moove is diagonal
* @param o origin of the moove
* @param d destination of the moove
* @result boolean, true if diagonal moove, false else
*/
bool diagonal_move(Square o, Square d);


/** @brief indicate if the moove straight from the king is legal
 * check if the the king moove from only 1 unit of distance
 * in raw/colum and 0 in colum/raw.
* @param o origin of the moove
* @param d destination of the moove
* @result boolean, true if king moove is legal, false else
*/
bool king_move_straight(Square o, Square d);

/** @brief indicate if the moove diagonal from the king is legal
 * check if the the king moove from only 1 unit of distance
 * in raw and column
* @param o origin of the moove
* @param d destination of the moove
* @result boolean, true if king moove is legal, false else
*/
bool king_move_diagonal(Square o, Square d);

/*chessboard */

/** @brief indicate if origin < dest
 * allow to know how to moove in the matrix in chessboard
* @param o origin of the moove
* @param d destination of the moove
* @param num_coord 1 or 0, for column or row
* @result integer, 1 if true, false else
*/
ssize_t origin_inf_to_dest(Square o, Square d, int num_coord);

/** @brief give the direction to moove in a straight way
 * if Square on the same column the piece moove along the row
 * else along the column
* @param o origin of the moove
* @param d destination of the moove
* @result integer, 0 if same column, 1 else
*/
int give_dir_straight(Square o, Square d);

/** @brief give the incrementor to know teh way of the direction
* @param o origin of the moove
* @param d destination of the moove
* @param dir teh direction of the moove
* @result integer, 1 or -1 
*/
int give_incre_for_dir_straight(Square o, Square d, int dir);

/** @brief Check condition for roque moove
* Check if the distance between column is right
* check if king an the rock Are statics
* @param king the king that will moove
* @param rock the rock that will moove
* @param dist distance between rock and king
* @result boolean, true if previous conditions respected, false else
*/
bool condition_roque(Piece *king, Piece *rock, int dist);

/** @brief give the way of the direction to moove
* @param o origin of the moove
* @param d destination of the moove
* @param num_coord the direction 0/1 (row/column)
* @result integer, 1 or -1 
*/
ssize_t origin_inf_to_dest(Square o, Square d, int num_coord);
#endif