/*************************************************************************
* Title: Polynomial Class 
* File: CIS278_Week12_10.11.cpp
* Author: James Eli
* Date: 2/18/2018
*
* Exercise 10.11 on page 495-496, Polynomial Class
* Develop class Polynomial. The internal representation of a Polynomial is 
* an array of terms. Each term contains a coefficient and an exponent—e.g., 
* the term
*   2x^4
* Has the coefficient 2 and the exponent 4. Develop a complete class 
* containing proper constructor and destructor functions as well as set and 
* get functions. The class should also provide the following overloaded 
* capabilities:
*   a) Overload the addition operator (+) to add two polynomials.
*   b) Overload the subtraction operator (-) to subtract two polynomials.
*   c) Overload the assignment operator to assign one polynomial to another.
*   d) Overload the multiplication operator (*) to multiply two polynomials.
*   e) Overload the addition assignment operator (+=), subtraction assignment 
*      operator (-=), and multiplication assignment operator (*=).
*
* Notes:
*  (1) Degree, unary minus, stream and untested evaluate and differentiate 
*      methods added also.
*  (2) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   02/18/2018: Initial release. JME
*************************************************************************/
#include <iostream>  // cout/endl

#include "polynomial.h" // Our polynomial class.

using std::cout;
using std::endl;

// Perform basic testing of Polynomial class.
int main()
{
	// Create polynomial 7x^4 - x^2 + 3.
	Polynomial a;
	a.setTerm(4, 7);
	a.setTerm(2, -1);
	a.setTerm(0, 3);
	cout << "degree of (" << a << ") is: " << a.getDegree() << endl;
	//cout << "(" << a << ") evaluated at 2 = " << a.evaluate(2) << endl;
	//cout << "Differentiate (" << a << ") = " << a.differentiate() << endl;

	// Create polynomial 6x^3 - 3x^2 + 4 with list initalizer.
	Polynomial b({ { 3, 6 }, { 2, -3 }, { 0, 4 } });
	// Get a term's coefficient.
	double c;
	if (b.getTerm(3, c))
		cout << "Coefficient of 3rd term of (" << b << ") is: " << c << endl;

	// Add, subtract and multiply binat operators.
	cout << "(" << a << ") + (" << b << ") = " << (a + b) << endl;
	cout << "(" << a << ") - (" << b << ") = " << (a - b) << endl;
	cout << "(" << a << ") * (" << b << ") = " << (a * b) << endl;

	// Assignment operator.
	cout << "a = " << a << endl;
	b = a;
	cout << "Set b = a, now b = " << b << endl;

	// Unary add, subtract and multiply.
	a += b;
	cout << "Set a += b, now a = " << a << endl;
	a -= b;
	cout << "Set a -= b, now a = " << a << endl;

	// Unary negate.
	cout << "a = " << a << endl;
	b = -a;
	cout << "Set b = -a, now b = " << b << endl;
}

