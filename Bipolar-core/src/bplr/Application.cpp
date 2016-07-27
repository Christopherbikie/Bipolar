#define GLEW_STATIC

#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>

namespace bplr
{
	class Bipolar
	{
	public:
		std::string text = "From Application.cpp";

		Bipolar(std::string moreText)
		{
			std::cout << text << std::endl << moreText << std::endl;
		}
	};
}
