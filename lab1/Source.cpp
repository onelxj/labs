#include <iostream>
#include <string>
#include <Windows.h>

#include "SearchEngine.h"

int main()
{
	std::cout << "Search for: ";
	std::string request;
	std::getline(std::cin, request);

	SearchEngine engine;
	auto res = engine.search(request);

	std::cout << std::endl;

	int id = 1;
	for (const auto& x : res)
	{
		std::cout << id++ << ". " << x.second << std::endl;
	}

	return 0;
}

