#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class table
{
public:
    table() {
        std::ifstream file("test.txt");
        while (!file.eof())
        {
            std::string temp;
            file >> temp;
            insertId(0, data.size(), temp);
        }

        file.close();
    };
    ~table() {};

    void print()
    {
        for (auto& x : data)
        {
            std::cout << "hash: " << x.first << "\n";
            for (auto& s : x.second)
            {
                std::cout << s << " ";
            }
            std::cout << "\n";
        }
    }
private:

    // methods

    unsigned int hash(const std::string& str)
    {
        return std::toupper(str[0]) + std::toupper(str[1]) + std::toupper(str[2]);
    }

    void insertId(size_t f, size_t l, const std::string& str)
    {
        unsigned int h = hash(str);
        int n = l - f;

        if (n == 1 || n == 0)
        {
            std::pair<unsigned int, std::vector<std::string>> newPair;
            newPair.second.push_back(str);
            newPair.first = h;

            if (n == 0)
            {
                data.push_back(newPair);
                return;
            }
            if (h == data[f].first)
            {
                data[f].second.push_back(str);
                return;
            }
            if (h < data[f].first)
            {                
                data.insert(data.begin() + f, newPair);
                return;
            }
            else
            {
                data.insert(data.begin() + f + 1, newPair);
                return;
            }
        }

        if (h == data[(l+f + 1) / 2].first)
        {
            data[(l+f + 1) / 2].second.push_back(str);
            return;
        }

        if (h < data[(l+f + 1) / 2].first)
        {
            return insertId(0, (l+f + 1) / 2, str);
        }
        else
        {
            return insertId((l + f) / 2, l, str);
        }
    }

    //variables

    std::vector<std::pair<unsigned int, std::vector<std::string>>> data;
};


int main()
{
    table obj;
    obj.print();
    return 0;
}