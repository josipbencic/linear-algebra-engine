#include "../Platform.hpp"

#if PLAYGROUND_MAIN > 0

#include "../../Core/Constants.hpp"
#include "../../Core/CommonFunctions.hpp"
#include "../../Core/MathStreams.hpp"

#include "../../AlgebraicStructures/Surface.hpp"
#include "../../AlgebraicStructures/Polynomial.hpp"
#include "../../AlgebraicStructures/Polynomial2.hpp"


#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace math;


void TestSurfaces() {
  using Surf = math::Surface<Poly2<2>, Poly2<2>, Poly2<2>>;
}


void testTrig(double from = -1000.0, double to = -1000.0, double inc = 1.0) {
  Sin<35, double> jsin;
  Cos<35, double> jcos;
  constexpr double eps = std::numeric_limits<double>::epsilon();

  for (double x = from; x < to; x += inc) {
    double canssin = sin(x);
    auto janssin = jsin(x);
    auto sindif = std::abs(canssin - janssin);

    double canscos = cos(x);
    auto janscos = jcos(x);
    auto cosdif = std::abs(canscos - janscos);

    cout << setprecision(10);
    if (sindif > eps) {
      cout << "Sin error at " << x << " by " << sindif << endl;
      if (sindif > 1.0) {
        cout << canssin << " " << janssin << endl;
      }
    }

    if (cosdif > eps) {
      cout << "Cos error at " << x << " by " << cosdif << endl;
      if (cosdif > 1.0) {
        cout << canscos << " " << janscos << endl;
      }
    }
  }
}

int main() {
  testTrig(rad(-90), rad(180), rad(3));
  getchar();
}
#endif
