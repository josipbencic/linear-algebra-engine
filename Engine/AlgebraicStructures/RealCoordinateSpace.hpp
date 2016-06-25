#ifndef REALCOORDINATESPACE_HPP
#define REALCOORDINATESPACE_HPP

namespace math {

	template <unsigned DIMENSION>
	class RealCoordinateSpace {

		friend RealCoordinateSpace<DIMENSION>
			operator +(
				const RealCoordinateSpace<DIMENSION> &op1,
				const RealCoordinateSpace<DIMENSION> &op2) {

			RealCoordinateSpace<DIMENSION> ret;
			for (size_t i = 0; i < DIMENSION; i++)
				ret.coords[i] = op1.coords[i] + op2.coords[i];
			return ret;
		}

		friend RealCoordinateSpace<DIMENSION>
			operator -(
				const RealCoordinateSpace<DIMENSION> &op1,
				const RealCoordinateSpace<DIMENSION> &op2) {

			RealCoordinateSpace<DIMENSION> ret;
			for (size_t i = 0; i < DIMENSION; i++)
				ret.coords[i] = op1.coords[i] - op2.coords[i];
			return ret;
		}

		friend double scalar(
			const RealCoordinateSpace<DIMENSION> &op1,
			const RealCoordinateSpace<DIMENSION> &op2) {

			double ret = 0.0f;
			for (size_t i = 0; i < DIMENSION; i++)
				ret += op1.coords[i] * op2.coords[i];
			return ret;
		}

		friend RealCoordinateSpace<DIMENSION>
			operator *(
				double alpha, const RealCoordinateSpace<DIMENSION> &op) {

			RealCoordinateSpace<DIMENSION> ret;
			for (size_t i = 0; i < DIMENSION; i++)
				ret.coords[i] = alpha * op.coords[i];
			return ret;

		}

		friend RealCoordinateSpace<DIMENSION>
			operator *(
				const RealCoordinateSpace<DIMENSION> &op, double alpha) {
			return alpha * op;
		}

	public:

		RealCoordinateSpace() {
			memset(coords, 0, sizeof(coords));
		}

		RealCoordinateSpace(const RealCoordinateSpace<DIMENSION> &src) {
			copyCoords(src.coords);
		}

		RealCoordinateSpace(const double newCoords[]) {
			copyCoords(newCoords);
		}

		const RealCoordinateSpace<DIMENSION>
			operator -() {
			RealCoordinateSpace<DIMENSION> ret;
			for (size_t i = 0; i < DIMENSION; i++)
				ret.coords[i] = 0 - coords[i];
			return ret;
		}

		bool operator ==(const RealCoordinateSpace<DIMENSION>& rhs) {

			bool ret = true;
			for (size_t i = 0; i < DIMENSION; i++)
				ret = ret && (abs(coords[i] - rhs.coords[i]) < EPSILON);
			return ret;
		}

		RealCoordinateSpace<DIMENSION>&
			normalize() {

			//	cannot divide by zero!
			if (*this == RealCoordinateSpace<DIMENSION>())
				return *this;

			double norm = sqrt(scalar(*this, *this));
			for (size_t i = 0; i < DIMENSION; i++)
				coords[i] = coords[i] / norm;
			
			return *this;
		}

		inline void copyCoords(const double newCoords[]) {
			for (size_t i = 0; i < DIMENSION; i++)
				coords[i] = newCoords[i];
		}

		double coords[DIMENSION];
	};
}

#endif
