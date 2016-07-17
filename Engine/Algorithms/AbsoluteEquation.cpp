#include "AbsoluteEquation.hpp"


using namespace std;

namespace math {

	/*

		Helper function.
		For every subset, there exist a unique bitmask.
		If the bitmask bit for a given coefficient is 1 on current

	*/
	inline double sign(unsigned currentMask, unsigned coefficientIndex) {

		//	Remove bits for first 2 indexes.
		unsigned coefficientMask = (1 << coefficientIndex) / 4;
		if (currentMask & coefficientMask)
			return -1.0;
		return 1.0;
	}

	/*

		Complexity is logexponential, O(N * 2^N), where N is the coefficient number.

		Algorithm explanation:
		Generate all possible outcomes of a given equation.
		There are 2^(N - 2) of those (since zero-th coefficient is standing by x,
		and first coefficient is not altered).
		For all given version of equation, calculate x and insert it in set.
	*/

	set<double> solveAbsoluteEquationWithSingleX(const vector<double>& equation) {

		//	Generate all subsets of A that are different in sign of
		//	coefficients indexed at 2...N-1.
		size_t N = equation.size();

		set<double> solutions;

		unsigned numberOfSubsets = 1 << (N - 2);
		for (unsigned i = 0; i < numberOfSubsets; i++) {

			unsigned currentSubset = i;

			//	The x we're searching for.
			double solution = 0.0;

			for (unsigned j = 2; j < N; j++)
				solution += sign(i, j) * equation[j];

			//	First coefficient will remain with its original sign.
			//	Add its negative counterpart to both sides of equation,
			//	so x remains alone.
			solution -= equation[1];

			//	Divide both sides with inverse number of the first coefficient.
			//	What we have left, is explicit value for x.
			solution /= equation[0];

			solutions.insert(solution);
		}
		return solutions;
	}
}

/*
#include <iostream>

int main() {

	vector<double> eq = {1, -2, -3, 1};
	set<double> sol = math::solveAbsoluteEquationWithSingleX(eq);

	for (auto& it = sol.begin(); it != sol.end(); it++)
		cout << *it << " ";
	cout << endl;
	getchar();
}
*/
