// ------------------------------------------------ poly.cpp --------------------------------------------------------
// Brent Stone CSS 343 Section C
// January 7th, 2016
// January 13th, 2016
// --------------------------------------------------------------------------------------------------------------------
// Purpose: This cpp file creates polynomials , from either constructors or user inputs.
//			The file allows for addition, multiplication, subtraction of polynomials.
// --------------------------------------------------------------------------------------------------------------------
// Notes: Negative values for exponents return 0 unless in the >> operator.  The negative
//        exponents are skipped from entering into the array.
// --------------------------------------------------------------------------------------------------------------------


#include "poly.h"
#include <iostream>

 // --------------------------------Defalut Constructor()-------------------------------------------
 // Description: This constructor creates a polynomial object that sets size to one and the
 //  			coefficient to zero
 // ------------------------------------------------------------------------------------------------
Poly::Poly()
{
	size = 1;
	arry = new int[size];
	arry[0] = 0;

}// end of constructor


// ---------------------------------Overloaded Constructor(int, int)----------------------------------
// Description: This constructor creates a polynomial object that takes in two integers as parameters
// 				The first integer is the coefficient and the second integer is the exponent of the
//				polynomial.  New memory is allocated and the array is initialized to
//				zero.
//				A negative exponent will return a 0.
// ---------------------------------------------------------------------------------------------------
Poly::Poly(int coeff, int expo)
{
	if (expo < 0) 			//checks for negative
	{
		size = 1;
		arry = new int[size];
		arry[0] = 0;
	}
	else
	{
		size = expo + 1;
		arry = new int[size]; 	//new memory allocation
		for (int i = 0; i < size; i++)
		{
			arry[i] = 0;
		}
		arry[expo] = coeff;
	}
}//end of two parameter constructor


  // ------------------------------Overloaded Constructor(int)-----------------------------------------
  // Description: This constructor creates a polynomial object that takes an integer as a parameter.
  // 				The integer is the coefficient and the exponent is set to zero.
  // --------------------------------------------------------------------------------------------------
Poly::Poly(int coeff)
{
	size = 1;
	arry = new int[size];
	arry[0] = coeff;

}//end of one parameter constructor


 // ------------------------------------Copy Constructor--------------------------------------------
 // Description: The copy constructor creates a deep copy of a polynomial object.  New memory is
 //				allocated and the polynomial's array is copied over.
 // ------------------------------------------------------------------------------------------------
Poly::Poly(const Poly &polynomial)
{
	size = polynomial.size;
	arry = new int[size];
	for (int i = 0; i < size; i++)
	{
		arry[i] = polynomial.arry[i];
	}

}// end of copy constructor


 // ------------------------------------Destructor--------------------------------------------
 // Description: The destructor deletes all of the array's contents and is set to null
 // ------------------------------------------------------------------------------------------------
Poly::~Poly()
{
	delete[] arry;
	arry = NULL;

}// end of destructor


 // ------------------------------------Operator+-----------------------------------------------------
 // Description: The + operator adds two polynomials together.  A temporary poly object is created and
 //				contents are copied to the temp object.  This operator calls the += operator to compute
 //				the arithmetic.
 // ---------------------------------------------------------------------------------------------------
Poly Poly::operator+(const Poly &polynomial) const
{
	Poly temp = *this;
	temp += polynomial;
	return temp;

}//end of Operator+


 // ------------------------------------Operator*-----------------------------------------------------
 // Description: The * operator multiples two polynomials together.  A temporary poly object is created
 //				and contents are copied to the temp object.  This operator calls the *= operator compute
 //				the arithmetic.
 // ---------------------------------------------------------------------------------------------------
Poly Poly::operator*(const Poly &polynomial) const
{
	Poly temp = *this;
	temp *= polynomial;
	return temp;

}//end of Operator*


 // ------------------------------------Operator------------------------------------------------------
 // Description: The - operator subtracts two polynomials.  A temporary poly object is created
 //				and contents are copied to the temp object.  This operator calls the -= operator compute
 //				the arithmetic.
 // --------------------------------------------------------------------------------------------------
Poly Poly::operator-(const Poly &polynomial) const
{
	Poly temp = *this;
	temp -= polynomial;
	return temp;

}//end of Operator-


 // ------------------------------------Operator+=-----------------------------------------------------
 // Description: The += operator computes the arithmetic for the addition of two polynomials.
 //				 first the function checks the sizes of the two polynomials.  If the object being
 //				 added has a larger size, the array of the first polynomial is resized.  Once resize,
 //				 the arrays are added together.
 // ---------------------------------------------------------------------------------------------------
