#ifndef CHESSBOARD_HEADER
#define CHESSBOARD_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/piece.h"

using namespace std;

class Chessboard
{
private:
    Piece *piecesB[8];
    Piece *piecesW[8];
    Pawn *pawnB[8];
    Pawn *pawnW[8];
    Piece *chessboard[8][8];

public:
    /**
     * @brief check if the moove is allow
     *
     * This function estimate if the piece on the pos origin is 
     * allow to move to the pos dest by calling allow 
     * fonctions depending on the type of the piece.
     * 
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @result boolean that indicate if the moove is allowed
     */
    bool allow_to_move(Square origin, Square dest);

    /**
     * @brief check if the pawn can moove
     * This function check if the pawn moove is legal
     * and if the pawn can eat an enemy piece by calling 
     * others functions.
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @param piece_on_mvnt the piece that move
     * @result boolean that indicate if the moove is allowed
     */
    bool allow_pawn(Square origin, Square dest, Piece *piece_on_mvnt);

    /**
     * @brief check if the rock can moove
     * This function check if the moove is allow and
     * if it is a moove straigth by 
     * calling da_way_straiht and movment legal functions.
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @param piece_on_mvnt the piece that move
     * @result boolean that indicate if the moove is allowed
     */
    bool allow_rock(Square origin, Square dest, Piece *piece_on_mvnt);

    /**
     * @brief check if the bishop can moove
     * This function check if the moove is allow and
     * if it is a moove digonal by calling 
     * nothing_in_da_way_diagonally and movment_legal functions.
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @param piece_on_mvnt the piece that move
     * @result boolean that indicate if the moove is allowed
     */
    bool allow_bishop(Square origin, Square dest, Piece *piece_on_mvnt);

    /**
     * @brief check if the da_way_queen can moove
     * This function check if the moove is allow and
     * if it is a diagonal/straight moove by calling 
     * da_way_queen and movment_legal functions.
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @param piece_on_mvnt the piece that move
     * @result boolean that indicate if the moove is allowed
     */
    bool allow_queen(Square origin, Square dest, Piece *piece_on_mvnt);

    /**
     * @brief deplace (because allowed) the piece from origin to dest
     * This function moove the piece if ok_moove is true
     * and the moove is allow.
     * it calls move_piece() that moove the piece,
     * if after checking there is no check with
     * check_check function, it validate the moove
     * and return true.
     * else it cancel the moove with cancel_deplacement
     * function.
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @param ok_moove boolen from allow_move function
     * @result boolean that indicate if the deplacement is done
     */
    bool deplacement(Square origin, Square dest, bool ok_moove);

    /**
     * @brief cancel the deplacement from origin to dest
     * This function cancel the moove ofthe piece
     * from origin to dest
     * if was_unmooved is true, it call the method
     * piece_unmooved() from Class piece
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @param was_unmooved boolean true if the piece as unmooved
     * @result no result
     */
    void cancel_deplacement(Square origin, Square dest, bool was_unmooved);

    /**
     * @brief moove freely the piece from origin to dest
     * This function move the piece from origin to dest
     * @param origin origin of the piece
     * @param dest destination of the move of the piece
     * @result tuple of bolean (piece_already_mooved_before, is_white)
     */
    tuple<bool, bool> move_piece(Square origin, Square dest);

    /**
     * @brief indicate if a piece is between pos o and d
     * This function check if a piece is between
     * pos o and d  for a diagonal moove
     * @param o origin of the piece
     * @param d destination of the move of the piece
     * @result boolean, true if no piece between o and d
     */

    bool nothing_in_da_way_diagonally(Square o, Square d);
    /**
     * @brief indicate if a moove from o to d is straight and free
     * This function check if a piece is between
     * pos o and d  for a straight moove.
     * @param o origin of the piece
     * @param d destination of the move of the piece
     * @result boolean, true if no piece between o and d 
     * and the moove is straight
     */
    bool da_way_straight(Square o, Square d);

    /**
     * @brief indicate if a moove from o to d is in a way the queen can moove.
     * This function check if the moove is in a diagonal
     * or straight moove without piece between o and d
     * by calling straight moove and diagonnaly moove
     * functions
     * @param o origin of the piece
     * @param d destination of the move of the piece
     * @result boolean, true if the moove is diagonal or straight
     */
    bool da_way_queen(Square o, Square d);

    /**
     * @brief indicate if the current configuration is check
     * This function collect the piece king with get_king() function
     * and call enemy_can_check() function.
     * @param is_white indicate if the player playing is white (or black)
     * @result boolean, true if configuration of a check
     */
    bool check_check(bool is_white);

    /**
     * @brief indicate if the enemy check your king
     * This function browse the enemy piece and 
     * check if its moove are allow to eat the king of
     * the player currently playing
     * @param player_is_white indicate if the player playing is white (or black)
     * @param k_i pos x of the king in the table of pieces
     * @param k_j pos y of the king in the table of pieces
     * @result boolean, true if the enemy can check the current player
     */
    bool enemy_can_check(bool player_is_white, int k_i, int k_j);

    /**
     * @brief collect the piece king and its pos of the current player
     * This function browse the table of piece and collect the king and its pos.
     * @param player_color indicate if the player playing is white(1) or black(0)
     * @result tuple, king and its pos of the current player
     */
    tuple<int, int, Piece *> get_king(bool player_color);

    /**
     * @brief collect the 2 rock for the roque moove
     * This function browse the table of piece and collect rocks
     * of the current player.
     * @param player_color indicate if the player playing is white(1) or black(0)
     * @result tuple, boths rocks of the current player
     */
    tuple<Piece *, Piece *> get_Rock_roque(bool player_color);

