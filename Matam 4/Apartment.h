#ifndef MTM4_APARTMENT_H
#define MTM4_APARTMENT_H

#include <exception>

class Apartment
{
public:
    class ApartmentException : public std::exception {};
    class IllegalArgException : public ApartmentException {};
    class OutOfApartmentBoundsException : public ApartmentException {};

    enum SquareType {EMPTY, WALL, NUM_SQUARE_TYPES};

    Apartment (SquareType** squares, int length, int width, int price);
    ~Apartment();
    int getTotalArea();
    int getPrice();
    int getLength();
    int getWidth();
private:
	int length,width,price;
	SquareType** apartment;
};

/*****************************
 * External operator function
 ****************************/

#endif //MTM4_APARTMENT_H
