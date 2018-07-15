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
	//
	// Test with floating point.
	//

	// Create polynomial, 7x^4 - x^2 + 3.
	Polynomial<double> a;
	a.setTerm(4, 7.);
	a.setTerm(2, -1.);
	a.setTerm(0, 3.);

	// Create same polynomial with list initalizer.
	Polynomial<double> b({ { 4, 7. }, { 2, -1. }, { 0, 3. } });

	// Create polynomial using overloaded index operator.
	Polynomial<double> d;
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

	BOOST_CHECK_EQUAL(a[0], b[0]);

	BOOST_CHECK(a == d);
	BOOST_CHECK(a == b);
	BOOST_CHECK(!(a != b));

	// Check degree of polynomials.
	BOOST_CHECK_EQUAL(a.getDegree(), 4);
	BOOST_CHECK_EQUAL(b.getDegree(), 4);

	//
	// Test with integers...
	//
	
	// Create polynomial, 7x^4 - x^2 + 3.
	Polynomial<int> e;
	e.setTerm(4, 7);
	e.setTerm(2, -1);
	e.setTerm(0, 3);

	// Create same polynomial with list initalizer.
	Polynomial<int> f({ { 4, 7 },{ 2, -1 },{ 0, 3 } });

	// Create polynomial using overloaded index operator.
	Polynomial<int> h;
	h[4] = 7;
	h[2] = -1;
	h[0] = 3;

	// Polynomials equal?
	int g;

	e.getTerm(4, g);
	BOOST_CHECK_EQUAL(g, 7);
	f.getTerm(4, g);
	BOOST_CHECK_EQUAL(g, 7);

	e.getTerm(2, g);
	BOOST_CHECK_EQUAL(g, -1);
	f.getTerm(2, g);
	BOOST_CHECK_EQUAL(g, -1);

	BOOST_CHECK_EQUAL(e[0], f[0]);

	BOOST_CHECK(e == h);
	BOOST_CHECK(e == f);
	BOOST_CHECK(!(e != f));

	// Check degree of polynomials.
	BOOST_CHECK_EQUAL(e.getDegree(), 4);
	BOOST_CHECK_EQUAL(f.getDegree(), 4);
}

BOOST_AUTO_TEST_CASE(assignment)
{
	// Floating point.
	// Create polynomial, 7x^4 - x^2 + 3.
	Polynomial<double> a({ { 4, 7 },{ 2, -1 },{ 0, 3 } });
	Polynomial<double> b;
	// Check assignment
	b = a;
	BOOST_CHECK(a == b);

	// Integers.
	// Create polynomial, 7x^4 - x^2 + 3.
	Polynomial<int> c({ { 4, 7 },{ 2, -1 },{ 0, 3 } });
	Polynomial<int> d;
	// Check assignment
	d = c;
	BOOST_CHECK(c == d);
}

