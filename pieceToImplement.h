

// TODO: Leaper class
// F -> file
// R -> rank
template <char N, int F, int R>
class Leaper : public NamedPiece<N>
{
    // board have a Piece ptr array and boolmap array
    // Piece <- NamedPiece <- Leaper
private:
    // override the pure virtual function in piece
    // virtual char name() const override { return N; }

    // Protected data member in Piece
    // Position position
    // Color color

public:
    // constructor
    Leaper(Color color) : NamedPiece<N>(color) {}

    // set need copy constructor
    Leaper(const Leaper &leap) = default;

    // clone
    virtual Piece *clone() const override
    {
        // return a new object
        return new Leaper(*this);
    }

    // getMoves
    virtual BooleanMap getMoves(const Board &board) const override
    {
        // will return a boolean map that what places that this piece can move

        // initialize new position on board
        Position destination = this->Piece::getPosition(); // defualt as its desination

        //std::cout << "cur Pos" << std::endl;                 //! test here
        //std::cout << Piece::getPosition().file << std::endl; //! test here
        //std::cout << Piece::getPosition().rank << std::endl; //! test here

        // find vector
        Vector newVector;
        if (Piece::getColor() == WHITE)
        {
            // cell[R][F]
            // move F square to right, R square up
            newVector.file = F; // move right
            newVector.rank = R; // move up
        }
        else // BLACK color
        {
            // cell[R][F]
            // move F square to left, R square down
            newVector.file = -F; // move left
            newVector.rank = -R; // move down
        }

        // calculate destination
        destination = newVector.operator+(destination); // operator will check out of bound (vector + pos -> return pos)

        //std::cout << "check dest" << std::endl;     //! test here
        //std::cout << destination.file << std::endl; //! test here
        //std::cout << destination.rank << std::endl; //! test here
        // if out of bound -> destination wont change
        // booleanMap -> copy the booleanMap from board
        BooleanMap newBooleanMap;

        //  Piece* pieces[NUM_RANKS][NUM_FILES];
        
        // std::cout << board.piece(destination)->getPosition().file << std::endl; //!test here
        // std::cout << board.piece(destination)->getColor() << std::endl; //!test here
        //  if move destination have piece
        if (board.piece(destination) != nullptr)
        {
            //  check same color or not
            //std::cout << "not nullptr" << std::endl;                       //! test here
            if (board.piece(destination)->getColor() == this->Piece::getColor()) // if same color
            {
                //std::cout << "same color" << std::endl;                    //! test here
                //std::cout << newBooleanMap.cell(destination) << std::endl; //! test here
                // defualt newBooleanMap is all false
                return newBooleanMap;
            }
            else
            {
                // different color
                // can move
                newBooleanMap.cell(destination) = true;
                //std::cout << "diff color capture" << std::endl;            //! test here
                //std::cout << newBooleanMap.cell(destination) << std::endl; //! test here

                // return
                return newBooleanMap;
            }
        }
        else // destination no piece
        {
            // can move
            newBooleanMap.cell(destination) = true;
            //std::cout << "no piece, can move" << std::endl;            //! test here
            //std::cout << newBooleanMap.cell(destination) << std::endl; //! test here

            // return
            return newBooleanMap;
        }

        // change board , change piece position

        // return a booleanMap
        return newBooleanMap;
    }
};

// TODO : Rider class
template <char N, int F, int R, int RANGE>
class Rider : public NamedPiece<N>
{

private:
    // to override the pure virtual function in piece
    // virtual char name() const override { return N; }

public:
    // constructor
    Rider(Color color) : NamedPiece<N>(color) {} //! SUS -----------------

    // set need copy constructor
    Rider(const Rider &ride) = default;

    // clone
    virtual Piece *clone() const override
    {
        // return a new dynamic class by calling the DEFUALT copy constructor
        // Piece *piecePtr = new Rider(*this);
        // return piecePtr;
        return new Rider(*this);
        //! aware of memory leak !
    }

