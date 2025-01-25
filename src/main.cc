#include "Double.h"
#include "String.h"
#include <iostream>

int main()
{
	try {
		String st{"Sample text"};

		FILE * f = fopen ("test1", "wb");
		st.save(f);
		fclose(f);

		st = "del";
		std::cout << st << '\n';

		f = fopen ("test1", "rb");
		st.read(f);
		fclose(f);

		std::cout << st << '\n';

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
