#include "StudentList.h"
#include <iostream>
#include <fstream>

int main()
{
	try {
		StudentList list{};
		std::ifstream src {"test1.txt"};
		src >> list;
		src.close();
		// list.add(1, "Иванов", "Иван", "Иванович", 4, 2, 3, 4, 5);
		// list.add(2, "Петров", "Пётр", "Петрович", 4, 4, 5, 4, 5);

		std::cout << list;

		std::ofstream out{"test1.txt"};
		out << list;
		out.close();

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