BOOST_AUTO_TEST_CASE(addition)
{
	// Floating point.
	// Add (7.0x^4 - 1.0x^2 + 3.0) + ( -3.0x^2 + 4.0) = 7.0x^4 - 4.0x^2 + 7.0
	Polynomial<double> a({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial<double> b({ { 2, -3. },{ 0, 4. } });
	Polynomial<double> answer1({ { 4, 7. },{ 2, -4. },{ 0, 7. } });
	BOOST_CHECK(answer1 == (a + b));

	// Add (7.0x^4 - 1.0x^2 + 3.0) + (-7.0x^4 + 4.0x^2 - 7.0) = 0
	Polynomial<double> c({ { 4, -7. },{ 2, 1. },{ 0, -3. } });
	Polynomial<double> answer2;
	BOOST_CHECK(answer2 == (a + c));

	// Integers.
	// Add (7x^4 - 1x^2 + 3) + ( -3x^2 + 4) = 7x^4 - 4x^2 + 7
	Polynomial<int> d({ { 4, 7 },{ 2, -1 },{ 0, 3 } });
	Polynomial<int> e({ { 2, -3 },{ 0, 4 } });
	Polynomial<int> answer3({ { 4, 7 },{ 2, -4 },{ 0, 7 } });
	BOOST_CHECK(answer3 == (d + e));

	// Add (7x^4 - 1x^2 + 3) + (-7x^4 + 4x^2 - 7) = 0
	Polynomial<int> f({ { 4, -7 },{ 2, 1 },{ 0, -3 } });
	Polynomial<int> answer4;
	BOOST_CHECK(answer4 == (d + f));
}

BOOST_AUTO_TEST_CASE(subtraction)
{
	// Floating point.
	// Subtract (7.0x^4 - 1.0x^2 + 3.0) - ( -3.0x^2 + 4.0) = 7.0x^4 + 2.0x^2 - 1.0
	Polynomial<double> a({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial<double> b({ { 2, -3. },{ 0, 4. } });
	Polynomial<double> answer1({ { 4, 7. },{ 2, 2. },{ 0, -1. } });
	BOOST_CHECK(answer1 == (a - b));

	// Subtract (7.0x^4 - 1.0x^2 + 3.0) - (7.0x^4 - 1.0x^2 + 3.0) = 0.0
	Polynomial<double> c({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial<double> answer2; answer2[0] = 0.;
	BOOST_CHECK(answer2 == (a - c));

	// Integers.
	// Subtract (7x^4 - 1x^2 + 3) - ( -3x^2 + 4) = 7x^4 + 2x^2 - 1
	Polynomial<int> d({ { 4, 7 },{ 2, -1 },{ 0, 3 } });
	Polynomial<int> e({ { 2, -3 },{ 0, 4 } });
	Polynomial<int> answer3({ { 4, 7 },{ 2, 2 },{ 0, -1 } });
	BOOST_CHECK(answer3 == (d - e));

	// Subtract (7x^4 - 1x^2 + 3) - (7x^4 - 1x^2 + 3) = 0
	Polynomial<int> f({ { 4, 7 },{ 2, -1 },{ 0, 3 } });
	Polynomial<int> answer4; answer4[0] = 0;
	BOOST_CHECK(answer4 == (d - f));
}

BOOST_AUTO_TEST_CASE(multiplication)
{
	// Floating point.
	// Multiplication (7.0x^4 - 1.0x^2 + 3.0) * ( -3.0x^2 + 4.0) = -21.0x^6 + 31.0x^4 - 13.0x^2 + 12.0
	Polynomial<double> a({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial<double> b({ { 2, -3. },{ 0, 4. } });
	Polynomial<double> answer1({ { 6, -21. },{ 4, 31. },{ 2, -13. },{ 0, 12. } });
	BOOST_CHECK(answer1 == (a * b));

	// Integers.
	// Multiplication (7x^4 - 1x^2 + 3) * ( -3x^2 + 4) = -21x^6 + 31x^4 - 13x^2 + 12
	Polynomial<double> c({ { 4, 7 },{ 2, -1 },{ 0, 3 } });
	Polynomial<double> d({ { 2, -3 },{ 0, 4 } });
	Polynomial<double> answer2({ { 6, -21 },{ 4, 31 },{ 2, -13 },{ 0, 12 } });
	BOOST_CHECK(answer2 == (c * d));
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
	Polynomial<double> a({ { 3, 1. }, { 2, -2. }, { 0, -4. } });
	Polynomial<double> b({ { 1, 1 }, { 0, -3 } });
	Polynomial<double> answer1({ { 2, 1. }, { 1, 1. }, { 0, 3. } });
	Polynomial<double> answer2({ { 0, 5. } });
	BOOST_CHECK(answer1 == (a / b));
	BOOST_CHECK(answer2 == (a % b));

	// Test division without remainder.
	Polynomial<double> c({ { 2, 1. }, { 1, 2. }, { 0, 2. } });
	Polynomial<double> d({ { 1, 1 }, { 0, 1 } });
	Polynomial<double> answer3({ { 1, 1. }, { 0, 1. } });
	Polynomial<double> answer4({ { 0, 0. } });
	BOOST_CHECK(answer3 == (c / d));
	BOOST_CHECK(answer4 == (c % d));

	// Test divide by zero exception.
	Polynomial<double> e;
	BOOST_CHECK_EXCEPTION((a / e), std::overflow_error, correctMessage);
}

BOOST_AUTO_TEST_CASE(unary_addition) 
{
	// Unary add a += b, now a = 14.0x^4 - 2.0x^2 + 6.0
	Polynomial<double> a({ { 4, 7. }, { 2, -1. }, { 0, 3. } });
	Polynomial<double> b({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial<double> answer1({ { 4, 14. },{ 2, -2. },{ 0, 6. } });
	a += b;
	BOOST_CHECK(a == answer1);

	Polynomial<double> c({ { 4, -14. },{ 2, 2. },{ 0, -6. } });
	Polynomial<double> answer2;
	a += c;
	BOOST_CHECK(a == answer2);
}

BOOST_AUTO_TEST_CASE(unary_subtraction)
{
	// Unary subtract a -= b, now a = 7.0x^4 - 1.0x^2 + 3.0
	Polynomial<double> a({ { 4, 14. }, { 2, -2. }, { 0, 6. } });
	Polynomial<double> b({ { 4, 7. }, { 2, -1. }, { 0, 3. } });
	Polynomial<double> answer1({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	a -= b;
	BOOST_CHECK(a == answer1);

	Polynomial<double> c({ { 4, 7. },{ 2, -1. },{ 0, 3. } });
	Polynomial<double> answer2;
	a -= c;
	BOOST_CHECK(a == answer2);
}

BOOST_AUTO_TEST_CASE(unary_multiplication)
{
	// Unary multiply a *= b, now a = 98.0x^8 - 28.0x^6 + 86.0x^4 - 12.0x^2 + 18.0
	Polynomial<double> a({ { 4, 14. }, { 2, -2. }, { 0, 6. } });
	Polynomial<double> b({ { 4, 7. }, { 2, -1. }, { 0, 3. } });
	Polynomial<double> answer({ { 8, 98. }, { 6, -28. }, { 4, 86. }, { 2, -12. }, { 0, 18. } });
	a *= b;
	BOOST_CHECK(a == answer);
}

BOOST_AUTO_TEST_CASE(unary_negate)
{
	// Unary negate.
	Polynomial<double> a({ { 4, 14. }, { 2, -2. }, { 0, 6. } });
	Polynomial<double> answer({ { 4, -14. }, { 2, 2. }, { 0, -6. } });
	BOOST_CHECK(answer == -a);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
