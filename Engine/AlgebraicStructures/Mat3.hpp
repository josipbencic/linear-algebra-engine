#ifndef MAT3_HPP
#define MAT3_HPP

//	matrix vector multiplication
#include "../../Engine/AlgebraicStructures/Vec3.hpp"

#include <cmath>
#include <cstring>

namespace math {

	class mat3 {

		friend inline vec3 operator* (const mat3& mat, const vec3& vec);
		friend inline mat3 operator* (float alpha, const mat3& matrix);
		friend inline mat3 operator* (const mat3& matrix, float alpha);
		friend inline mat3 operator* (const mat3& left, const mat3& right);
		friend inline mat3 operator+ (const mat3& a, const mat3& b);
		friend inline mat3 operator- (const mat3& a, const mat3& b);

		friend inline mat3 transpose(const mat3& a);
		friend inline float trace(const mat3 &a);
		friend inline float scalar(const mat3 &a, const mat3 &b);

		//	angle HAS to between 0 and half Pi
		friend inline mat3 rotate(float angle_in_radians);
		friend inline mat3 translate(const vec3& vec);
		friend inline mat3 scale(const vec3& coeff);
		friend inline mat3 scale(float coeff);

	public:
		mat3() {
			memset(data, 0, sizeof(data));
		}

		mat3(const float matrix[][3]) {
			
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

		mat3(float x) {
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

			float norm = sqrt(scalar(*this, *this));
			for (unsigned i = 0; i < 9; i++)
				data[i] = data[i] / norm;

			return *this;
		}

		bool operator ==(const mat3& rhs) {
			bool ret = true;
			for (unsigned i = 0; i < 9; i++)
				ret = ret && (rhs.data[i] == data[i]);
			return ret;
		}

		float data[9];
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

	//	 TODO: edit last line if possible
	inline vec3 operator*(const mat3& mat, const vec3& vec) {
		return vec3(
			mat.data[0] * vec.x + mat.data[1] * vec.y + mat.data[2] * vec.z,
			mat.data[3] * vec.x + mat.data[4] * vec.y + mat.data[5] * vec.z,
			mat.data[6] * vec.x + mat.data[7] * vec.y + mat.data[8] * vec.z);
	}

	inline mat3 scale(float coeff) {
		mat3 ret;
		ret.data[0] = ret.data[4] = ret.data[8] = coeff;
		return ret;
	}

	inline mat3 scale(const vec3& coeff) {
		mat3 ret;
		ret.data[0] = coeff.x;
		ret.data[4] = coeff.y;
		ret.data[8] = 1;
		return ret;
	}

	inline mat3 translate(const vec3& vec) {
		mat3 ret;
		ret.data[2] = vec.x;
		ret.data[5] = vec.y;
		ret.data[8] = ret.data[4] = ret.data[0] = 1;
		return ret;
	}

	inline mat3 rotate(float angle) {
		float c = cos(angle);
		float s = sin(angle);
		mat3 ret;
		ret.data[0] = ret.data[4] = c;
		ret.data[1] = -s;
		ret.data[3] = s;
		ret.data[8] = 1;
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

	inline float trace(const mat3 &a) {
		return a.data[0] + a.data[4] + a.data[8];
	}

	inline float scalar(const mat3& a, const mat3& b) {
		return trace(a * transpose(b));
	}

	inline mat3 operator* (float alpha, const mat3& A) {
		mat3 ret = A;
		for (int i = 0; i < 9; i++)
			ret.data[i] *= alpha;
		return ret;
	}

	inline mat3 operator* (const mat3& A, float alpha) {
		return operator*(alpha, A);
	}
}

#endif