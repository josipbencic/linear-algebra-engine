#ifndef MATH_STREAMS_HPP
#define MATH_STREAMS_HPP

#include "../Engine/AlgebraicStructures/RealCoordinateSpace.hpp"
#include "../Engine/AlgebraicStructures/Mat3.hpp"
#include "../Engine/AlgebraicStructures/Polynomial.hpp"
#include "../Engine/AlgebraicStructures/Polynomial2.hpp"
#include "../Engine/AlgebraicStructures/Surface.hpp"

#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>

struct InputUtil {
  template<typename VectorSpace>
  static int readVectorSpaceInputFromStream(
    std::vector<VectorSpace>& space, std::stringstream& stream);

  static int readLinearSystemFromStream(
    std::vector<std::vector<double>> &linearSystem, std::stringstream& stream);
};

struct OutputUtil {

  template <typename VectorSpace>
  static void writeGramSchmidtSolutionToStream(std::vector<VectorSpace>& v, std::ostream* stream);

  template <typename VectorSpace>
  static void writeDistanceFromSubspaceSolutionToStream(
    std::vector<VectorSpace>& linearHull, std::ostream* stream);

  static void writeLinearSystemSolutionToStream(std::vector<double>& ret, std::ostream* stream);

  static void printMatrixScientific(std::vector<std::vector<double>>& M, std::ostream& stream);

};

std::istream& operator >>(std::istream& stream, math::M33& mat);

std::ostream& operator <<(std::ostream& stream, const math::M33& mat);

template <unsigned DIM__>
inline std::ostream& operator <<(std::ostream& stream, const math::Rn<DIM__>& vector);

template <unsigned DIM__>
inline std::istream& operator >>(std::istream& stream, math::Rn<DIM__>& vector);

template <unsigned DEGREE_>
inline std::ostream& operator <<(std::ostream& stream, const math::Polynomial<DEGREE_>& p);

template <unsigned DEGREE_>
inline std::istream& operator >>(std::istream& stream, math::Polynomial<DEGREE_>& p);

template <unsigned DEGREE_>
inline std::ostream& operator <<(std::ostream& stream, const math::Polynomial2<DEGREE_>& p);

template <unsigned DEGREE_>
inline std::istream& operator >>(std::istream& stream, math::Polynomial2<DEGREE_>& p);

template <typename F1, typename F2, typename F3>
inline std::ostream& operator <<(std::ostream& stream, const math::Surface<F1, F2, F3>& Phi);

template <typename F1, typename F2, typename F3>
inline std::istream& operator >>(std::istream& stream, math::Surface<F1, F2, F3>& Phi);

//  Implementation

template<typename VectorSpace>
int InputUtil::readVectorSpaceInputFromStream(std::vector<VectorSpace>& space, std::stringstream& stream) {
  unsigned vectorNum;
  stream >> vectorNum;

  space.clear();
  space.resize(vectorNum, VectorSpace());

  for (std::size_t i = 0; i < vectorNum; i++) {
    if (!stream) {
      space.clear();
      return 1;
    }
    stream >> space[i];
  }
  return 0;
}

template <typename VectorSpace>
void OutputUtil::writeGramSchmidtSolutionToStream(std::vector<VectorSpace>& v, std::ostream* stream) {
  std::ostream& out = *stream;
  out << "\n\t The result:\n\n";
  auto ret = math::GramSchmidt(v);
  for (auto& x : ret) {
    out << "\t" << x << "\n";
  }
}

template <typename VectorSpace>
void OutputUtil::writeDistanceFromSubspaceSolutionToStream(std::vector<VectorSpace>& linearHull, std::ostream* stream) {

  std::ostream& out = *stream;
  if (linearHull.empty()) {
    out << "The linear subspace has not been specified properly!" << std::endl;
    return;
  }
  VectorSpace v = linearHull[linearHull.size() - 1];
  linearHull.pop_back();
  double distance = distanceFromSpace(linearHull, v);
  out << "\n\t The distance is:\n\n";
  out << distance << std::endl;
}

