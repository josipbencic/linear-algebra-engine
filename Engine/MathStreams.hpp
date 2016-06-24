#ifndef MATH_STREAMS_HPP
#define MATH_STREAMS_HPP

#include "../Engine/AlgebraicStructures/Vec3.hpp"
#include "../Engine/AlgebraicStructures/RealCoordinateSpace.hpp"

#include <iostream>

//	TODO: Matrix i/o

namespace math {
	
	std::ostream& operator<< (std::ostream& stream, const vec3& v) {
		stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return stream;
	}

	template <unsigned DIM__>
	std::ostream& operator <<(
		std::ostream& stream, const RealCoordinateSpace<DIM__> vector) {

		stream << "(";
		for (size_t i = 0; i < DIM__ - 1; i++)
			stream << vector.coords[i] << ", ";
		stream << vector.coords[DIM__ - 1] << ")";
		return stream;
	}
}


#endif
