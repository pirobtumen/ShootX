#include <iostream>
#include "Vector.hpp"

int main(){

	Vector<int> vector;
	Vector<int> otro;

	vector.AddElement(5);

	otro = vector;
	otro.AddElement(6);

	std::cout << vector << std::endl;
	std::cout << otro << std::endl;

	std::cout << "Fin del programa." << std::endl;
}