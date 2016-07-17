#ifndef MATH_STREAMS_HPP
#define MATH_STREAMS_HPP

#include "../Engine/AlgebraicStructures/RealCoordinateSpace.hpp"
#include "../Engine/AlgebraicStructures/Mat3.hpp"
#include "../Engine/AlgebraicStructures/Polynomial.hpp"

#include "../Engine/MathStreams.hpp"

#include <iostream>
#include <iomanip>
#include <string>

namespace math {

	inline std::ostream& operator <<(std::ostream& stream, const mat3& mat) {
		stream << '[';
		for (int i = 0; i < 3; i++) {
			stream << "  ";
			for (int j = 0; j < 3; j++)
				stream << std::fixed << std::setprecision(6)
					<< mat.data[i * 3 + j] << "  ";
			if (i < 2) stream << "\n";
		}
		stream << ']' << std::endl;
		return stream;
	}

	inline std::istream& operator >>(std::istream& stream, mat3& mat) {
		for (size_t i = 0; i < 9; i++)
			stream >> mat.data[i];
		return stream;
	}

	template <unsigned DIM__>
	inline std::ostream& operator <<(
		std::ostream& stream, const RealCoordinateSpace<DIM__>& vector) {

		stream << "(";
		for (size_t i = 0; i < DIM__ - 1; i++)
			stream << vector.coords[i] << ", ";
		stream << vector.coords[DIM__ - 1] << ")";
		return stream;
	}

	template <unsigned DIM__>
	inline std::istream& operator >>(std::istream& stream, RealCoordinateSpace<DIM__>& vector) {
		for (size_t i = 0; i < DIM__; i++)
			stream >> vector.coords[i];
		return stream;
	}

	template <unsigned DEGREE_>
	inline std::ostream& operator <<(std::ostream& stream, const Polynomial<DEGREE_>& p) {

		if (DEGREE_ == 0) {
			stream << p[0]; return stream;
		}

		if (p[DEGREE_] == 1.0)
			stream << "x^" << DEGREE_;
		else stream << p[DEGREE_] << "x^" << DEGREE_;

		static std::string plus = " + ", minus = " - ";

		for (size_t i = DEGREE_ - 1; i > 1; i--) {
			if (abs(p[i] - 1.0) < EPSILON) stream << plus << "x^" << i;
			else if (abs(p[i] + 1.0) < EPSILON) stream << minus << "x^" << i;
			else if (p[i] > EPSILON) stream << plus << p[i] << "x^" << i;
			else stream << minus << (-p[i]) << "x^" << i;
		}

		if (abs(p[1] - 1.0) < EPSILON) stream << plus << "x";
		else if (abs(p[1] + 1.0) < EPSILON) stream << minus << "x";
		else if (p[1] > EPSILON) stream << plus << p[1] << "x";
		else stream << minus << (-p[1]) << "x";
		
		if (p[0] > EPSILON) stream << plus << p[0];
		else stream << minus << (-p[0]);
		return stream;
	}

	template <unsigned DEGREE_>
	inline std::istream& operator >>(std::istream& stream, Polynomial<DEGREE_>& p) {
		for (size_t i = DEGREE_; i >= 0; i--)
			stream >> p[i];
		return stream;
	}
}


#endif
