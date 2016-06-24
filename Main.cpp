#include <iostream>
#include <vector>
#include <fstream>

#include "Engine/AlgebraicStructures/Mat3.hpp"
#include "Engine/AlgebraicStructures/RealCoordinateSpace.hpp"
#include "Engine/AlgebraicStructures/Vec3.hpp"
#include "Engine/Algorithms/GramSchmidt.hpp"
#include "Engine/MathStreams.hpp"

int main() {

	using namespace std;
	using namespace math;

	cout << "Linear Algebra Solver\n\n";
	cout << "This program operates through files."
		 << "Create your file, name it input.txt and put it in the program folder.\n";
	cout << "File has to contain:\n";
	cout << "Row\t\t\t Purpose\n";
	cout << 1 << "\t 1 for GramSchmidt orthogonalization or 2 for distance from subspace\n";
	cout << 2 << "\t 1 for 3x3 Matrices over Reals or 2,3,4,5 for Real Coordinate Space\n";
	cout << 3 << "\t number of vectors you will operate with\n";
	cout << 4 << "\t given vectors, each in its own line\n"
		 << "\t\t(matrices are entered row by row in the same line)\n";
	cout << 5 << "\t (subspace distance only) vector to evaluate\n";
	cout << endl << endl;

	std::vector<vec3> space3;
	std::vector<RealCoordinateSpace<4> > space4;
	std::vector<RealCoordinateSpace<5> > space5;

	unsigned decisions[3];
	ifstream input("Input/input.txt");
	if (!input.is_open()) {
		cout << endl << "ERROR::INPUT FILE:: Failed to find a file!" << endl;
		getchar();
		return 0;
	}

	input >> decisions[0];
	if (decisions[0] == 1) {

		input >> decisions[1];

		if (decisions[1] == 3) {
			input >> decisions[2];
			for (unsigned i = 0; i < decisions[2]; i++) {
				float x, y, z; input >> x >> y >> z;
				space3.push_back(vec3(x, y, z));
			}

			space3 = GramSchmidt(space3);
			cout << endl << "Result:" << endl << endl;
			for (unsigned i = 0; i < space3.size(); i++)
				cout << space3[i] << endl;
			cout << endl;
			getchar();
			return 0;
		}
		else if (decisions[1] == 4) {
			input >> decisions[2];
			for (unsigned i = 0; i < decisions[2]; i++) {
				float x[4]; input >> x[0] >> x[1] >> x[2] >> x[3];
				space4.push_back(RealCoordinateSpace<4>(x));
			}

			space4 = GramSchmidt(space4);
			cout << endl << "Result:" << endl;
			for (unsigned i = 0; i < space4.size(); i++)
				cout << space4[i] << endl;
			cout << endl;
			getchar();
			return 0;
		}
		else if (decisions[1] == 5) {

			input >> decisions[2];
			for (unsigned i = 0; i < decisions[2]; i++) {
				float x[5]; input >> x[0] >> x[1] >> x[2] >> x[3] >> x[4];
				space5.push_back(RealCoordinateSpace<5>(x));
			}

			space5 = GramSchmidt(space5);
			cout << endl << "Result:" << endl;
			for (unsigned i = 0; i < space5.size(); i++)
				cout << space5[i] << endl;
			cout << endl;
			getchar();
			return 0;
		}
		else {
			cout << "ERROR::INPUT FILE::File not formatted correctly!" << endl;
			return 0;
		}
	}
	else if (decisions[0] == 2) {

		input >> decisions[1];

		if (decisions[1] == 3) {
			input >> decisions[2];
			for (unsigned i = 0; i < decisions[2]; i++) {
				float x, y, z; input >> x >> y >> z;
				space3.push_back(vec3(x, y, z));
			}

			float x, y, z; input >> x >> y >> z;
			vec3 vect = vec3(x, y, z);
			float ans = distanceFromSpace(space3, vect);
			cout << "Distance from subspace result: " << "\n\t" << ans << endl;
			getchar();
			return 0;
		}
		else if (decisions[1] == 4) {
			input >> decisions[2];
			for (unsigned i = 0; i < decisions[2]; i++) {
				float x[4]; input >> x[0] >> x[1] >> x[2] >> x[3];
				space4.push_back(RealCoordinateSpace<4>(x));
			}
			float x[4]; input >> x[0] >> x[1] >> x[2] >> x[3];
			RealCoordinateSpace<4> vect(x);
			float ans = distanceFromSpace(space4, vect);
			cout << "Distance from subspace result: " << "\n\t" << ans << endl;
			getchar();
			return 0;
		}
		else if (decisions[1] == 5) {

			input >> decisions[2];
			for (unsigned i = 0; i < decisions[2]; i++) {
				float x[5]; input >> x[0] >> x[1] >> x[2] >> x[3] >> x[4];
				space5.push_back(RealCoordinateSpace<5>(x));
			}

			float x[5]; input >> x[0] >> x[1] >> x[2] >> x[3] >> x[4];
			RealCoordinateSpace<5> vect(x);
			float ans = distanceFromSpace(space5, vect);
			cout << "Distance from subspace result: " << "\n\t" << ans << endl;
			getchar();
			return 0;
		}
		else {
			cout << "ERROR::INPUT FILE::File not formatted correctly!" << endl;
			return 0;
		}
	}
	else {
		cout << "ERROR::INPUT FILE::File not formatted correctly!" << endl;
		return 0;
	}
}
