#include <iostream>
#include "utility.h"
using namespace std;

ostream &operator<<(ostream &os, const Position &pos)
{
    os << static_cast<char>(pos.file + 'a') << static_cast<char>(pos.rank + '1');
    return os;
}

// TODO: Position::operator==(const Position&) const
bool Position::operator==(const Position &pos) const
{
    // return true if the pos is same as the current Position
    if (this->file == pos.file && this->rank == pos.rank)
        // if pos same -> return true
        return true;
    // else return false
    return false;
}

// TODO: Vector::operator+(const Position&) const
Position Vector::operator+(const Position &pos) const
{
    // vector + position
    // vector{1,2} + position{_C,_3} => return position{_D(_C+1), _5 (_3+2)}
    // can negative ->Vector{-2, 0} + Position{_G, _5} = Position{_E, _5}
    // if out bound -> Vector{3, 1} + Position{_H, _1} = Position{_H, _1} (both wont change)
    // new ABC
    int newFile = this->file + static_cast<int>(pos.file);
    // std::cout << "dest file:" << newFile <<std::endl;

    // new 123
    int newRank = this->rank + static_cast<int>(pos.rank);
    // std::cout << "dest rank:" << newRank <<std::endl;

    // check out of bound
    if (newFile > 7 || newRank > 7 || newFile < 0 || newRank < 0) // out of bound
    {
        return pos; // return non change pos
    }

    // not out of bound
    // return updated position
    return Position{static_cast<_FILE>(newFile), static_cast<_RANK>(newRank)};
}

// TODO: Vector::operator*(int) const
Vector Vector::operator*(int mul) const
{
    // Vector{1, 2} * 2 = Returns Vector{2, 4}
    // Vector{-3, 1} * -3 = Returns Vector{9, -3}

    // update new file and rank
    int newFile = mul * this->file;
    int newRank = mul * this->rank;

    // return updated vector
    return Vector{newFile, newRank};
}

// TODO: BooleanMap::operator|=(const BooleanMap&)
BooleanMap &BooleanMap::operator|=(const BooleanMap &other)
{
    // cell(pos) || other.cell(pos)
    // return a map that have both OR cells
    // so just put all other->cell that is true to this->map

    // loop through all cells
    for (int i = 0; i < NUM_RANKS; ++i)
    {
        for (int j = 0; j < NUM_FILES; ++j)
        {
            // if this cell[i][j] == true || other.cell[i][j] == true, one of them is true
            // set to true, else set to false
            if (this->cells[i][j] == true || other.cells[i][j] == true)
            {
                // set to true
                this->cells[i][j] = true;
            }
        }
    }
    /*
    //    std::cout << "OR operator" << std::endl; //! test here
    //    for (int i = 0; i < NUM_RANKS; ++i)  //!test cout shit
    //    {
    //        std::cout << std::endl; //! test here
    //        for (int j = 0; j < NUM_FILES; ++j)
    //        {
    //            std::cout << this->cells[i][j] << " "; //! test here
    //         }
    //    }
    //    std::cout << std::endl; //! test here
    //      std::cout << "end cout this-> boolean map" << std::endl; //! test here
    */
    // return by reference
    return *this;
}

// TODO: BooleanMap::operator&=(const BooleanMap&)
BooleanMap &BooleanMap::operator&=(const BooleanMap &other)
{
    // cell(pos) && other.cell(pos)

    // loop through all cells
    for (int i = 0; i < NUM_RANKS; ++i)
    {
        for (int j = 0; j < NUM_FILES; ++j)
        {
            // if this cell[i][j] == true && other.cell[i][j] == true, both of them is true
            // set to true, else set to false
            if (this->cells[i][j] == true && other.cells[i][j] == true)
            {
                // set to true
                this->cells[i][j] = true;
            }
            else
            {
                // set to false
                this->cells[i][j] = false;
            }
        }
    }

    // std::cout << "AND operator" << std::endl; //! test here

    return *this;
}

// TODO: BooleanMap::operator~() const
BooleanMap BooleanMap::operator~() const
{
    // do bitwise NOT : 0->1, 1->0

    BooleanMap newMap; // construct a new map

    // loop through all cells
    for (int i = 0; i < NUM_RANKS; ++i)
    {
        for (int j = 0; j < NUM_FILES; ++j)
        {
            // if this->cells[i][j] == true -> set false
            // else set true
            if (this->cells[i][j] == true)
            {
                // set false
                newMap.cells[i][j] = false;
            }
            // this->cells[i][j] == false
            else
            {
                // set true
                newMap.cells[i][j] = true;
            }
        }
    }

    // return a new map by value
    return newMap;
}
