#include "apartment.h"

static bool legalSquares(const SquareType** squares, int length, int width){
	for (int i = 0; i < length; i++){
		for (int j = 0; j < width; j++){
			if(squares[i][j] != 'E' && squares[i][j] != 'W')
				return false;
		}
	}
	return true;
}

Apartment (SquareType** squares, int len, int wid, int p)
	length(len), width(wid), price(p){
	/***************************************************************************
	if(!leagalSquares(squares&,length,width))
		return the excption
	if any of the arguments is illegal:
		throw an excption - illegalArgException
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

Apartment (const Apartment copy_from){
	/***************************************************************************
	if the argument is illegal: throw an excption - illegalArgException
	***************************************************************************/
	this->length = copy_from->length;
	this->width = copy_from->width;
	this->price = copy_from->price;
	//allocating enough memory for the apartment
	apartment = new SquareType*[this->length];
	for (int i = 0; i < this->length; i++)
		apartment[i] = new SquareType[this->width];
	//init apartment using squares- can delegate a new function because of code duplication
	for (int i = 0; i < this->length; i++){
		for (int j = 0; j < this->width; j++){
			apartment[i][j] = copy_from[i][j];
		}
	}
}

~Apartment(){
	for (int i = 0; i < length; i++)
		delete[] apartment[i];
	delete[] apartment;
}

int getTotalArea() const{
	int total_area = 0;
	for (int i = 0; i < this->length; i++){
		for (int j = 0; j < this->width; j++){
			if(apartment[i][j] == 'E')
				total_area++;
		}
	}
	return total_area;
}

int getPrice() const{
	return (this->price);
}

int getLength() const{
	return (this->length);
}

int getWidth() const{
	return (this->width);
}