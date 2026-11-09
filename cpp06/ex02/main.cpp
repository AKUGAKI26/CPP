#include "Base.hpp"

#include <cstdlib>
#include <iostream>

int main()
{
	std::srand(42);
	for (int i = 0; i < 5; ++i)
	{
		Base* object = generate();
		std::cout << "pointer: ";
		identify(object);
		std::cout << "reference: ";
		identify(*object);
		delete object;
	}
	return 0;
}
