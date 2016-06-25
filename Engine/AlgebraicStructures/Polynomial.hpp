#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <cstring>

//	TODO

namespace math {

	template <unsigned DEGREE>
	class Polynomial {

		template <unsigned DEGREE_>
		friend const Polynomial operator +(
			const Polynomial<DEGREE_>& op1, const Polynomial<DEGREE_>& op2);

		template <unsigned DEGREE_>
		friend const Polynomial operator -(
			const Polynomial<DEGREE_>& op1, const Polynomial<DEGREE_>& op2);

	public:

		static degree() {
			return DEGREE;
		}

		Polynomial() {
			memset(coefficients, 0, sizeof(coefficients));
		}

		Polynomial(float coefficients__[]) {
			copyCoefficients(coefficients__);
		}

		Polynomial(const Polynomial<DEGREE>& src) {
			copyCoefficients(src.coefficients);
		}

	private:

		inline void copyCoefficients(const coefficients__[]) {
			for (size_t i = 0; i < DEGREE; i++)
				this->coefficients[i] = coefficients__[i];
		}

		float coefficients[DEGREE];
	};

}
#endif
