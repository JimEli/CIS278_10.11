/*************************************************************************
* Title: Polynomial Class
* File: polynomial.h
* Author: James Eli
* Date: 2/18/2018
*
* Exercise 10.11 on page 495-496, Polynomial Class
*
* Develop class Polynomial. The internal representation of a Polynomial is
* an array of terms. Each term contains a coefficient and an exponent—e.g.,
* the term:
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
*  (1) division, modulus, unary minus, [], comparison, stream and untested
*      evaluate and differentiate methods/operators added also.
*  (2) Compile release version if boost is not installed.
*  (3) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   02/18/2018: Initial release. JME
*   04/03/2018: Divided into .h & .cpp files. JME
*               Changed return value from getDegree() to unsigned. JME
*   04/12/2018: Added boost test file. JME
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

// Used to calculate poly evaluation for comparison operators.
static const double EVALUATION_CONSTANT{ 1.1 };

class Polynomial
{
private:
	// Polynomial terms contained in map in format of map<exponent, coefficient>.
	std::map<unsigned, double> terms;

	// Determines if a term exists for given exponent.
	bool exists(const unsigned& exponent) const;

public:

	// Default constructor.
	Polynomial();
	// List initaializer constructor.
	Polynomial(std::initializer_list<std::pair<const unsigned, double>> init);
	// Default destructor.
	~Polynomial() = default;

	// Setter function for term.
	void setTerm(const unsigned exponent, const double coefficient);
	// Getter function for term coefficient.
	bool const getTerm(const unsigned exponent, double& coefficient);
	// Getter function for polynomial degree.
	unsigned const getDegree();

	// Evaluate polynomial at x (used by comparison operations).
	double evaluate(double x);
	// Differentiate polynomial and return result.
	Polynomial differentiate();

	// Return polynomial coefficient at exponent index.
	double operator[] (const int exponent) const
	{
		if (exponent < 0)
			throw std::out_of_range("Index < 0");
	
		return terms.at(exponent);
	}

	// Set polynomial coefficient at exponent index.
	double& operator[] (const int exponent)  
	{
		if (exponent < 0)
			throw std::out_of_range("Index < 0");
		
		return terms[exponent];
	}

	// Overload assignment operator.
	const Polynomial& operator= (const Polynomial rhs)
	{
		// Check for self-assignment.
		if (this == &rhs)
			// Skip assignment, and just return *this.
			return *this;

		// Zeroize poly, and reassign this to rhs terms.
		terms.clear();

		for (auto t : rhs.terms)
			terms[t.first] = t.second;

		return *this;
	}

	// Add polynomials via overloaded binary plus operator.
	const Polynomial operator+ (const Polynomial rhs)
	{
		// Copy this's terms to result poly.
		Polynomial result = *this;

		// Use accumulator to add rhs to lhs terms. 
		result.terms = accumulate(rhs.terms.cbegin(), rhs.terms.cend(), result.terms,
			[](std::map<unsigned, double>& t, const std::pair<const unsigned, double>& p)
			{ 
				return (t[p.first] += p.second, t); 
			}
		);

		// Normalize polynomial.
		result.getDegree();

		return result;
	}

	// Subtract polynomials via overloaded binary minus operator.
	const Polynomial operator- (const Polynomial rhs)
	{
		// Copy this's terms to result poly.
		Polynomial result = *this;

		// Use accumulator to subtract rhs from lhs terms. 
		result.terms = accumulate(rhs.terms.cbegin(), rhs.terms.cend(), result.terms,
			[](std::map<unsigned, double> &t, const std::pair<const unsigned, double> &p)
			{ 
				return (t[p.first] -= p.second, t); 
			}
		);

		// Normalize polynomial.
		result.getDegree();

		return result;
	}

	// Multiply Polynomials via overloaded binary multiplication operator.
	const Polynomial operator* (const Polynomial rhs)
	{
		Polynomial result;

		// Multiply all lhs (or this) terms by all rhs terms.
		for_each(this->terms.cbegin(), this->terms.cend(), [&result, rhs](auto lhsTerm) 
		{
			for_each(rhs.terms.cbegin(), rhs.terms.cend(), [&result, lhsTerm](auto rhsTerm) 
			{
				result.terms[lhsTerm.first + rhsTerm.first] += (lhsTerm.second * rhsTerm.second);
			} );
		} );

		// Normalize polynomial.
		result.getDegree();

		return result;
	}

	// Overloaded unary += operator, passes our to "overloaded +".
	const Polynomial& operator+= (const Polynomial rhs)
	{
		*this = *this + rhs;
		return *this;
	}

	// Overloaded unary -= operator, passes our to "overloaded -".
	const Polynomial& operator-= (const Polynomial rhs)
	{
		*this = *this - rhs;
		return *this;
	}

	// Overloaded unary *= operator, passes to our "overloaded *".
	const Polynomial& operator*= (const Polynomial rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	// Overloaded unary minus operator.
	const Polynomial operator- ()
	{
		// Iterate through all terms negating them.
		for (auto& t : (*this).terms)
			t.second = -t.second;

		return *this;
	}

	// Overload equality operator.
	const bool operator== (Polynomial rhs)
	{
		if ((*this).getDegree() != rhs.getDegree())
			return false;

		// Iterate through all terms, check equal.
		for (auto& t : (*this).terms)
			// If coefficients don't match then fail.
			if (rhs[t.first] != t.second)
				return false;

		return true;
	}

	// Overload inequality operator.
	const bool operator!= (Polynomial rhs)
	{
		return !(*this == rhs);
	}

	// Overload greater than operator.
	const bool operator> (Polynomial rhs)
	{
		if (fabs(evaluate(EVALUATION_CONSTANT)) > fabs(rhs.evaluate(EVALUATION_CONSTANT)))
			return true;

		return false;
	}

	// Overload greater than or equal operator.
	const bool operator>= (Polynomial rhs)
	{
		if (fabs(evaluate(EVALUATION_CONSTANT)) >= fabs(rhs.evaluate(EVALUATION_CONSTANT)))
			return true;

		return false;
	}

	// Overload less than operator.
	const bool operator< (Polynomial rhs)
	{
		if (fabs(evaluate(EVALUATION_CONSTANT)) < fabs(rhs.evaluate(EVALUATION_CONSTANT)))
			return true;

		return false;
	}

	// Overload less than or equal operator.
	const bool operator<= (Polynomial rhs)
	{
		if (fabs(evaluate(EVALUATION_CONSTANT)) <= fabs(rhs.evaluate(EVALUATION_CONSTANT)))
			return true;

		return false;
	}

	// Divide polynomials via overloaded binary modulus operator.
	const Polynomial operator% (Polynomial& divisor)
	{
		// Check for division by zero.
		if (divisor.getDegree() == 0 && divisor[0] == 0)
			throw std::overflow_error("Divide by zero");

		// Preserve this.
		Polynomial dividend = *this;

		// Is divisor larger than dividend?
		if (divisor > dividend)
			// Return zero.
			return Polynomial();

		Polynomial quotient;

		// Iterate through all dividend terms.
		do {
			// Divide coefficients of highest terms, subtract exponents, insert as new quotient term.
			quotient[dividend.getDegree() - divisor.getDegree()] = dividend[dividend.getDegree()] / divisor[divisor.getDegree()];

			// Multiply divisor by quotient and subtract from dividend.
			dividend = *this - (divisor * quotient);

			// Repeat until reaching final term or divison is complete.
		} while ((dividend.getDegree() != 0) && (dividend.getDegree() >= divisor.getDegree()));

		// Normalize polynomial.
		dividend.getDegree();

		return dividend;
	}
	
	// Polynomial long division via overloaded binary divide operator.
	const Polynomial operator/ (Polynomial& divisor)
	{
		// Check for division by zero.
		if (divisor.getDegree() == 0 && divisor[0] == 0)
			throw std::overflow_error("Divide by zero");

		// Preserve this.
		Polynomial dividend = *this;

		// Is divisor larger than dividend?
		if (divisor > dividend)
			// Return zero.
			return Polynomial();

		Polynomial quotient;

		// Iterate through all dividend terms.
		do {
			// Divide coefficients of highest terms, subtract exponents, insert as new quotient term.
			quotient[dividend.getDegree() - divisor.getDegree()] = dividend[dividend.getDegree()] / divisor[divisor.getDegree()];

			// Multiply divisor by quotient and subtract from dividend.
			dividend = *this - (divisor * quotient);

			// Repeat until reaching final term or divison is complete.
		} while ((dividend.getDegree() != 0) && (dividend.getDegree() >= divisor.getDegree()));

		// Normalize polynomial.
		quotient.getDegree();

		return quotient;
	}

	// Stream polynomial.
	friend std::ostream& operator<< (std::ostream& os, const Polynomial& p)
	{
		// Loop, filling string with poly terms.
		std::string s{ "" };

		// Check for zero polynomial first.
		if (p.terms.empty())
			s = "0";
		else
		{
			// Iterate backwards through all terms.
			for (auto& t : reverse(p.terms))
			{
				// Only terms with coefficients are printed.
				if (t.second)
				{
					std::stringstream stream;

					// Print/format properly leading sign.
					s += (t == *p.terms.rbegin()) ? (t.second < 0) ? "-" : "" : (t.second > 0) ? " - " : " + ";
					stream << std::fixed << std::setprecision(1) << abs(t.second);
					// Skip display of superfluous 0 exponent.
					if (t.first)
						stream << "x^" << t.first;
					// Add to string.
					s += stream.str();
				}
			}
		}

		return os << s;
	}
};

