#include <iostream>

#include "App.h"

int main(int argc, char** argv)
{
	std::cout << "Number of args: " << argc << std::endl;
	for (int i = 0; i < argc; i++)
		std::cout << "Arg " << i << ": " << argv[i] << std::endl;

	App app{};
	
	return app.Run();
}