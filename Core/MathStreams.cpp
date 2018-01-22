#include "MathStreams.hpp"

using namespace std;

int InputUtil::readLinearSystemFromStream(
  vector<vector<double>> &linearSystem, stringstream& stream) {

  size_t n;
  stream >> n;
  linearSystem.clear();
  linearSystem.resize(n, vector<double>(n + 1, 0.0));

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n + 1; j++) {
      if (!stream) {
        return 1;
      }
      stream >> linearSystem[i][j];
    }
  }
  return 0;
}

void OutputUtil::writeLinearSystemSolutionToStream(std::vector<double>& ret, std::ostream* stream) {
  std::ostream& out = *stream;

  out << "\t The result:\n\n";
  for (std::size_t i = 0; i < ret.size(); i++) {
    out << "\tx" << (i + 1) << " = " << ret[i] << "\n";
  }
  out << std::endl;
}

std::ostream& operator <<(std::ostream& stream, const math::M33& mat) {
  stream << '[';
  for (int i = 0; i < 3; i++) {
    stream << "  ";
    for (int j = 0; j < 3; j++) {
      stream << std::fixed << std::setprecision(6) << mat.data[i * 3 + j] << "  ";
    }
    if (i < 2) {
      stream << "\n";
    }
  }
  stream << ']' << std::endl;
  return stream;
}

std::istream& operator >>(std::istream& stream, math::M33& mat) {
  for (size_t i = 0; i < 9; i++) {
    stream >> mat.data[i];
  }
  return stream;
}
