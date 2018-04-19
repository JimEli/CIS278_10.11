#include "polynomial.h"

// Default constructor.
Polynomial::Polynomial()
{
	// Empty polynomial.
	terms.clear();
}

// List initaializer constructor.
Polynomial::Polynomial(std::initializer_list<std::pair<const unsigned, double>> init) : terms(init) { }

// Determines if a term exists for exponent.
bool Polynomial::exists(const unsigned& exponent) const
{
	return terms.count(exponent);
}

// Setter function for term.
void Polynomial::setTerm(const unsigned exponent, const double coefficient)
{
	// Set or update an existing polynomial term.
	if (coefficient != 0.)
		terms[exponent] += coefficient;
}

// Getter function for term coefficient.
bool const Polynomial::getTerm(const unsigned exponent, double& coefficient)
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
unsigned Polynomial::getDegree() 
{
	// Check for and remove any null terms.
	std::map<unsigned, double>::iterator it = terms.begin();
	while (it != terms.end()) 
	{
		if ((*it).second == 0.) 
			it = terms.erase(it);
		else 
			++it;
	}

	// Return highest degree.
	return terms.rbegin()->first;
}

// Evaluate polynomial at x.
double Polynomial::evaluate(double x)
{
	double p{ 0. };

	for (auto t : terms)
		p += (pow(x, t.first) * t.second);

	return p;
}

// Differentiate polynomial and return result.
Polynomial Polynomial::differentiate()
{
	Polynomial derivative;
	unsigned degree = getDegree();

	if (degree == 0)
		return derivative;

//	derivative.degree = degree - 1;
	// Calculate looping through all terms.
	for (unsigned i = 0; i < degree; i++)
		if (exists(i + 1))
			derivative.terms[i] = (i + 1) * terms[i + 1];
	
	return derivative;
}

