


#include "apartment.h"
#include <new>

using SquareType = Apartment::SquareType;

Apartment::Apartment (SquareType **squares, int len, int wid, int p):
apartment(NULL), length(len), width(wid), price(p){
    
    if(squares == NULL || len <= 0 || wid <= 0 || p < 0)
    {
        throw Apartment::IllegalArgException();
    }
    
    copySquares(squares);
}


static void allocateSquares (SquareType **& squares, int length, int width)
{
    squares = new SquareType*[length];
    for (int i = 0; i < length; i++)
    {
        try {
            squares[i] = new SquareType[width];
        } catch (std::bad_alloc& e) {//out of mem or anything else
            for(int j = 0; j < i; j++)
            {
                delete[] squares[i];
            }
            delete[] squares;
            throw e;
        }
        
    }
}

static void copySquares (SquareType ** const& squares_from,
                         SquareType ** & squares_to, int length, int width)
{
    ::allocateSquares(squares_to, length, width);
    
    //init apartment using squares
    for (int i = 0; i < length; i++){
        for (int j = 0; j < width; j++){
            squares_to[i][j] = squares_from[i][j];
        }
    }
}

void Apartment::copySquares (SquareType ** const& squares_from)
{
    ::copySquares(squares_from, this->apartment, length, width);
}

Apartment::Apartment (Apartment const &copy_from) :
apartment(NULL), length(-1), width(-1), price(-1)
{
    *this = copy_from;
}

Apartment& Apartment::operator=(const Apartment &apt)
{
    if(this==&apt)
        return *this;
    
    SquareType ** temp = NULL;
    ::copySquares(apt.apartment, temp, apt.length, apt.width);
    
    //free old data:
    destroySquares();
    
    this->apartment = temp;
    this->length = apt.length;
    this->width = apt.width;
    this->price = apt.price;
    
    return *this;
}

void Apartment::checkBounds(int r, int c) const
{
    if(r<0 || c < 0 || r >= length || c >= width)
    {
        throw Apartment::OutOfApartmentBoundsException();
    }
}

const SquareType& Apartment::operator()(int r, int c) const
{
    checkBounds(r, c);
    return apartment[r][c];
}

SquareType& Apartment::operator()(int r, int c)
{
    checkBounds(r, c);
    return apartment[r][c];
}

Apartment::~Apartment(){
    destroySquares();
}

static void destroySquares(SquareType ** squares, int length, int width)
{
    if(squares == NULL)
        return;
    
    for (int i = 0; i < length; i++)
        delete[] squares[i];
    delete[] squares;

}

void Apartment::destroySquares()
{
    ::destroySquares(apartment, length, width);
}

int Apartment::getTotalArea() const{
    int total_area = 0;
    for (int i = 0; i < this->length; i++){
        for (int j = 0; j < this->width; j++){
            if(apartment[i][j] == Apartment::EMPTY)
                total_area++;
        }
    }
    return total_area;
}

int Apartment::getPrice() const{
    return (this->price);
}

int Apartment::getLength() const{
    return (this->length);
}

int Apartment::getWidth() const{
    return (this->width);
}


bool operator<(Apartment const& a, Apartment const& b)
{
    //assumes both a and b are valid - that is, they are apartments with price
    //and area
    
    int a_p = a.getPrice();
    int a_a = a.getTotalArea();
    
    int b_p = b.getPrice();
    int b_a = b.getTotalArea();
    
    int r1 = a_p*b_a;
    int r2 = b_p*a_a;
    
    if(r1 != r2)
        return r1 < r2;
    
    return a_p < b_p;
    
}




Apartment& Apartment::operator+=(const Apartment& flat){
    int len = this->length, wid = this->width;
    if(this->width == flat.width){
        len += flat.length; /*put flat under the one we add to*/}
    else if(this->length == flat.length){
        wid += flat.width; /*put flat to the right of the one we add to*/}
    else{/*put flat under the one we add to and beacause it's uneven sizes*/
        len += flat.length;
        wid = wid>flat.width?wid:flat.width;}
    
    SquareType **newFlat = NULL;
    allocateSquares(newFlat, len, wid);

    for (int i = 0; i < len; i++){
        for (int j = 0; j < wid; j++){
            if(j>=0 && j<this->width && i>=0 && i<this->length)
                newFlat[i][j] = this->apartment[i][j];
            else if(j<flat.width && i>=this->length)
                //meaning i is suitable for the second apartment
                newFlat[i][j] = flat.apartment[i-this->length][j];
            else
                newFlat[i][j] = Apartment::WALL;
    }}
    try {
        Apartment a(newFlat, len, wid, this->price+flat.price);
        *this = a;
    } catch (...) {
        ::destroySquares(newFlat, len, wid);
        throw;}
    ::destroySquares(newFlat, len, wid);
    return *this;
}



Apartment operator+(Apartment const& a, Apartment const& b)
{
    Apartment c = a;
    return c+=b;
}
