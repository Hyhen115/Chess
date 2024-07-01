#include <iostream>
#include "board.h"
#include "piece.h"
using namespace std;

//copy constructor
Board::Board(const Board &board)
{
    // TODO
    // perform deep copy
    // cout << "Called COPY" << endl; //! test
    // cout << board.royalPieces[0]->getName() << endl;
    // cout << board.royalPieces[0]->getPosition() << endl;
    // cout << board.royalPieces[1]->getName() << endl;
    // cout << board.royalPieces[1]->getPosition() << endl;

    // pieces

    // use piece clone function
    // loop through the board
    for (int i = 0; i < NUM_RANKS; ++i)
    {
        for (int j = 0; j < NUM_FILES; ++j)
        {
            // check copy nullptr or copy piece
            if (board.pieces[i][j] == nullptr) // no piece
            {
                this->pieces[i][j] = nullptr; // set to nullptr
            }
            else
            {
                // copy piece using clone function
                this->pieces[i][j] = board.pieces[i][j]->clone(); // set piece
            }
        }
    }

    // isWhiteTurn
    this->isWhiteTurn = board.isWhiteTurn;

    // selectedPiece

    Position NewPos;

    if (board.selectedPiece != nullptr) // if selected piece is not nullptr
    {
        // set this data member point to the correspinding piece on the new board
        // int newRankPos = board.selectedPiece->getPosition().rank;
        // int newFilePos = board.selectedPiece->getPosition().file;

        NewPos = board.selectedPiece->getPosition();

        // update where the ptr should point
        this->selectedPiece = this->pieces[NewPos.rank][NewPos.file]; // selected piece ptr point to where the pieces board points to
    }
    else // board.selectedPiece is nullptr
    {
        this->selectedPiece = nullptr;
    }

    // moveMap
    for (int r = 0; r < NUM_RANKS; ++r)
    {
        for (int f = 0; f < NUM_FILES; ++f)
        {
            // copy board.movemap to this movemap
            this->moveMap.cell(static_cast<_FILE>(f), static_cast<_RANK>(r)) = board.moveMap.cell(static_cast<_FILE>(f), static_cast<_RANK>(r));
        }
    }

    Position newRoyalPos;

    // loop through both royalpieces
    for (int i = 0; i < 2; ++i) //!!!!!=========DUN KNOW WHY TF WILL ROYAL PIECE IS NULLPTR
    {
        // copy both royalpiece point to the thing
        if (board.royalPieces[i] != nullptr)
        {
            // copy the royal piece position
            newRoyalPos = board.royalPieces[i]->getPosition();

            // update the royal piece ptr point to that position of the board
            this->royalPieces[i] = this->pieces[newRoyalPos.rank][newRoyalPos.file];
        }
    }

    // std::cout << "end copying" << std::endl; //! test
};


// Board destructor

Board::~Board()
{
    // TODO
    // destructor

    // delete pieces
    // loop through all piexes in the 2D ptr array
    for (int i = 0; i < NUM_RANKS; ++i)
    {
        for (int j = 0; j < NUM_FILES; ++j)
        {
            // if not null -> delete
            if (this->pieces[i][j] != nullptr)
            {
                delete pieces[i][j];
            }
        }
    }

    //?no need delete [] pieces cuz not new

    // no need delete:
    // isWhiteTurn
    // selectedPiece
    selectedPiece = nullptr;
    // moveMap

    //! no need delete i think
    // ?royalPieces
    // for(int i = 0; i < 2; ++i)
    //    delete royalPieces[i];
}


void Board::move(const Position &destPos)
{
    // Safeguard against misusage of move()
    if (!selectedPiece)
    {
        cout << "ERROR: Piece not selected, cannot call move()" << endl;
        return;
    }

    // TODO
    //! sus

    // if destPos have a piece -> delocate it (capture move)
    if (piece(destPos) != nullptr) // have a piece -> capture move
    {
        // capture the piece
        delete piece(destPos);
    }

    // if no need capture -> no need delete piece

    // perform movement
    // modify pieces accroding the piece being moved
    // destination position ptr point to the selected piece
    piece(destPos) = selectedPiece;

    // original pos of the selected piece -> nullptr
    piece(selectedPiece->getPosition()) = nullptr;

    // update selectedPiece's position
    selectedPiece->setPosition(destPos);

    // change isWhiteTurn (true->false or false-> true)
    if (isWhiteTurn == true) // isWhiteTurn == true -> false
    {
        isWhiteTurn = false;
    }
    else // isWhiteTurn == false -> true
    {
        isWhiteTurn = true;
    }

    // return
    return;
}


