#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <Windows.h>

struct Translator
{
	void SetUp(const std::string& path)
	{
		std::ifstream file(path);
		while (!file.eof())
		{
			std::string temp;
			std::getline(file, temp);
			size_t pos = temp.find('-');
			std::string rus = temp.substr(0, pos);
			std::string eng = temp.substr(pos + 1);
			re.insert({ rus, eng });
			er.insert({ eng, rus });
		}
		file.close();
	}

	std::string translate(const std::string& input, bool dir)
	{
		size_t pos = input.find(' ');
		size_t start = 0;
		std::string res;

		while (pos != std::string::npos)
		{
			if (dir)
				res += re.at(input.substr(start, pos - start)) + ' ';
			else
				res += er.at(input.substr(start, pos - start)) + ' ';

			start = pos + 1;
			pos = input.find(' ', start);
		}

		if (dir)
			res += re.at(input.substr(start, pos - start)) + ' ';
		else
			res += er.at(input.substr(start, pos - start)) + ' ';

		return res;
	}

	std::map<std::string, std::string> re;
	std::map<std::string, std::string> er;
};


int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Translator translator;

	translator.SetUp("dict.txt");

	std::string input;
	std::cout << "Enter text to translate: ";
	std::getline(std::cin, input);

	std::cout << translator.translate(input, true);

	return 0;
}