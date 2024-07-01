#ifndef __USERPIECE_H__
#define __USERPIECE_H__

#include "piece.h"

bool isRoyal(const Piece *piece);

// The following 2 classes are given as example
using Knight = OmniLeaper<'N', 2, 1>;

using Rook = OmniRider<'R', 1, 0>;

// TODO

// template<char N, int F, int R, int RANGE = MAX_RANGE>

// Bishop
using Bishop = Compound<'B',
                        Compound<'B', Rider<'B', -1, -1, MAX_RANGE>, Rider<'B', 1, -1, MAX_RANGE>>, // north west, north east
                        Compound<'B', Rider<'B', -1, 1, MAX_RANGE>, Rider<'B', 1, 1, MAX_RANGE>>    // south west, south east
                        >;

// Queen
using Queen = Compound<'Q', Bishop, Rook>;

// King
// template<char N, int F, int R>
// 8 direction
using King = Compound<'K',
                      Compound<'K',
                               Compound<'K', Leaper<'K', 0, 1>, Leaper<'K', 0, -1>>,  // north, south
                               Compound<'K', Leaper<'K', -1, 0>, Leaper<'K', 1, 0>>>, // west, east
                      Compound<'K',
                               Compound<'K', Leaper<'K', -1, 1>, Leaper<'K', 1, 1>>,   // north west, north east
                               Compound<'K', Leaper<'K', -1, -1>, Leaper<'K', 1, -1>>> // south west, south east
                      >;

// TODO

// only to decide should go foward to one more step
template <char N, int F, int R>
class omniPawn : public NamedPiece<N>
{
private:
public:
        // constructor
        omniPawn(Color color) : NamedPiece<N>(color) {}

        // set need copy constructor
        omniPawn(const omniPawn &pawn) = default;

        // clone
        virtual Piece *clone() const override
        {
                return new omniPawn(*this);
        }
        // no need?

        // override the getMoves part
        virtual BooleanMap getMoves(const Board &board) const override
        {
                // new map
                BooleanMap newMap; // defualt all false

                // set pos
                Position dest = this->Piece::getPosition();

                // find vector
                Vector newVector;
                if (this->Piece::getColor() == WHITE)
                {
                        // cell[R][F]
                        // move F square to right, R square up
                        newVector.file = F;  // move right , next column
                        newVector.rank = R; // move up , last row
                }
                else // BLACK color
                {
                        // cell[R][F]
                        // move F square to left, R square down
                        newVector.file = -F; // move left , last column
                        newVector.rank = -R;  // move down , next row
                }

                // update destination
                dest = newVector + dest;

                // boolean to check is on starting pos now
                bool StartPos = false;

                // if piece is in start pos -> true
                if (this->Piece::position.rank == 1 && this->Piece::color == WHITE)
                {
                        StartPos = true;
                }
                else if (this->Piece::position.rank == 6 && this->Piece::color == BLACK)
                {
                        StartPos = true;
                }

                // check in start pos
                if (StartPos == true)
                {
                        // in start pos -> check dest have piece
                        if (board.piece(dest) != nullptr)
                        {
                                // dest have piece
                                // no Need check color, cuz cannot capture -> cannot move there
                                return newMap;
                        }
                        else // no piece
                        {
                                // can move
                                newMap.cell(dest) = true;

                                // return
                                return newMap;
                        }
                }
                else
                {
                        // not in start pos
                        // return all false
                        return newMap;
                }

                // return
                return newMap;
        }
};

//!testing here =============

// use if else for using?

using Pawn = Compound<'P',
                      Divergent<'P',
                                Leaper<'P', 0, 1>,                                     // move up
                                Compound<'P', Leaper<'P', 1, 1>, Leaper<'P', -1, 1>>>, // capture up left, up right
                      omniPawn<'P', 0, 2>>;


//using Pawn = Compound <'P',Leaper<'P',0,1>, Leaper<'P',0,3>>; //!test compound----------------------------
//using Pawn = Leaper<'P',0, 3>; //!test Leaper
//using Pawn = Rider<'P',0,1>; //!test rider


#endif // __USERPIECE_H__