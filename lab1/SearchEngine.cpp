#include "SearchEngine.h"
#include <fstream>
#include <filesystem>
#include <iostream>

SearchEngine::SearchEngine() : B(0), fileCount(0)
{
	std::ifstream file("config.txt");
	std::getline(file, dataFolder_);
	file.close();
}

std::map<double, std::string> SearchEngine::search(const std::string& request)
{
	fileCount = 0;
	B = 0;
	result_.clear();
	wordCount.clear();

	setupSearchConfig(request);

	for (const auto& x : wordCount)
	{
		result_.insert({ B * x.second, x.first });
	}

	return result_;
}

void SearchEngine::setupSearchConfig(const std::string& request)
{
	for (const auto& dirPath : std::filesystem::recursive_directory_iterator(dataFolder_))
	{
		++fileCount;
		bool wordExists = false;
		size_t wordCountFile = 0;

		std::ifstream file(dirPath);

		while (!file.eof())
		{
			std::string word;
			file >> word;
			
			if (word.size() && !isalpha(word[word.size() - 1]))
			{
				word.pop_back();
			}
			if (word == request)
			{
				wordExists = true;
				++wordCountFile;
			}
		}
		file.close();

		if (wordExists)
		{
			wordCount.push_back({ dirPath.path().filename().string(), wordCountFile });
		}

	}

	B = log10((double)wordCount.size() / (double)fileCount);

}
