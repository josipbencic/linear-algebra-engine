#ifndef GRAM_SCHMIDT_HPP
#define GRAM_SCHMIDT_HPP

#include <cmath>
#include <vector>

namespace math {

/*
  Gram Schmidt orthogonalization algorithm for any set.
  Returns orthonormal basis for space that is spaned by given set.
  Note:
    If set is lineary dependant, the size of returned set will be smaller.

  Structure requirements:
    - Algorithm assumes that default ctor of given VectorSpace
      will produce null vector.
    - Defined scalar product and normalization function.
    - Arithmetic operators and scalar multiplication.
*/
template <typename VectorSpace>
::std::vector<VectorSpace> GramSchmidt(::std::vector<VectorSpace> set) {

  if (set.size() == 0)
    return set;

  //  The Orthonormal set returned by function
  ::std::vector<VectorSpace> ONS;
  ONS.push_back(set[0].normalize());
  for (::std::size_t i = 1; i < set.size(); i++) {

    //  Orthogonal projection of i-th vector on the subspace
    //  spanned by current orthonormal set
    VectorSpace orthoProj = VectorSpace();
    for (::std::size_t j = 0; j < ONS.size(); j++)
      orthoProj = orthoProj + inner_product(set[i], ONS[j]) * ONS[j];

    //  Vector orthogonal to every vector currently in ONS
    VectorSpace f = set[i] - orthoProj;

    /*
      If the set is lineary dependant, it spans less dimensions
      than there are vectors in it. It is known that in a given (sub)space,
      there can only be as many orthogonal vectors as there are dimensions.
      So at the certain step in algorithm, lineary dependant set will
      "run out" of orthogonal vectors, and our f will become 0 (0 is orthogonal
      to every vector and every (sub)space contains 0).
    */
    if (f == VectorSpace())
      return ONS;

    ONS.push_back(f.normalize());
  }
  return ONS;
}

/*
  Distance from some subspace can be obtained as norm of difference
  of vector and its orthogonal projection on the subspace.
  (Which is actually norm of orthogonal projection of that vector
  to orthogonal complement of that subspace).
*/
template <typename VectorSpace>
double distanceFromSpace(::std::vector<VectorSpace> space, VectorSpace vector) {

  //  GramSchmidt can handle lineary dependent sets
  space = GramSchmidt(space);

  // We will treat empty space as if it contains only null-vector
  if (space.size() == 0)
    return sqrt(inner_product(vector, vector));

  //  Another edge case: What if the subspace is actually whole space?
  //  GramSchmidt will produce basis for the whole space
  //  and orthogonal projection of vector on whole space will be vector itself.
  //  So norm of vector minus itself is zero.

  //  orthogonal projection of vector on the subspace
  //  obtained with Fourier coefficients
  VectorSpace orthoProj = VectorSpace();
  for (size_t i = 0; i < space.size(); i++)
    orthoProj = orthoProj + inner_product(vector, space[i]) * space[i];

  VectorSpace vec = vector - orthoProj;
  double s = inner_product(vec, vec);
  double ret = sqrt(s);
  return ret;
}
} // namespace math

#endif
