#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class table
{
public:
    table() {
        std::ifstream file("test.txt");
        while (!file.eof())
        {
            std::string temp;
            file >> temp;
            insertId(temp);
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

    int find(const std::string& str)
    {
        return find(0, data[hash(str)].size(), str);
    }

    void print(const std::string& str, int pos)
    {
        std::cout << "Hash: " << hash(str) << "\n";
        std::cout << data[hash(str)][pos] << "\n";
    }

    void remove(const std::string& str, int pos)
    {
        data[hash(str)].erase(data[hash(str)].begin() + pos);
        if (data[hash(str)].empty())
        {
            data.erase(data.find(hash(str)));
        }
    }
private:

    // methods

    int find(size_t f, size_t l, const std::string& str)
    {
        unsigned int h = hash(str);
        int n = l - f;

        if (str == data[h][0])
        {
            return 0;
        }

        if (str == data[h][(l + f + 1) / 2])
        {
            return (l + f + 1) / 2;
        }

        if (str < data[h][(l + f + 1) / 2])
        {
            return find(0, (l + f + 1) / 2, str);
        }
        else
        {
            return find((l + f) / 2, l, str);
        }
    }

    unsigned int hash(const std::string& str)
    {
        return std::toupper(str[0]) + std::toupper(str[1]) + std::toupper(str[2]);
    }

    void insertId(const std::string& str)
    {
        unsigned int h = hash(str);
        std::pair<unsigned int, std::vector<std::string>> newPair;
        newPair.second.push_back(str);
        newPair.first = h;

        if (data.find(h) == data.end())
        {
            data.insert(newPair);
            return;
        }
        
        (*data.find(h)).second.push_back(str);
        std::sort((*data.find(h)).second.begin(), (*data.find(h)).second.end());
    }

    //variables

    std::map<unsigned int, std::vector<std::string>> data;
};

int menu()
{
    system("pause");
    system("cls");
    int c;
    std::cout << "1. print\n2. find\n3. remove";
    std::cin >> c;
    system("cls");
    return c;
}

int main()
{
    table obj;
    int c = menu();
    while (true)
    {
        switch (c)
        {
        case 1:
        {
            obj.print();
            c = menu();
            break;
        }
        case 2:
        {
            std::string str;
            std::cout << "Enter string: ";
            std::cin >> str;
            int pos = obj.find(str);
            if (pos != -1)
            {
                obj.print(str, pos);
            }
            else
            {
                std::cout << "No such id!\n";
            }
            c = menu();
            break;
        }
        case 3:
        {
            std::string str;
            std::cout << "Enter string: ";
            std::cin >> str;
            int pos = obj.find(str);
            if (pos != -1)
            {
                obj.remove(str, pos);
            }
            else
            {
                std::cout << "No such id!\n";
            }
            c = menu();
            break;
        }
        default:
        {
            return 0;
        }
        }
    }
    return 0;
}