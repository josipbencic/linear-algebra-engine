#include "InputManager.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace math;

template<typename VectorSpace>
inline int readFromStream(std::vector<VectorSpace>& space, stringstream& stream) {

	unsigned vectorNum;
	stream >> vectorNum;

	space.clear();
	space.reserve(vectorNum);
	for (size_t i = 0; i < vectorNum; i++)
		space.push_back(VectorSpace());

	for (size_t i = 0; i < vectorNum; i++) {
		if (!stream) {
			space.clear();
			return 1;
		}
		stream >> space[i];
	}
	return 0;
}

int readLinearSystemFromStream(std::vector<std::vector<double>> &linearSystem, stringstream& stream) {

	unsigned n;
	stream >> n;
	for (size_t i = 0; i < n; i++)
		linearSystem.push_back(std::vector<double>(n + 1, 0));

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n + 1; j++) {
			if (!stream) return 1;
			stream >> linearSystem[i][j];
		}
	return 0;
}

int InputManager::processInput(const char* fileName, Spaces space) {

	ifstream file(string("Input/") + string(fileName));
	if (!file.is_open())
		return 1;

	stringstream stream;
	stream << file.rdbuf();
	file.close();

	switch (space) {
	case Spaces::SPACE3:
		return readFromStream(space3, stream);
	case Spaces::SPACE4:
		return readFromStream(space4, stream);
	case Spaces::SPACE5:
		return readFromStream(space5, stream);
	case Spaces::MATRIXSPACE3:
		return readFromStream(matrixSpace3, stream);
	case Spaces::LINEARSYSTEM:
		return readLinearSystemFromStream(linearSystem, stream);
	}
	return 1;
}
