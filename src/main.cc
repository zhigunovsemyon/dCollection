#include "StudentList.h"
#include <iostream>
#include <fstream>

int main()
{
	try {
		StudentList list{};
		std::ifstream src{"test.src.txt"};
		src >> list;
		src.close();

		std::cout << "До:\n"<< list;
		list.SortStudentByMark5Desc();
		std::cout << "\nПосле:\n"<< list;

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
