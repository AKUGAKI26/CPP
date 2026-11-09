#include "Base.hpp"

#include <cstdlib>
#include <iostream>

Base* generate(void)
{
	switch (std::rand() % 3)
	{
		case 0:
			return new A;
		case 1:
			return new B;
		default:
			return new C;
	}
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p) != 0)
		std::cout << "A\n";
	else if (dynamic_cast<B*>(p) != 0)
		std::cout << "B\n";
	else if (dynamic_cast<C*>(p) != 0)
		std::cout << "C\n";
	else
		std::cout << "Unknown\n";
}

void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A\n";
		return;
	}
	catch (...)
	{
	}
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B\n";
		return;
	}
	catch (...)
	{
	}
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C\n";
	}
	catch (...)
	{
		std::cout << "Unknown\n";
	}
}
