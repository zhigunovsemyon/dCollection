#include "Double.h"
#include "Int.h"
#include "object.h"
#include <iostream>

int main()
{
	try {
		Int n{10};
		Int m;

		std::FILE * f = fopen("test1", "wb");
		n.save(f);
		fclose(f);

		std::cout << "n = " << n << '\n';

		f = fopen("test1", "rb");
		m.read(f);
		fclose(f);

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
