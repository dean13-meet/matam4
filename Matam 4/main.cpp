//
//  main.cpp
//  Matam 4
//
//  Created by Dean Leitersdorf on 6/8/16.
//  Copyright © 2016 Dean Leitersdorf. All rights reserved.
//

#include <iostream>
#include "Apartment.h"
#include <assert.h>

#define setup \
int price = 100, length = 0, width = 0; \
SquareType **squares;


#define makeSquares \
squares =  new SquareType*[length]; \
\
for (int i = 0; i < length; i++ )   \
{   \
squares[i] = new SquareType[width]; \
\
for(int j = 0; j < width; j++)  \
{   \
squares[i][j] = Apartment::EMPTY;   \
}   \
\
}

#define deleteSquares \
for(int i = 0; i < length; i++)     \
{   \
delete[] squares[i];    \
}   \
delete[] squares;

using SquareType = Apartment::SquareType;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!" << std::endl;
    

    setup;
    
    price = 7;
    length = 5;
    width = 5;
    
    
    makeSquares;
    squares[1][0] = Apartment::WALL;
    squares[1][1] = Apartment::WALL;
    squares[1][2] = Apartment::WALL;
    squares[1][3] = Apartment::WALL;
    squares[2][3] = Apartment::WALL;
    squares[3][0] = Apartment::WALL;
    squares[3][1] = Apartment::WALL;
    squares[3][2] = Apartment::WALL;
    squares[3][3] = Apartment::WALL;
    
    //Looks like this:
    //    /*
    //
    //     0 1 2 3 4
    //      _________
    //     0|        |
    //     1|______  |
    //     2|______| |
    //     3|        |
    //     4|________|
    //     
    //     
    //     */
    
    
    
    
    Apartment apt(squares, length, width, price);
    deleteSquares;
    
    SquareType& p = apt(0, 0);
    SquareType& s = apt(1, 2);
    
    p = Apartment::WALL;
    
    SquareType& d = apt(0,0);
    assert(d == Apartment::WALL);
    
    //will still go to the non-const because "this" isn't const and return type changes nothing
    const SquareType& a = apt(0,0);
    const SquareType& b = apt(1, 2);
    
    
    
    //Tests for operator<
    price = 100;
    length = 1;
    width = 4;
    
    makeSquares;
    squares[0][0] = Apartment::WALL;
    squares[0][1] = Apartment::WALL;
    
    Apartment a1(squares, length, width, price); // WWEE
    deleteSquares;
    
    makeSquares;
    squares[0][2] = Apartment::WALL;
    squares[0][3] = Apartment::WALL;
    
    Apartment a2(squares, length, width, price); // EEWW
    deleteSquares;
    
    price = 50;
    width = 2;
    makeSquares;
    squares[0][0] = Apartment::WALL;
    
    Apartment a3(squares, length, width, price); // WE
    deleteSquares;
    
    price = 50;
    makeSquares;
    squares[0][0] = Apartment::WALL;
    
    Apartment a4(squares, length, width, price); // WEEE
    deleteSquares;
    
    bool bigger1 = a1 < a2;
    assert(bigger1==false);
    
    bool bigger2 = a3 < a1;
    assert(bigger2==true);
    
    return 0;
}
