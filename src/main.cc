#include "StudentList.h"
#include <iostream>

int main()
{
	try {
		StudentList list{};
		list.add(1, "Строуструп", "Бьярн", "", 1, 2, 3, 4, 5);
		std::cout << list;
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
