#include "StudentList.h"
#include <iostream>

int main()
{
	try {
		StudentList list{};
		list.add(1, "Иванов", "Иван", "Иванович", 4, 2, 3, 4, 5);
		list.add(2, "Петров", "Пётр", "Петрович", 4, 4, 5, 4, 5);
		std::cin >> list;
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
