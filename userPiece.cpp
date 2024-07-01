#include "userPiece.h"

// TODO
bool isRoyal(const Piece *piece)
{
    // return true if the provided piece is to KING
    if (typeid(*piece) == typeid(const King))
    {
        // std::cout<< piece->getName() <<std::endl; //!test
        // std::cout<<piece->getPosition() <<std::endl; //!test
        return true;
    }
    //std::cout<< piece->getName() ; //!test
    //std::cout<< "is not royal" <<std::endl;
    //std::cout<<piece->getPosition() <<std::endl; //!test
    return false;
}

