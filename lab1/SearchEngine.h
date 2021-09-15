#pragma once
#include <string>
#include <map>
#include <vector>

class SearchEngine
{
public:
	SearchEngine();

	std::map<double, std::string> search(const std::string& request);
	
private:

	void setupSearchConfig(const std::string& request);

	double B;
	size_t fileCount;
	std::string dataFolder_;
	std::vector<std::pair<std::string, int>> wordCount;
	std::map<double, std::string> result_;
};

