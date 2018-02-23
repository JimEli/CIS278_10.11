/*************************************************************************
* Title: Polynomial Class
* File: polynomial.h
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
#include <string>    // string
#include <iomanip>   // setprecision
#include <sstream>   // stringstream
#include <map>       // map for poly terms.
#include <numeric>   // accumulate
#include <algorithm> // for_each
#include <cmath>     // fabs
#include <initializer_list>

#include "range_for_reverse_iterator.h"

class Polynomial
{
private:
	// Polynomial terms in format of map<exponent, coefficient>.
	std::map<unsigned, double> terms;

	// degree of polynomial (0 for the zero polynomial).
	unsigned degree;

	// Determines if a term exists for exponent.
	bool exists(const unsigned& exponent)
	{
		return terms.count(exponent);
	}

public:

	// Default constructor.
	Polynomial()
	{
		// Empty polynomial.
		terms.clear();
		// Initialize as null polynomial.
		setTerm(0, 0);
		// No degree.
		degree = 0;
	}

	// List initaializer constructor.
	Polynomial(std::initializer_list<std::pair<const unsigned, double>> init) : terms(init)
	{
		// Init empty 0 term in polynomial.
		if (!exists(0))
			setTerm(0, 0.);
	}

	// Default destructor.
	~Polynomial() = default;

	// Setter function for term.
	void setTerm(unsigned exponent, double coefficient)
	{
		// Set or update an existing polynomial term.
		terms[exponent] += coefficient;

		// Update polynomial degree.
		if (exponent > degree)
			degree = exponent;
	}

	// Getter function for term coefficient.
	bool getTerm(unsigned exponent, double& coefficient)
	{
		// Get polynomial term if exists.
		if (exists(exponent))
		{
			coefficient = terms[exponent];
			return true;
		}

		return false;
	}

	// Getter function for polynomial degree.
	int getDegree()
	{
		return terms.rbegin()->first;
	}
/*
	// Uses Horner's method to calculate the polynomial evaluated at x.
	double evaluate(double x)
	{
		double p{ 0. };

		for (int i = degree; i >= 0; i--)
			if (exists(i))
				p = terms[i] + (x * p);
			else
				p = (x * p);
		// Old school method.
		//for (auto t : terms) p += (pow(x, t.first) * t.second);

		return p;
	}

	// Differentiate polynomial and return result.
	Polynomial differentiate()
	{
		Polynomial derivative;

		if (degree == 0)
			return derivative;

		derivative.degree = degree - 1;
		// Calculate looping through all terms.
		for (unsigned i = 0; i < degree; i++)
			if (exists(i + 1))
				derivative.terms[i] = (i + 1) * terms[i + 1];

		return derivative;
	}
*/
	// Overload assignment operator.
	Polynomial& operator= (const Polynomial rhs) {
		// Check for self-assignment.
		if (this == &rhs)
			// Skip assignment, and just return *this.
			return *this;

		// Zeroize poly, and reassign this to rhs terms.
		terms.clear();
		setTerm(0, 0);

		for (auto t : rhs.terms)
			setTerm(t.first, t.second);
		
		degree = rhs.degree;

		return *this;
	}

	// Add polynomials via overloaded binary plus operator.
	Polynomial operator+ (Polynomial rhs)
	{
		// Copy this's terms to result poly.
		Polynomial result = *this;

		// Use accumulator to add rhs to lhs terms. 
		result.terms = accumulate(rhs.terms.cbegin(), rhs.terms.cend(), result.terms,
			[](std::map<unsigned, double>& t, const std::pair<const unsigned, double>& p)
			{ return (t[p.first] += p.second, t); }
		);

		// Set poly result's degree.
		result.degree = result.getDegree();

		return result;
	}

	// Subtract polynomials via overloaded binary minus operator.
	Polynomial operator- (Polynomial rhs)
	{
		// Copy this's terms to result poly.
		Polynomial result = *this;

		// Use accumulator to subtract rhs from lhs terms. 
		result.terms = accumulate(rhs.terms.cbegin(), rhs.terms.cend(), result.terms,
			[](std::map<unsigned, double> &t, const std::pair<const unsigned, double> &p)
			{ return (t[p.first] -= p.second, t); }
		);

		// Set poly result's degree.
		result.degree = result.getDegree();

		return result;
	}

	// Multiply Polynomials via overloaded binary multiplication operator.
	Polynomial operator* (Polynomial rhs)
	{
		Polynomial result;

		// Multiply all lhs (or this) terms by all rhs terms.
		for_each(this->terms.cbegin(), this->terms.cend(), [&result, rhs](auto lhsTerm){
			for_each(rhs.terms.cbegin(), rhs.terms.cend(), [&result, lhsTerm](auto rhsTerm){
				result.terms[lhsTerm.first + rhsTerm.first] += (lhsTerm.second * rhsTerm.second);
			});
		});

		// Set polynomial result's degree.
		result.degree = result.getDegree();

		return result;
	}

	// Overloaded unary += operator, passes to our "overloaded +".
	Polynomial& operator+= (Polynomial p)
	{
		*this = *this + p;
		return *this;
	}

	// Overloaded unary -= operator, passes to our "overloaded -".
	Polynomial& operator-= (Polynomial p)
	{
		*this = *this - p;
		return *this;
	}

	// Overloaded unary *= operator, passes to our "overloaded *".
	Polynomial& operator*= (const Polynomial p)
	{
		*this = *this * p;
		return *this;
	}

	// Overloaded unary minus operator.
	Polynomial operator- ()
	{
		Polynomial p = *this;

		// Iterate through all terms negating them.
		for (auto& t : p.terms)
			t.second = -t.second;

		return p;
	}

	// Stream polynomial.
	friend std::ostream& operator<< (std::ostream& os, const Polynomial& p)
	{
		// Loop, filling string with poly terms.
		std::string s{ "" };

		// Iterate backwards through all terms.
		for (auto& t : reverse(p.terms))
		{
			// Only terms with coefficients are printed.
			if (t.second)
			{
				std::stringstream stream;

				// Print leading sign except on first term.
				s += (t.second > 0 ? (t == *p.terms.rbegin() ? "" : " + ") : " - ");
				stream << std::fixed << std::setprecision(1) << abs(t.second);
				// Skip display of superfluous 0 exponent?
				if (t.first)
					stream << "x^" << t.first;
				// Add to string.
				s += stream.str();
			}
		}

		return os << s;
	}
};