    /**
     * @brief check if roque is possible and proceed if it is
     * get the rocks with get_rocks functions,
     * check the condition of the with condition_roque() function
     * then check if there are pieces between king and the rock 
     * for roque, if it okay, moove the king and the rock
     * @param o origin of the king
     * @param d destination of the king
     * @result tuple, if succed <true, position where the rock has to gor>, else <false, 
     * pos of the king in the state where it has been mooved>
     */
    tuple<bool, Square> da_way_straight_roque(Square o, Square d);

    /**
     * @brief call da_way_straight_roque and return if the
     * roque was done
     * @param o origin of the king
     * @param d destination of the king
     * @result boolean, indicating if the roque was done.
     */
    bool moove_rock_roque(Square o, Square d);

    /**
     * @brief reinitialize the flag en_passant
     * for each turn for pawn, this flag is True
     * if a pawn just moove for the first time
     * and of 2cases
     * @param color color of the player to reinitialize pawns
     * @result nothing
     */
    void reinitialized_en_passant(bool color);

    /**
     * @brief verify if the piece on movment is a pawn
     * if the piece in diagonal is empty and if
     * the moove to proceed is diagonal
     * @param origin origin of the pawn
     * @param dest destination of the pawn
     * @result return true if the previous conditions are apply
     */
    bool check_if_pawn_diagonal_empty(Square origin, Square dest);

    /**
     * @brief verify if there is a neighbour
     * if it is a pawn, if its color is different
     * from the current player's and if configuration
     * of en passant are applies
     * @param neighbour the neighbour pawn
     * @param current_piece the piece to moove
     * @result return true if the previous conditions are apply
     */
    bool condition_en_passant(Piece *neighbour, Piece *current_piece);

    /** @brief general function to proceed en passant
     * calls en passant's related functions and moove the pieces
     * @param origin origin of the pawn to moove
     * @param dest destination of the pawn to moove
     * @result return true if the end passant moove was done
     */
    bool proceed_en_passant(Square origin, Square dest);

    /** @brief get the pawn neighbour of the pawn
     * next to origin
     * @param origin origin of the pawn to moove
     * @param dest destination of the pawn to moove
     * @result the pawn neighbour 
     */
    Piece *get_neighbour_pawn_enemy(Square origin, Square dest);

    /** @brief delete the neighbour from the table of piece*
     * @param dest destination of the pawn to moove in the
     * en passant moove
     * @result nothing
     */
    void remove_neighbour(Square dest);

    /** @brief drop the piece in the table representing the chessboard
     * @param _piece the peice to drop
     * @result nothing
     */
    void drop_piece(Piece *_piece);

    /** @brief get the piece of pos in the chessboard
     * @param pos pos of the piece to get
     * @result the piece* of the chessboard
     */
    Piece *create_piece(Square pos);

    /** @brief print the chessboard
     * @result nothing
     */
    void print() const;

    /** @brief get the piece of coord i and j
     * @param i coord x
     * @param j coord y
     * @result the piece* of the chessboard
     */
    Piece *piece_on_cb(size_t i, size_t j) const; // pour y acceder à partir de la classe Game

    /** @brief indicate if the piece* is not null and of the same color of color param
     * @param piece the piece to test
     * @param color color of the piece, white =1, black is 0
     * @result boolean if the piece is not null and of type color
     */
    bool piece_not_empty_and_color(Piece *piece, bool color);

    /** @brief function to allow pawn to moove when it eat 
     * a piece
     * @param origin origin of the pawn to moove
     * @param dest destination of the pawn to moove
     * @param piece_on_mvnt the pawn
     * @result true if the pawn can moove
     */
    bool pawn_eat_smth(Square origin, Square dest, Piece *piece_on_mvnt);

    Chessboard()
    {

        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                this->chessboard[i][j] = nullptr;
            }
        }
        this->piecesW[0] = new Rock("Black", " \u2656 ", Square(0, 0));
        this->piecesW[1] = new Knights("Black", " \u2658 ", Square(0, 1));
        this->piecesW[2] = new Bishops("Black", " \u2657 ", Square(0, 2));
        this->piecesW[3] = new Queen("Black", " \u2655 ", Square(0, 3));
        this->piecesW[4] = new King("Black", " \u2654 ", Square(0, 4));
        this->piecesW[5] = new Bishops("Black", " \u2657 ", Square(0, 5));
        this->piecesW[6] = new Knights("Black", " \u2658 ", Square(0, 6));
        this->piecesW[7] = new Rock("Black", " \u2656 ", Square(0, 7));
        this->piecesB[0] = new Rock("White", " \u265C ", Square(7, 0));
        this->piecesB[1] = new Knights("White", " \u265E ", Square(7, 1));
        this->piecesB[2] = new Bishops("White", " \u265D ", Square(7, 2));
        this->piecesB[3] = new Queen("White", " \u265B ", Square(7, 3));
        this->piecesB[4] = new King("White", " \u265A ", Square(7, 4));
        this->piecesB[5] = new Bishops("White", " \u265D ", Square(7, 5));
        this->piecesB[6] = new Knights("White", " \u265E ", Square(7, 6));
        this->piecesB[7] = new Rock("White", " \u265C ", Square(7, 7));

        // allocation of panws
        for (unsigned char i(0); i < 8; i++)
        {
            this->pawnW[i] = new Pawn("Black", " \u2659 ", Square(1, i));
            this->pawnB[i] = new Pawn("White", " \u265F ", Square(6, i));
        }

        for (size_t i = 0; i < 8; i++)
        {
            drop_piece(this->piecesW[i]);
            drop_piece(this->piecesB[i]);
            drop_piece(this->pawnW[i]);
            drop_piece(this->pawnB[i]);
        }
    }
};
#endif
