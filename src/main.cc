#include "Int.h"
#include "Double.h"
#include <iostream>

int main()
{
	Double n{10};
	std::cout << n.read(stdin) << std::endl;
	return 0;
}
