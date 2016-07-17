#ifndef ABSOLUTE_EQUATION
#define ABSOLUTE_EQUATION

#include <vector>
#include <set>

namespace math {

	/*
		Solve absolute equations with single appearance of x.
		Coefficients are laid out from left to right in following way:

		|| .. ||A0x + A1| + A2| ... | + AN-1| = AN
	*/
	std::set<double> solveAbsoluteEquationWithSingleX(const std::vector<double>& equation);

	/*
		TODO.

		Return value will be std::set<double>.
	*/
	void solveAbsoluteEquationWithMultipleX(const std::vector<double>& equation) {}
}

#endif