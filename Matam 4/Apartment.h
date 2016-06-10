#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H

#include <exception>

class Apartment
{
    
public:
    /* ~~~ Definitions ~~~ */
    class ApartmentException : public std::exception {};
    class IllegalArgException : public ApartmentException {};
    class OutOfApartmentBoundsException : public ApartmentException {};

    enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};
    typedef enum SquareType SquareType;
    
    /* ~~~ Constructors ~~~ */
    Apartment (SquareType** squares, int length, int width, int price);
    Apartment (Apartment const &copy_from); //copy constructor
    
    /* ~~~ Destructor ~~~ */
    ~Apartment();
    
    /* ~~~ Assessors ~~~ */
    int getTotalArea() const;
    int getPrice() const;
    int getLength() const;
    int getWidth() const;
    
    /* ~~~ Operators ~~~ */
    Apartment& operator=(const Apartment &apt);
    SquareType& operator()(int r, int c);
    const SquareType& operator()(int r, int c) const;
    Apartment& operator+=(const Apartment& flat);
    
private:
    /* ~~~ Memebrs ~~~ */
	int length, width, price;
	SquareType** apartment;
    
    void destroySquares();      //destroys apartment of this
    void copySquares(SquareType ** const& squares_from);
    //copies squares_from to this->aptartment
    
    void checkBounds(int r, int c) const;   //checks if r,c is valid for the obj
};

/* ~~~ External Operators ~~~ */
bool operator<(Apartment const& a, Apartment const& b); //friend not needed
Apartment operator+(Apartment const& a, Apartment const& b);//friend not needed

#endif //MTM4_APARTMENT_H
