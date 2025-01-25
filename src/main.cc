#include "Double.h"
#include "Int.h"
#include <iostream>

int main()
{
	try {
		Double n{10};
		Double m;

		std::cout << "n = " << n << '\n';

		m = n;

		std::cout << "m = " << m << '\n';
		return EXIT_SUCCESS;
	} catch (Object::exceptions exc) {
		switch (exc) {
		case Object::exceptions::NOT_MATCHING_TYPES:
			std::cerr << "NOT_MATCHING_TYPES\n";
			break;
		case Object::exceptions::FREAD_FAIL:
			std::cerr << "NOT_MATCHING_TYPES\n";
			break;
		case Object::exceptions::FWRITE_FAIL:
			std::cerr << "NOT_MATCHING_TYPES\n";
			break;
		}
		return EXIT_FAILURE;
	}
}
