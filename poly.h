// ------------------------------------------------ Poly.h --------------------------------------------------------
// Brent Stone CSS 343 Section C
// January 7th, 2016
// January 13th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose: This header file contains all declarations of the functions and the data.  These functions are used
//			to create and edit polynomial objects.
// --------------------------------------------------------------------------------------------------------------------
// Notes: Negative values for exponents return 0 unless in the >> operator.  The negative
//        exponents are skipped from entering into the array.
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
using namespace std;

class Poly
{

public:
	//Constructors & Destructors
	Poly(int coeff, int expo);
	Poly(int coeff);
	Poly();
	Poly(const Poly& polynomial);
	~Poly();

	//Operators
	Poly operator+(const Poly &polynomial)const;
	Poly operator-(const Poly &polynomial)const;
	Poly operator*(const Poly &polynomial)const;
	Poly& operator+=(const Poly &polynomial);
	Poly& operator-=(const Poly &polynomial);
	Poly& operator*=(const Poly &polynomial);
	Poly& operator=(const Poly &polynomial);
	bool operator==(const Poly &polynomial);
	bool operator!=(const Poly &polynomial);

	friend ostream &operator<<(ostream& out, const Poly &ref);
	friend istream &operator>>(istream& in, Poly &ref);

	//Setters & Getters
	int getCoeff(int expo);
	void setCoeff(int coeff, int expo);

private:
	int *arry;  //array pointer
	int size;	//size of array

};
