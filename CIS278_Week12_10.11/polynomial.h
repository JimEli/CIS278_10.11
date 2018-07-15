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
*      evaluate and differentiate methods/operators added.
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
*   06/03/2018: Changed to templated class. JME
*************************************************************************/
#include <string>    // string
#include <iomanip>   // setprecision
#include <sstream>   // stringstream
#include <map>       // map for poly terms.
#include <numeric>   // accumulate
#include <algorithm> // for_each
#include <initializer_list>

#include "range_for_reverse_iterator.h"

template<typename T>
class Polynomial
{
private:
	// Polynomial terms contained in map in format of map<exponent, coefficient>.
	std::map<unsigned, T> terms;

	// Determines if a term exists for given exponent.
	bool exists(const unsigned& exponent) const;

	// Absolute value.
	T _abs(T);

	// Overload greater than operator, used for polynomial division.
	const bool operator> (Polynomial rhs)
	{
		if (_abs(evaluate(1)) > _abs(rhs.evaluate(1)))
			return true;

		return false;
	}

public:
	// Default constructor.
	Polynomial();
	// List initaializer constructor.
	Polynomial(std::initializer_list<std::pair<const unsigned, T> > init);
	// Default destructor.
	~Polynomial() = default;

	// Setter function for term.
	void setTerm(const unsigned exponent, const T coefficient);
	// Getter function for term coefficient.
	bool const getTerm(const unsigned exponent, T& coefficient);
	// Getter function for polynomial degree.
	unsigned const getDegree();

	// Evaluate polynomial at x.
	T evaluate(T x);
	// Differentiate polynomial and return result.
	Polynomial differentiate();

	// Return polynomial coefficient at exponent index.
	T operator[] (const int exponent) const
	{
		if (exponent < 0)
			throw std::out_of_range("Index < 0");
	
		return terms.at(exponent);
	}

	// Set polynomial coefficient at exponent index.
	T& operator[] (const int exponent)  
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
			[](std::map<unsigned, T>& t, const std::pair<const unsigned, T>& p)
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
			[](std::map<unsigned, T> &t, const std::pair<const unsigned, T> &p)
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

	// Divide polynomials via overloaded binary modulus operator.
	const Polynomial operator% (Polynomial& divisor)
	{
		// Check for division by zero.
		if (divisor.getDegree() == 0 && divisor[0] == T{ 0 })
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
		if (divisor.getDegree() == 0 && divisor[0] == T{ 0 })
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

	// Overloaded unary /= operator, passes to our "overloaded /".
	const Polynomial& operator/= (Polynomial rhs)
	{
		*this = *this / rhs;
		return *this;
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
					s += (t == *p.terms.rbegin()) ? (t.second < T{ 0 }) ? "-" : "" : (t.second > T{ 0 }) ? " + " : " - ";
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

// Default constructor.
template<typename T>
Polynomial<T>::Polynomial()
{
	// Empty polynomial.
	terms.clear();
}

// List initaializer constructor.
template<typename T>
Polynomial<T>::Polynomial(std::initializer_list<std::pair<const unsigned, T> > init) : terms(init) { }

// Determines if a term exists for exponent.
template<typename T>
bool Polynomial<T>::exists(const unsigned& exponent) const
{
	return terms.count(exponent);
}

// Setter function for term.
template<typename T>
void Polynomial<T>::setTerm(const unsigned exponent, const T coefficient)
{
	// Set or update an existing polynomial term.
	if (coefficient != T{ 0 })
		terms[exponent] += coefficient;
}

// Getter function for term coefficient.
template<typename T>
bool const Polynomial<T>::getTerm(const unsigned exponent, T& coefficient)
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
template<typename T>
unsigned const Polynomial<T>::getDegree()
{
	// Check for and remove any null terms.
	auto it = terms.begin();

	while (it != terms.end())
	{
		if ((*it).second == T{ 0 })
			it = terms.erase(it);
		else
			++it;
	}

	// Return highest degree or zero.
	if (!terms.empty())
		return terms.rbegin()->first;
	else
		return 0;
}

// Evaluate polynomial at x.
template<typename T>
T Polynomial<T>::evaluate(T x)
{
	T p{ 0 };

	for (auto t : terms)
		p += (pow(x, t.first) * t.second);

	return p;
}

// Differentiate polynomial and return result.
template<typename T>
Polynomial<T> Polynomial<T>::differentiate()
{
	Polynomial<T> derivative;
	unsigned degree = getDegree();

	if (degree == 0)
		return derivative;

	//derivative.degree = degree - 1;
	// Calculate by looping through all terms.
	for (unsigned i = 0; i < degree; i++)
		if (exists(i + 1))
			derivative.terms[i] = (i + 1) * terms[i + 1];

	return derivative;
}

template<typename T>
T Polynomial<T>::_abs(T x)
{
	if (x < T{ 0 })
		return x * T{ -1 };
	else
		return x;
}
