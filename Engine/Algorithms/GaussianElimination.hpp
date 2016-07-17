#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP

#include <vector>

#include "../../Engine/Constants.hpp"

namespace math {

	/*
		Gaussian elimination on lineary independent set.
	*/
	std::vector<double> GaussianElimination(std::vector<std::vector<double>> v);
}

#endif