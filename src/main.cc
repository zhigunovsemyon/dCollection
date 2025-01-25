#include "object.h"
#include "Int.h"
#include <iostream>

int main()
{
	Int n{10};
	n.save(stdout);
	return 0;
}
