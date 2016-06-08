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
    Apartment (SquareType** &squares, int length, int width, int price);
    Apartment (Apartment const &copy_from); //copy constructor
    
    /* ~~~ Destructor ~~~ */
    ~Apartment();
    
    /* ~~~ Assessors ~~~ */
    int getTotalArea() const;
    int getPrice() const;
    int getLength() const;
    int getWidth() const;
    
    /* ~~~ Operators ~~~ */
    
    
private:
    /* ~~~ Memebrs ~~~ */
	int length, width, price;
	SquareType** apartment;
    
    /* ~~~ Private Functions ~~~ */
    static bool legalSquares(const Apartment::SquareType** &squares, int length,
                             int width);
};

/*****************************
 * External operator function
 ****************************/

#endif //MTM4_APARTMENT_H