Poly &Poly::operator+=(const Poly &polynomial)
{
	if (size < polynomial.size)				//enters if the array on the right is larger
	{
		int sizeNew = polynomial.size;
		int *resize = new int[sizeNew];		//new memory allocation to resize array

		for (int i = 0; i < sizeNew; i++)	//array initialized to larger polynomial
		{
			resize[i] = polynomial.arry[i];
		}

		for (int i = 0; i < size; i++)		//values are added together in the resized array
		{
			resize[i] = arry[i] + resize[i];
		}
		delete[] arry;						//deletion of array contents
		arry = resize;						//copy the contents of larger array
		size = polynomial.size;
		resize = NULL;						//set new allocated memory to null

	}
	else
	{
		for (int i = 0; i < polynomial.size; i++)	//if the left polynomial has a larger array
		{
			arry[i] = arry[i] + polynomial.arry[i];
		}
	}
	return *this;

}//end of Operator +=


 // ------------------------------------Operator-=-----------------------------------------------------
 // Description: The -= operator computes the arithmetic for the subtraction of two polynomials.
 //				 first the function checks the sizes of the two polynomials.  If the object being
 //				 subtracted has a larger size, the array of the first polynomial is resized.  Once resize,
 //				 the arrays are subtracted.
 // ---------------------------------------------------------------------------------------------------
Poly &Poly::operator-=(const Poly &polynomial)
{
	if (size < polynomial.size)				//enters if the array on the right is larger
	{
		int sizeNew = polynomial.size;
		int *resize = new int[sizeNew];		//new memory allocation to resize array

		for (int i = 0; i < sizeNew; i++)	//array initialized to larger array
		{
			resize[i] = polynomial.arry[i];
		}
		for (int i = 0; i < size; i++)		//subtraction of array contents
		{
			resize[i] = arry[i] - resize[i];
		}
		delete[] arry;						//deletion of array contents
		arry = resize;						//copy the contents of larger array
		size = polynomial.size;
		resize = NULL;						//set new allocated memory to null

	}
	else
	{
		for (int i = 0; i < polynomial.size; i++) //copies array
		{
			arry[i] = arry[i] - polynomial.arry[i];
		}
	}
	return *this;

}// end of operator -=


 // ------------------------------------Operator*=-----------------------------------------------------
 // Description: The *= operator computes the arithmetic for the multiplication of two polynomials.
 //				 The function creates a new size that is the sum of the two polynomial sizes minus 1.
 //				 New memory is allocated and an array with the new size is initialized to zero. The
 //				 function then goes through a nested for loop and adds the indexes and multiples
 //			 	 the indexed values. The left array is then cleared and the new contents is copied in.
 // ---------------------------------------------------------------------------------------------------
Poly &Poly::operator*=(const Poly &polynomial)
{
	int sizeNew = (size + polynomial.size) - 1;		//new size of both arrays
	int *resize = new int[sizeNew];					//new memory allocation

	for (int i = 0; i < sizeNew; i++)				//initialized to zero
	{
		resize[i] = 0;
	}

	for (int i = size - 1; i >= 0; i--)				//nested for loop for the multiplication of polynomials
	{
		for (int j = polynomial.size - 1; j >= 0; j--)
		{
			resize[i + j] += arry[i] * polynomial.arry[j];	//add indexes and multiply the values
		}
	}
	delete[] arry;		//deletion of array contents
	size = sizeNew;		//copy of array with the products of the two polynomials
	arry = resize;
	resize = NULL;
	return *this;

}//end of operator *=


 // ------------------------------------Operator=-----------------------------------------------------
 // Description: The assignment operator copies the contents of a polynomial into another polynomial
 // ---------------------------------------------------------------------------------------------------
Poly &Poly::operator=(const Poly& polynomial)
{
	if (*this == polynomial)			//uses the == operator to check for equality
	{
		return *this;
	}
	else
	{
		delete[] arry;					//deletes current contents of array

		if (size < polynomial.size)		//if the array size is less than the polynomial allocate new memory
		{
			size = polynomial.size;
		}
		arry = new int[size];

		for (int i = 0; i < size; i++)	//copy contents of array
		{
			arry[i] = polynomial.arry[i];
		}
	}
    return *this;

}//end of Operator =


 // ------------------------------------Operator==-----------------------------------------------------
 // Description: The == operator checks for equality between two polynomials.  Since this is a math
 //				concept checking the size of the array to determine equality is not valid.  Each
 //				index with be checked for equality until the indexed values do not equal each other.
 // ---------------------------------------------------------------------------------------------------
