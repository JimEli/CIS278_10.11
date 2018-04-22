/*************************************************************************
* Title: Polynomial Class 
* File: CIS278_Week12_10.11.cpp
* Author: James Eli
* Date: 2/18/2018
*
* Exercise 10.11 on page 495-496, Polynomial Class
*
* This is a short boost test of the polynomial class.
* 
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141).
*  (2) Compiled with boost test 1_66_0.
*  (3) Add (appropriate) boost include and lib diretories to project:
*      C:\Program Files\boost\boost_1_66_0
*      C:\Program Files\boost\boost_1_66_0\stage\lib
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   02/18/2018: Initial release. JME
*   04/12/2018: Added boost test file. JME
*************************************************************************/
#ifndef NDEBUG

#include <iostream>  // cout/endl

// Visual Leak Detector.
#include "C:\Program Files (x86)\Visual Leak Detector\include\vld.h"

// Our polynomial class.
#include "polynomial.h"

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#define BOOST_TEST_MODULE TestPolynomial
#include <boost\test\unit_test.hpp>

using std::cout;
using std::endl;

BOOST_AUTO_TEST_SUITE(TestPolynomial)

BOOST_AUTO_TEST_CASE(instantiation) 
{
	// Create polynomial, 7x^4 - x^2 + 3.
	Polynomial a;
	a.setTerm(4, 7.);
	a.setTerm(2, -1.);
	a.setTerm(0, 3.);

	// Create same polynomial with list initalizer.
	Polynomial b({ { 4, 7. }, { 2, -1. }, { 0, 3. } });

	// Create polynomial using overloaded index operator.
	Polynomial d;
	d[4] = 7.;
	d[2] = -1.;
	d[0] = 3.;

	// Polynomials equal?
	double c;

	a.getTerm(4, c);
	BOOST_CHECK_EQUAL(c, 7.);
	b.getTerm(4, c);
	BOOST_CHECK_EQUAL(c, 7.);

	a.getTerm(2, c);
	BOOST_CHECK_EQUAL(c, -1.);
	b.getTerm(2, c);
	BOOST_CHECK_EQUAL(c, -1.);

	a.getTerm(0, c);
	BOOST_CHECK_EQUAL(c, 3.);
	b.getTerm(0, c);

	BOOST_CHECK_EQUAL(c, 3.);
	BOOST_CHECK(a == d);
	BOOST_CHECK(a == b);
	BOOST_CHECK(!(a != b));

	// Check degree of polynomials.
	BOOST_CHECK_EQUAL(a.getDegree(), 4);
	BOOST_CHECK_EQUAL(b.getDegree(), 4);
}

