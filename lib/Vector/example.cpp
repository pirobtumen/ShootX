#include <iostream>
#include "Vector.hpp"

int main(){

	Vector<int> vector;
	Vector<int> otro;

	otro = vector;

	vector.AddElemento(5);
	otro.AddElemento(6);

	std::cout << vector << std::endl;
	std::cout << otro << std::endl;

	std::cout << "Fin del programa." << std::endl;
}