#ifndef INCLUDED_INTERPOLATION_HPP
#define INCLUDED_INTERPOLATION_HPP

#include <utility>
#include <vector>

/*  IP = Interpolation Polynomial
 */
namespace math {

class LagrangeIP {

  std::vector<double> A;
  std::vector<std::pair<double, double>> points;

public:
  LagrangeIP(const std::vector<std::pair<double, double>> &a);

  inline double operator()(double x) const { return Evaluate(x); }

private:
  void Precompute();
  double Evaluate(double x) const;
};

class NewtonIP {
public:
  std::vector<double> x;
  std::vector<double> f;

  NewtonIP(const std::vector<std::pair<double, double>> &a);

  inline double operator()(double x) const { return Evaluate(x); }

private:
  void Precompute();
  double Evaluate(double x) const;
};

//  TODO
struct InterpolationUtil {
  static double Horner(const std::vector<double> &a);
};

} // namespace math
#endif