BooleanMap Board::getAttackingMap() const
{
    // TODO
    // return a BooleanMap representing which cells the current player can capture

    Color curColor; // cur color of the player
    // Color oppColor; // cur color of opponent
    if (isWhiteTurn == true)
    {
        curColor = WHITE; // white's turn
        // oppColor = BLACK;
    }
    else
    {
        curColor = BLACK; // black's turn
        // oppColor = WHITE;
    }

    // make a map that have all movesets for current player
    BooleanMap curPlayerBooMap;

    // get opponentMap
    BooleanMap opponentBooMap = getOpponentMap(curColor);

    //  loop through all pieces of board
    for (int r = 0; r < NUM_RANKS; ++r)
    {
        for (int f = 0; f < NUM_FILES; ++f)
        {
            // check have piece?
            if (pieces[r][f] != nullptr) // have piece
            {
                // check color of cur color?
                if (pieces[r][f]->getColor() == curColor) // same color
                {
                    // cur player color piece

                    // get this piece's Move set
                    BooleanMap curMove = pieces[r][f]->getMoves(*this);

                    // calculate a map that this piece can capture
                    curMove &= opponentBooMap; // moveSet && opponent piece -> capture

                    // perform bitwise OR on every piece to get the final map
                    curPlayerBooMap |= curMove;
                }
                // not cur player color -> ignore
            }
            // no piece -> ignore
        }
    }

    // return BooleanMap{};
    // return
    return curPlayerBooMap;
}


void Board::validateMoveMap()
{
    // TODO
    // for each pos -> if moveMap.cell(f,r) is true
    //-> create a temp board
    // call move(pos) to simulate move, use selectedPiece
    // so the copied board will select the piece
    // call getattackingMap to get a boolMap
    // get the current player's royal piece using royalPieces and isWhiteTurn
    // if the attacjing map at royal piece's pos is true -> set moveMap.cell(f,r) to false

    // cout << "validate in" << endl; //!test

    // if there are no royal piece -> moves must be valid
    //  check is royal piece nullptr
    if (royalPieces[0] == nullptr && royalPieces[1] == nullptr) //if no royal PIECE AT ALL -> DO NOTHING
    {
        //cout << "both null" <<endl;
        return;
    }

    if (royalPieces[isWhiteTurn] == nullptr)
    {
        //cout << "cur col is null " <<endl;
        return;
    }

    //cout << "perform func"<<endl;
    // check cur turn
    // check cur turn's royal piece is nullptr or not

    Position pos;

    // loop all piece
    for (int r = 0; r < NUM_RANKS; ++r)
    {
        for (int f = 0; f < NUM_FILES; ++f)
        {
            // piece pos
            pos = {static_cast<_FILE>(f), static_cast<_RANK>(r)};

            // check moveMap.cell(f,r) is ture
            if (moveMap.cell(pos) == true) // true
            {
                // make a piece there

                // create temp board
                Board tempBoard{*this}; // get temp board using the copy constructor

                // call move(pos) to simulate move->use selectedPiece
                tempBoard.move(pos);

                // call get attacking map
                BooleanMap atkMap = tempBoard.getAttackingMap();

                // get cur player's royal piece
                // check color
                // Color curCol;

                // if (isWhiteTurn == true)
                //{
                //     curCol = WHITE;
                // }
                // else
                //{
                //     curCol = BLACK;
                // }

                // Royal pos
                Position royalPos;
                // get cur player's royal piece
                // Piece* royPic;

                //temp board already move -> will change color
                //check tempBoard's royal pos -> b4 move's col
                royalPos = tempBoard.royalPieces[this->isWhiteTurn]->getPosition();

                //  check attacking map at pos of royal piece true or not
                if (atkMap.cell(royalPos) == true) // true
                {
                    this->moveMap.cell(pos) = false; // set to false
                }

                //  false
                //  no need do anything-> can move there
            }
        }
    }
}