bool Poly::operator==(const Poly& polynomial)
{
	if (size == polynomial.size)			//checks if both sizes are equal
	{
		for (int i = 0; i < size; i++)
		{
			if (arry[i] != polynomial.arry[i]) 		//if not equal return false
			{
				return false;
			}
		}
	}
	else if (size > polynomial.size)				//if size on left hand size is larger
	{
		for (int i = 0; i < polynomial.size; i++)	//checks up to the size of the smaller array
		{
			if (arry[i] != polynomial.arry[i])
			{
				return false;
			}
		}
		for (int i = polynomial.size; i < size; i++)//checking for zero's  in the remaining size of the array
		{
			if (arry[i] != 0)
			{
				return false;
			}
		}
	}
	else if (size < polynomial.size)			//in this case the right hand side polynomial is larger
	{
		for (int i = 0; i < size; i++)
		{
			if (arry[i] != polynomial.arry[i]) //checks for equality
			{
				return false;
			}
		}
		for (int i = size; i < polynomial.size; i++)	//checking for zero's
		{
			if (polynomial.arry[i] != 0)
			{
				return false;
			}
		}
	}
	return true;

}//end of Operator ==


 // ------------------------------------Operator!=-----------------------------------------------------
 // Description: Checks for inequality between two polynomials.  Uses the == operator to check.
 // ---------------------------------------------------------------------------------------------------
bool Poly::operator!=(const Poly& polynomial)
{
	if (*(this) == polynomial)
	{
		return false;
	}
	else
	{
		return true;
	}
}


// ------------------------------------Operator<<-----------------------------------------------------
// Description: The << operator outputs the contents of the array.  If the all of the contents are
//				all zeros, the output is '0'.
// ---------------------------------------------------------------------------------------------------
ostream & operator<<(ostream & out, const Poly & ref)
{
	int zeroCounter = 0;
	out << " ";
	for (int i = ref.size - 1; i >= 0; i--)
	{
		int coeff = ref.arry[i];
		if (coeff != 0)
		{
			if (coeff > 0)
			{
				out << "+";
			}

			if (i == 1)
			{
				if (ref.arry[i] == 1 || ref.arry[i] == -1)
				{
					out << "x" << " ";
				}
				else
				{
					out << ref.arry[i] << "x" << " ";
				}
			}
			else if (i == 0)
			{
				out << coeff << " ";
			}
			else
			{
				out << ref.arry[i] << "x^" << i << " ";
			}
		}
		else
		{
			zeroCounter++;
		}

	}
	if (zeroCounter == ref.size)
	{
		out << "0";
	}
	return out;

}//end of Operator<<


 // ------------------------------------Operator>>-----------------------------------------------------
 // Description: The >> operator takes inputs from the console and sets the first value to the coefficient
 //				and the second value to the exponent.  If a negative exponent is entered, the code skips
 //				the input.
 // ---------------------------------------------------------------------------------------------------
istream &operator >> (istream &in, Poly &ref)
{
	int writeCoeff = 0;
	int writeExpo = 0;
	bool test = true;


	while (test)							//while loop to keep adding
	{
		in >> writeCoeff >> writeExpo;

		if (writeCoeff == -1 && writeExpo == -1)//stops when both numbers are -1 -1
		{
			test = false;
		}
		else if (writeExpo <= -1 && writeCoeff !=-1)	//skips over negaive exponent
		{
			continue;
		}
		else
		{
			ref.setCoeff(writeCoeff, writeExpo);	//calls the setCoeff
		}
	}

	return in;

}//end of Operator>>


 // ------------------------------------getCoeff(int)-----------------------------------------------------
 // Description: Returns the coefficient of an index. If the index is a negative number or is larger
 //				than the size the function returns zero.
 // ---------------------------------------------------------------------------------------------------
int Poly::getCoeff(int expo)
{
	if (expo > size - 1 || expo < 0)
	{
		return 0;
	}
	else
	{
		return arry[expo];
	}

}//end of getCoeff(int)


 // ------------------------------------setCoeff(int,int)----------------------------------------------
 // Description: The setCoeff function sets the coefficient of a polynomial given its index.  If
 //				the exponent is larger than the current sized array, the array is then resized.
 //				function also checks for negative exponent.
 // ---------------------------------------------------------------------------------------------------
void Poly::setCoeff(int coeff, int expo)
{

	if (expo > size - 1)
	{
		int newSize = expo + 1;
		int *resize = new int[newSize];  	//new array is created to resize

		for (int i = 0; i < newSize; i++)	//initialized to 0
		{
			resize[i] = 0;
		}
		for (int i = 0; i < size; i++)		//copies the contents of the array
		{
			resize[i] = arry[i];
		}
		delete[]arry;						//deletes old contents
		arry = resize;						//copies the array
		size = newSize;
		resize = NULL;
		arry[expo] = coeff;
	}
	else
	{
		arry[expo] = coeff;					//sets coefficient
	}

}//end of setCoeff