    // getMoves
    virtual BooleanMap getMoves(const Board &board) const override
    {
        // booleanMap initialization
        BooleanMap newBooleanMap;

        // vector initialization
        Vector newVector;
        newVector.file = F;
        newVector.rank = R;

        // destination initialization
        Position destination = this->Piece::getPosition();

        // loop through the jumps and update the bool map
        for (int i = 0; i < RANGE; ++i)
        {
            // update destination
            // vec + pos -> pos
            destination = newVector + destination;

            // check have encountered piece
            if (board.piece(destination) != nullptr)
            {
                // have piece

                // check color
                if (board.piece(destination)->getColor() == this->Piece::getColor()) // same color
                {
                    // stop immidetally
                    // return
                    return newBooleanMap;
                }
                else // different color
                {
                    // can capture piece -> can move there
                    newBooleanMap.cell(destination) = true;

                    // stop
                    // return
                    return newBooleanMap;
                }
            }
            else // no piece
            {
                // update booleanMap
                newBooleanMap.cell(destination) = true;
            }
        }

        // return
        return newBooleanMap;
    }
};

// TODO : Compound class
template <char N, typename P1, typename P2>
class Compound : public NamedPiece<N>
{
private:
    // override the pure virtual function in piece
    // virtual char name() const override { return N; }

public:
    // constructor
    Compound(Color color) : NamedPiece<N>(color) {}

    // set need copy constructor
    Compound(const Compound &comp) = default;

    // clone
    virtual Piece *clone() const override
    {
        // return a new dynamic class by calling the DEFUALT copy constructor
        // Piece *piecePtr = new Compound(*this);
        // return piecePtr;
        return new Compound(*this);
        //! aware of memory leak !
    }

    // getMoves
    virtual BooleanMap getMoves(const Board &board) const override //!===MOSTLY HEREEEEEEEEE
    {
        // combines the moveset of 2 pieces of type P1 and P2
        // can create a temp P1 and P2 object to get the moveset
        // then use bitwise OR to combine the two

        //std::cout << "combound getMoves" << std::endl; //! test here

        //!-----SO MANY ERRORS HERE

        // create two objs
        P1 * piece_1 = new P1(this->Piece::getColor());
        P2 * piece_2 = new P2(this->Piece::getColor());

        //P1 piece_1(this->Piece::getColor());
        //P2 piece_2(this->Piece::getColor());
        //! done?????

        // get temp board for piece_1 and piece_2
        Board board_1 = board.getTempBoard(piece_1, this->Piece::getPosition());
        Board board_2 = board.getTempBoard(piece_2, this->Piece::getPosition());

        // get movesets for both pieces
        BooleanMap map1 = piece_1->getMoves(board_1); //?--should be ok
        BooleanMap map2 = piece_2->getMoves(board_2); //?--

        // combine two booleanMap
        map1 |= map2;

        //std::cout << "done combine and return" << std::endl;//!test here

        return map1;
    }
};

// TODO : Divergent class
template <char N, typename M, typename C>
class Divergent : public NamedPiece<N>
{
private:
    // override the pure virtual function in piece
    // virtual char name() const override { return N; }

public:
    // constructor
    Divergent(Color color) : NamedPiece<N>(color) {}

    // set need copy constructor
    Divergent(const Divergent &diverge) = default;

    // clone
    virtual Piece *clone() const override
    {
        // return a new dynamic class by calling the DEFUALT copy constructor
        // Piece *piecePtr = new Divergent(*this);
        // return piecePtr;
        return new Divergent(*this);
    }

    // getMoves
    virtual BooleanMap getMoves(const Board &board) const override
    {
        // create 2 objs
        M* move_piece = new M(Piece::getColor());
        C* capture_piece = new C(Piece::getColor()); //! need new? will gg?

        // get temp board for 2 piece
        Board move_board = board.getTempBoard(move_piece, this->Piece::getPosition());
        Board capture_board = board.getTempBoard(capture_piece, this->Piece::getPosition());

        // get map
        BooleanMap move_map = move_piece->getMoves(move_board);
        BooleanMap capture_map = capture_piece->getMoves(capture_board);

        // get opponent map
        // getColor -> BLACK(0), WHITE(1)
        BooleanMap opponent_map = board.getOpponentMap(this->Piece::getColor());

        // C moveset AND opponent map
        capture_map &= opponent_map; // updated capture_map

        // M moveset AND negate opponent map
        move_map &= ~(opponent_map); // updated move_map

        // combine using OR
        capture_map |= move_map; // capture map OR move map

        // return
        return capture_map;
    }
};
