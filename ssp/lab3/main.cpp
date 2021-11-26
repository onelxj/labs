#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> getFromFile(const std::string &fname)
{
    std::vector<int> data;
    std::ifstream file(fname);

    while (!file.eof())
    {
        int temp;
        file >> temp;
        data.push_back(temp);
    }

    file.close();

    return data;
}

void save(const std::vector<int> &data)
{
    std::ofstream file("out.txt");

    for (const auto &i : data)
    {
        file << std::to_string(i) << "\n";
    }

    file.close();
}

int main()
{

    std::cout << "1. Greater\n2. Less\n";
    int choice;
    std::cin >> choice;

    auto data = getFromFile("in.txt");
    std::sort(data.begin(), data.end());
    if (choice == 2)
    {
        std::reverse(data.begin(), data.end());
    }

    save(data);
    return 0;
}