template <unsigned DIM__>
inline std::ostream& operator <<(std::ostream& stream, const math::Rn<DIM__>& vector) {

  stream << "(";
  for (size_t i = 0; i < DIM__ - 1; i++) {
    stream << vector.component[i] << ", ";
  }
  return stream << vector.component[DIM__ - 1] << ")";
}

template <unsigned DIM__>
inline std::istream& operator >>(std::istream& stream, math::Rn<DIM__>& vector) {
  for (size_t i = 0; i < DIM__; i++) {
    stream >> vector.component[i];
  }
  return stream;
}

template <unsigned DEGREE_>
inline std::ostream& operator <<(std::ostream& stream, const math::Polynomial<DEGREE_>& p) {

  if (DEGREE_ == 0) {
    stream << p[0];
    return stream;
  }

  if (p[DEGREE_] == 1.0) {
    stream << "x^" << DEGREE_;
  }
  else {
    stream << p[DEGREE_] << "x^" << DEGREE_;
  }

  static std::string plus = " + ", minus = " - ";

  for (size_t i = DEGREE_ - 1; i > 1; i--) {
    if (abs(p[i] - 1.0) < math::EPSILON) stream << plus << "x^" << i;
    else if (abs(p[i] + 1.0) < math::EPSILON) stream << minus << "x^" << i;
    else if (p[i] > math::EPSILON) stream << plus << p[i] << "x^" << i;
    else stream << minus << (-p[i]) << "x^" << i;
  }

  if (abs(p[1] - 1.0) < math::EPSILON) stream << plus << "x";
  else if (abs(p[1] + 1.0) < math::EPSILON) stream << minus << "x";
  else if (p[1] > math::EPSILON) stream << plus << p[1] << "x";
  else stream << minus << (-p[1]) << "x";
    
  if (p[0] > math::EPSILON) stream << plus << p[0];
  else stream << minus << (-p[0]);
  return stream;
}

template <unsigned DEGREE_>
inline std::istream& operator >>(std::istream& stream, math::Polynomial<DEGREE_>& p) {
  for (size_t i = DEGREE_; i >= 0; i--) {
    stream >> p[i];
  }
  return stream;
}


/*  Pretty print operator for 2d polynomial.
*/
template <unsigned DEGREE_>
inline std::ostream& operator <<(std::ostream& stream, const math::Polynomial2<DEGREE_>& p) {
  tuple<size_t, size_t> start = { 0,0 };
  const tuple<size_t, size_t> last = { DEGREE_ + 1, DEGREE_ + 1 };

  for (size_t i = 0; i <= DEGREE_; i++) {
    for (size_t j = 0; j <= DEGREE_; j++) {
      const auto aij = p.coefficient[i][j];
      if (aij == 0) {
        if (start != last) {
          start = { i,j };
        }
        continue;
      }

      if (aij > 0) {
        if (start == last) {
          stream << " + ";
        }
        else {
          start = last;
        }
        if (aij != 1 || (i == 0 && j == 0)) {
          stream << aij;
        }
      }
      if (aij < 0) {
        stream << " - ";
        if (aij != -1 || (i == 0 && j == 0)) {
          stream << abs(aij);
        }
      }
      if (i > 0) {
        stream << "x";
        if (i > 1) {
          stream << i;
        }
      }
      if (j != 0) {
        stream << "y";
        if (j > 1) {
          stream << j;
        }
      }
    }
  }
  return stream;
}

template <unsigned DEGREE_>
inline std::istream& operator >>(std::istream& stream, math::Polynomial2<DEGREE_>& p) {
  for (size_t i = 0; i <= DEGREE_; i++) {
    for (size_t j = 0; j <= DEGREE_; j++) {
      stream >> p.coefficient[i][j];
    }
  }
  return stream;
}

template <typename F1, typename F2, typename F3>
inline std::ostream& operator <<(std::ostream& stream, const math::Surface<F1, F2, F3>& Phi) {
  return stream << "Phi(x,y) = (" << Phi.f1 << ", " << Phi.f2 << ", " << Phi.f3 << ")";
}

template <typename F1, typename F2, typename F3>
inline std::istream& operator >>(std::istream& stream, math::Surface<F1, F2, F3>& Phi) {
  return stream >> Phi.f1 >> Phi.f2 >> Phi.f3;
}


#endif
