#include "../Platform.hpp"

#if PLAYGROUND_MAIN > 0

#include "../../Engine/Constants.hpp"

#include "../../Engine/AlgebraicStructures/Surface.hpp"
#include "../../Engine/AlgebraicStructures/Polynomial.hpp"
#include "../../Engine/AlgebraicStructures/Polynomial2.hpp"

#include "../../Core/MathStreams.hpp"

#include <iostream>

using namespace std;
using namespace math;

using Surf = math::Surface<Poly2<2>, Poly2<2>, Poly2<2>>;


int main() {
  Surf s({0, 1}, {1, -1,1,-1,-1,1,-1, 1,1}, {1, 0, 2, 1});
  cout << s << endl;
  getchar(); getchar();
}

#endif
