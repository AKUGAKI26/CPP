#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>

int main()
{
	Data data;
	data.id = 42;
	data.label = "serialization";

	Data* original = &data;
	uintptr_t raw = Serializer::serialize(original);
	Data* restored = Serializer::deserialize(raw);

	std::cout << "original: " << original << "\n";
	std::cout << "restored: " << restored << "\n";
	std::cout << "same pointer: " << (original == restored ? "yes" : "no") << "\n";
	return original == restored ? 0 : 1;
}
