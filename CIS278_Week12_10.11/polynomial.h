#include <iostream>  // cout/endl
#include <string>    // string
#include <iomanip>   // setprecision
#include <sstream>   // stringstream
#include <map>       // map for poly terms.
#include <numeric>   // accumulate
#include <algorithm> // for_each
#include <cmath>     // fabs
#include <initializer_list>

using namespace std;

class Polynomial
{
private:
	// Polynomial terms in format of map<exponent, coefficient>.
	map<unsigned, double> terms;

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
	Polynomial(initializer_list<pair<const unsigned, double>> init) : terms(init) { }

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
	Polynomial& operator= (const Polynomial& rhs) {
		// Check for self-assignment.
		if (this == &rhs)
			// Skip assignment, and just return *this.
			return *this;

		terms.clear();
		//setTerm(0, 0);
		for (auto t : rhs.terms)
			setTerm(t.first, t.second);
		degree = rhs.degree;

		return *this;
	}

	// Add polynomials via overloaded binary plus operator.
	Polynomial operator+ (Polynomial& b)
	{
		Polynomial result;

		for (auto t : this->terms)
			result.setTerm(t.first, t.second);

		result.terms = accumulate(b.terms.cbegin(), b.terms.cend(), result.terms,
			[](map<unsigned, double>& t, const pair<const unsigned, double>& p)
			{ return (t[p.first] += p.second, t); }
		);

		result.degree = result.getDegree();

		return result;
	}

	// Subtract polynomials via overloaded binary minus operator.
	Polynomial operator- (Polynomial& b)
	{
		Polynomial result;

		for (auto t : this->terms)
			result.setTerm(t.first, t.second);

		result.terms = accumulate(b.terms.cbegin(), b.terms.cend(), result.terms,
			[](map<unsigned, double> &t, const pair<const unsigned, double> &p)
			{ return (t[p.first] -= p.second, t); }
		);
		result.degree = result.getDegree();

		return result;
	}

	// Multiply Polynomials via overloaded binary multiplication operator.
	Polynomial operator* (Polynomial b)
	{
		Polynomial result;

		// Multiply all a terms by all b terms.
		for_each(this->terms.cbegin(), this->terms.cend(), [&result, b](auto aterm){
			for_each(b.terms.cbegin(), b.terms.cend(), [&result, aterm](auto bterm){
				result.terms[aterm.first + bterm.first] += (aterm.second * bterm.second);
			});
		});

		result.degree = result.getDegree();

		return result;
	}

	// Overloaded unary += operator.
	Polynomial operator+= (Polynomial& p)
	{
		*this = *this + p;
		return *this;
	}

	// Overloaded unary -= operator.
	Polynomial operator-= (Polynomial& p)
	{
		*this = *this - p;
		return *this;
	}

	// Overloaded unary *= operator.
	Polynomial operator*= (const Polynomial p)
	{
		*this = *this * p;
		return *this;
	}

	// Overloaded unary minus operator.
	Polynomial operator- ()
	{
		Polynomial p = *this;

		for (auto& t : p.terms)
			t.second = -t.second;

		return p;
	}

	// Stream polynomial.
	friend ostream& operator<< (ostream& os, const Polynomial& p)
	{
		string s{ "" };

		for (auto it = p.terms.rbegin(); it != p.terms.rend(); ++it) {
			unsigned exponent = it->first;
			double coefficient = it->second;
			stringstream stream;

			// Only terms with coefficients are printed.
			if (coefficient)
			{
				// Print leading sign except on first term.
				s += (coefficient > 0 ? (it == p.terms.rbegin() ? "" : " + ") : " - ");
				stream << fixed << setprecision(1) << abs(coefficient);
				// Skip exponents of 0.
				if (exponent)
					stream << "x^" << exponent;
				s += stream.str();
			}
		}

		return os << s;
	}
};

