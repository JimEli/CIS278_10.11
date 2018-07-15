/*************************************************************************
* Title: Polynomial Class 
* File: CIS278_Week12_10.11.cpp
* Author: James Eli
* Date: 2/18/2018
*
* Exercise 10.11 on page 495-496, Polynomial Class
*
* This is a short test of our polynomial class.
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
#if 0
#include <iostream>  // cout/endl

// Our polynomial class.
#include "polynomial.h"

using std::cout;
using std::endl;

int main()
{
	Polynomial<double> a;

	a.setTerm(2, 2.);
	a.setTerm(1, -2.);
	a.setTerm(0, 2.);

	Polynomial<double> b({ { 2, 3. },{ 1, 3. },{ 0, 3. } });

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "add: " << a + b << endl;
	cout << " multiply: " << a * b << endl;

	return 0;
}
#endif