BOOST_AUTO_TEST_CASE(assignment)
{
	// Create polynomial, 7x^4 - x^2 + 3.
	Polynomial a({ { 4, 7 }, { 2, -1 }, { 0, 3 } });
	Polynomial b;
	// Check assignment
	b = a;
	BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(addition) 
{
	// Add (7.0x^4 - 1.0x^2 + 3.0) + ( -3.0x^2 + 4.0) = 7.0x^4 - 4.0x^2 + 7.0
	Polynomial a({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial b({ { 2, -3. }, { 0, 4. } });
	Polynomial answer1({ { 4, 7. },{ 2, -4. },{ 0, 7. } });
	BOOST_CHECK(answer1 == (a + b));

	// Add (7.0x^4 - 1.0x^2 + 3.0) + (-7.0x^4 + 4.0x^2 - 7.0) = 0
	Polynomial c({ { 4, -7. },{ 2, 1. },{ 0, -3. } });
	Polynomial answer2;
	BOOST_CHECK(answer2 == (a + c));
}

BOOST_AUTO_TEST_CASE(subtraction)
{
	// Subtract (7.0x^4 - 1.0x^2 + 3.0) - ( -3.0x^2 + 4.0) = 7.0x^4 + 2.0x^2 - 1.0
	Polynomial a({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial b({ { 2, -3. }, { 0, 4. } });
	Polynomial answer1({ { 4, 7. },{ 2, 2. },{ 0, -1. } });
	BOOST_CHECK(answer1 == (a - b));

	// Subtract (7.0x^4 - 1.0x^2 + 3.0) - (7.0x^4 - 1.0x^2 + 3.0) = 0.0
	Polynomial c({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial answer2; answer2[0] = 0.;
	BOOST_CHECK(answer2 == (a - c));
}

BOOST_AUTO_TEST_CASE(multiplication)
{
	// Multiplication (7.0x^4 - 1.0x^2 + 3.0) * ( -3.0x^2 + 4.0) = -21.0x^6 + 31.0x^4 - 13.0x^2 + 12.0
	Polynomial a({ { 4, 7. }, { 2, -1. }, { 0, 3. } });
	Polynomial b({ { 2, -3. }, { 0, 4. } });
	Polynomial answer({ { 6, -21. },{ 4, 31. },{ 2, -13. },{ 0, 12. } });
	BOOST_CHECK(answer == (a * b));
}

// Test for our exception message.
bool correctMessage(const std::overflow_error& ex)
{
	BOOST_CHECK_EQUAL(ex.what(), std::string("Divide by zero"));
	return true;
}

BOOST_AUTO_TEST_CASE(division_modulus)
{
	// Test division with remainder.
	Polynomial a({ { 3, 1. }, { 2, -2. }, { 0, -4. } });
	Polynomial b({ { 1, 1 }, { 0, -3 } });
	Polynomial answer1({ { 2, 1. }, { 1, 1. }, { 0, 3. } });
	Polynomial answer2({ { 0, 5. } });
	BOOST_CHECK(answer1 == (a / b));
	BOOST_CHECK(answer2 == (a % b));

	// Test division without remainder.
	Polynomial c({ { 2, 1. }, { 1, 2. }, { 0, 2. } });
	Polynomial d({ { 1, 1 }, { 0, 1 } });
	Polynomial answer3({ { 1, 1. }, { 0, 1. } });
	Polynomial answer4({ { 0, 0. } });
	BOOST_CHECK(answer3 == (c / d));
	BOOST_CHECK(answer4 == (c % d));

	// Test divide by zero exception.
	Polynomial e;
	BOOST_CHECK_EXCEPTION((a / e), std::overflow_error, correctMessage);
}

BOOST_AUTO_TEST_CASE(unary_addition) 
{
	// Unary add a += b, now a = 14.0x^4 - 2.0x^2 + 6.0
	Polynomial a({ { 4, 7. }, { 2, -1. }, { 0, 3. } });
	Polynomial b({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial answer1({ { 4, 14. },{ 2, -2. },{ 0, 6. } });
	a += b;
	BOOST_CHECK(a == answer1);

	Polynomial c({ { 4, -14. },{ 2, 2. },{ 0, -6. } });
	Polynomial answer2;
	a += c;
	BOOST_CHECK(a == answer2);
}

BOOST_AUTO_TEST_CASE(unary_subtraction)
{
	// Unary subtract a -= b, now a = 7.0x^4 - 1.0x^2 + 3.0
	Polynomial a({ { 4, 14. }, { 2, -2. }, { 0, 6. } });
	Polynomial b({ { 4, 7. }, { 2, -1. }, { 0, 3. } });
	Polynomial answer1({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	a -= b;
	BOOST_CHECK(a == answer1);

	Polynomial c({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial answer2;
	a -= c;
	BOOST_CHECK(a == answer2);
}

BOOST_AUTO_TEST_CASE(unary_multiplication)
{
	// Unary multiply a *= b, now a = 98.0x^8 - 28.0x^6 + 86.0x^4 - 12.0x^2 + 18.0
	Polynomial a({ { 4, 14. }, { 2, -2. }, { 0, 6. } });
	Polynomial b({ { 4, 7. }, { 2, -1. }, { 0, 3. } });
	Polynomial answer({ { 8, 98. }, { 6, -28. }, { 4, 86. }, { 2, -12. }, { 0, 18. } });
	a *= b;
	BOOST_CHECK(a == answer);
}

BOOST_AUTO_TEST_CASE(unary_negate)
{
	// Unary negate.
	Polynomial a({ { 4, 14. }, { 2, -2. }, { 0, 6. } });
	Polynomial answer({ { 4, -14. }, { 2, 2. }, { 0, -6. } });
	BOOST_CHECK(answer == -a);
}

BOOST_AUTO_TEST_CASE(comparison)
{
	// Create unequal polynomials (a is larger).
	Polynomial a({ { 4, 14.1 }, { 2, -2. }, { 0, 6. } });
	Polynomial b({ { 4, 14. }, { 2, -2. }, { 0, 6. } });

	// Greater than or equal.
	BOOST_CHECK(a > b);
	BOOST_CHECK(a >= b);
	// Less than or equal.
	BOOST_CHECK(b < a);
	BOOST_CHECK(b <= a);
	// Set polynomials equal and test.
	a.setTerm(4, 14.);
	BOOST_CHECK(b <= a);
	BOOST_CHECK(a >= b);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
