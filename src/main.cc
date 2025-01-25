#include "object.h"
#include "Int.h"
#include "Double.h"
#include <iostream>
#include <string_view>

int main()
{
	Object *a{}, *b{};

	std::cout << "Тип a -- Int или Double (i|d)? ";
	switch (getchar()) {
	case 'D':
	case 'd':
		a = new Double();
		break;
	case 'I':
	case 'i':
		a = new Int();
		break;
	default:
		std::cerr << "Неправильный ввод!\n";
		return 0;
	}
	std::cout << "Значение a: ";
	std::cin >> *a;

	std::cout << "Тип b -- Int или Double (i|d)? ";
	while (getchar() != '\n')
		;
	switch (getchar()) {
	case 'D':
	case 'd':
		b = new Double();
		break;
	case 'I':
	case 'i':
		b = new Int();
		break;
	default:
		std::cerr << "Неправильный ввод!\n";
		delete a;
		return 0;
	}
	std::cout << "Значение b: ";
	std::cin >> *b;

	std::cout << "a: " << "id = " << a->id() //
		  << ", type: " << a->type()	 //
		  << ", value: " << *a << '\n';

	std::cout << "b: " << "id = " << b->id() //
		  << ", type: " << b->type()	 //
		  << ", value: " << *b << '\n';

	try {
		std::cout << std::boolalpha;
		std::cout << "a != b : " << (*a != *b) << '\n';
		std::cout << "a >= b : " << (*a >= *b) << '\n';
		std::cout << "a <= b : " << (*a <= *b) << '\n';

		std::cout << "\na+=b\n";
		*a += *b;
		std::cout << "a: " << "id = " << a->id() //
			  << ", type: " << a->type()	 //
			  << ", value: " << *a << '\n';
		delete a;
		delete b;
		return 0;
	} catch (Object::exceptions exc) {
		switch (exc) {
		case Object::exceptions::NOT_MATCHING_DERIVED:
			std::cerr << "\n!!Error: NOT_MATCHING_DERIVED!!\n";
		}
		delete a;
		delete b;
		return -1;
	}
}
