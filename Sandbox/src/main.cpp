#include <iostream>
#include <string>
#include <Bipolar.h>

int main()
{
	std::cout << "Hello World";

	bplr::Bipolar engine = bplr::Bipolar(static_cast<std::string>("This was passed in the constructor"));

	system("PAUSE");

	return 0;
}
