


#include "apartment.h"

bool Apartment::legalSquares(const Apartment::SquareType** &squares, int length,
                             int width){
	for (int i = 0; i < length; i++){
		for (int j = 0; j < width; j++){
            if(squares[i][j] != Apartment::EMPTY &&
               squares[i][j] != Apartment::WALL)
				return false;
		}
	}
	return true;
}

Apartment::Apartment (Apartment::SquareType ** &squares, int len, int wid,
                      int p):
	length(len), width(wid), price(p){
	/***************************************************************************
     if any of the arguments is illegal:
     throw an excption - illegalArgException
     if(!leagalSquares(squares&,length,width))
		return the excption
	***************************************************************************/
	//allocating enough memory for the apartment
	apartment = new SquareType*[length];
	for (int i = 0; i < length; i++)
		apartment[i] = new SquareType[width];
	//init apartment using squares
	for (int i = 0; i < length; i++){
		for (int j = 0; j < width; j++){
			apartment[i][j] = squares[i][j];
		}
	}
}

Apartment::Apartment (Apartment const &copy_from){
	/***************************************************************************
	if the argument is illegal: throw an excption - illegalArgException
	***************************************************************************/
	this->length = copy_from.length;
	this->width = copy_from.width;
	this->price = copy_from.price;
	//allocating enough memory for the apartment
	apartment = new SquareType*[this->length];
	for (int i = 0; i < this->length; i++)
		apartment[i] = new SquareType[this->width];
	//init apartment using squares- can delegate a new function because of code duplication
	for (int i = 0; i < this->length; i++){
		for (int j = 0; j < this->width; j++){
			apartment[i][j] = copy_from.apartment[i][j];
		}
	}
}

Apartment::~Apartment(){
	for (int i = 0; i < length; i++)
		delete[] apartment[i];
	delete[] apartment;
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