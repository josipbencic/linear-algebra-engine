#ifndef MAT3_HPP
#define MAT3_HPP

//	matrix vector multiplication
#include "../../Engine/Constants.hpp"

#include <cmath>
#include <cstring>

namespace math {

	class mat3 {

		//	TODO: MATRIX - VECTOR MULTIPLICATION
		//friend inline vec3 operator* (const mat3& mat, const vec3& vec);

		friend inline mat3 operator* (double alpha, const mat3& matrix);
		friend inline mat3 operator* (const mat3& matrix, double alpha);
		friend inline mat3 operator* (const mat3& left, const mat3& right);
		friend inline mat3 operator+ (const mat3& a, const mat3& b);
		friend inline mat3 operator- (const mat3& a, const mat3& b);

		friend inline mat3 transpose(const mat3& a);
		friend inline double trace(const mat3 &a);
		friend inline double scalar(const mat3 &a, const mat3 &b);

	public:
		mat3() {
			memset(data, 0, sizeof(data));
		}

		mat3(const double matrix[][3]) {
			
			data[0] = matrix[0][0];
			data[1] = matrix[0][1];
			data[2] = matrix[0][2];
			data[3] = matrix[1][0];
			data[4] = matrix[1][1];
			data[5] = matrix[1][2];
			data[6] = matrix[2][0];
			data[7] = matrix[2][1];
			data[8] = matrix[2][2];
		}

		mat3(double x) {
			for (unsigned i = 0; i < 9; i++)
				data[i] = 0;
			data[0] = data[4] = data[8] = x;
		}

		mat3(const mat3& src) {
			for (unsigned i = 0; i < 9; i++)
				data[i] = src.data[i];
		}

		mat3& operator= (const mat3& rhs) {
			for (unsigned i = 0; i < 9; i++)
				data[i] = rhs.data[i];
			return *this;
		}

		mat3 operator -() {

			mat3 ret;
			for (unsigned i = 0; i < 9; i++)
				ret.data[i] = 0 - data[i];
			return ret;
		}
		
		const mat3& normalize() {

			double norm = sqrt(scalar(*this, *this));
			for (unsigned i = 0; i < 9; i++)
				data[i] = data[i] / norm;

			return *this;
		}

		bool operator ==(const mat3& rhs) {
			bool ret = true;
			for (unsigned i = 0; i < 9; i++)
				ret = ret && (abs(rhs.data[i] - data[i]) < EPSILON);
			return ret;
		}

		double data[9];
	};

	inline mat3 operator-(const mat3& a, const mat3& b) {
		mat3 ret;
		for (unsigned i = 0; i < 9; i++)
			ret.data[i] = a.data[i] - b.data[i];
		return ret;
	}

	inline mat3 operator+(const mat3& a, const mat3& b) {
		mat3 ret;
		for (unsigned i = 0; i < 9; i++)
			ret.data[i] = a.data[i] + b.data[i];
		return ret;
	}

	inline mat3 operator*(const mat3& left, const mat3& right) {
		mat3 ret;
		for (unsigned i = 0; i < 3; i++)
			for (unsigned j = 0; j < 3; j++)
				for (unsigned k = 0; k < 3; k++)
					ret.data[i * 3 + j] += left.data[i * 3 + k] * right.data[k * 3 + j];
		return ret;
	}
	
	inline mat3 transpose(const mat3 &a) {

		mat3 ret = a;
		ret.data[1] = a.data[3];
		ret.data[3] = a.data[1];
		ret.data[2] = a.data[6];
		ret.data[6] = a.data[2];
		ret.data[5] = a.data[7];
		ret.data[7] = a.data[5];
		return ret;
	}

	inline double trace(const mat3 &a) {
		return a.data[0] + a.data[4] + a.data[8];
	}

	inline double scalar(const mat3& a, const mat3& b) {
		return trace(a * transpose(b));
	}

	inline mat3 operator* (double alpha, const mat3& A) {
		mat3 ret = A;
		for (int i = 0; i < 9; i++)
			ret.data[i] *= alpha;
		return ret;
	}

	inline mat3 operator* (const mat3& A, double alpha) {
		return operator*(alpha, A);
	}
}

#endif