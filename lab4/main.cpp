#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct LanguageHandler
{

    void setupDictionary()
    {
        getData("data_src/rus.txt", rus);
        getData("data_src/eng.txt", eng);
    }

    std::string getLanguage(const std::string &fname)
    {
        std::ifstream file(fname);

        size_t r = 0, e = 0;

        while (!file.eof())
        {
            std::string temp;
            file >> temp;

            for (const auto &c : temp)
            {
                if (rus.find(c) != std::string::npos)
                {
                    ++r;
                }
                else if (eng.find(c) != std::string::npos)
                {
                    ++e;
                }
            }
        }
        file.close();

        return e > r ? "English" : "Russian";
    }

    void getData(const std::string &fname, std::string &data)
    {
        std::ifstream file(fname);

        std::getline(file, data);

        file.close();
    }

    std::string rus;
    std::string eng;
};

int main()
{
    LanguageHandler lg;

    lg.setupDictionary();

    std::cout << lg.getLanguage("text.txt") << std::endl;

    return 0;
}