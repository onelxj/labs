#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

class Analyst
{
public:
    Analyst() : checkRule(true){};
    Analyst(const std::string& str) : text(str), checkRule(true) {};
    ~Analyst() {};

    // methods

    void setText(const std::string& str)
    {
        variables.clear();
        text = str;
    }

    void analyse()
    {
        if (!checkRules())
        {
            checkRule = false;
            return;
        }

        std::vector<std::vector<std::string>> data = parseText(text);

        for (size_t i = 0; i < data.size(); i++)
        {
            for (size_t j = 0; j < data[i].size(); j++)
            {
                if (data[i][j].find("#name") != std::string::npos)
                {
                    data[i][j].erase(data[i][j].find("#name"));
                    variables.push_back(std::make_pair(data[i][j], type::PROC_NAME));
                    continue;
                }
                if (checkRoman(data[i][j]))
                {
                    variables.push_back(std::make_pair(data[i][j], type::ROMAN_NUM));
                    continue;
                }
                variables.push_back(std::make_pair(data[i][j], type::ID));
            }
        }
    }

    void save()
    {
        if (!checkRule)
        {
            return;
        }
        unsigned int countId = 1;
        std::map<std::string, unsigned int> data;

        std::ofstream file("result.xls");
        file << "Lexeme\t" << "Type\t" << "Value\r";

        for (const auto& x : variables)
        {
            file << x.first << "\t";
            switch (x.second)
            {
            case 1:
            {
                file << "PROCEDURE NAME\r";
                break;
            }
            case 2:
            {
                file << "ROMAN NUMERAL\t" << x.first << '\r';
                break;
            }
            case 3:
            {
                if (data.find(x.first) == data.end())
                {
                    data.insert(std::make_pair(x.first, countId++));
                }
                unsigned int localId = (*data.find(x.first)).second;

                file << "IDENTIFIER\t" << x.first << " : " << std::to_string(localId) << '\r';
                break;
            }
            default:
                break;
            }
        }
        file.close();
    }

private:

    bool checkRules()
    {
        unsigned int cLeft = std::count(text.begin(), text.end(), '(');
        unsigned int cRight = std::count(text.begin(), text.end(), ')');

        if (cLeft != cRight)
        {
            cLeft > cRight ? std::cout << "symbol ')' was expected!\n" : std::cout << "symbol '(' was expected!\n";
            return false;
        }

        for (size_t i = 0; i < text.size(); i++)
        {
            i = text.find(')', i);
            if (text[i + 1] != ';' && i != std::string::npos)
            {
                std::cout << "symbol ';' was expected!\n";
                return false;
            }
            if (i == std::string::npos)
            {
                break;
            }
        }
    }
    std::vector<std::vector<std::string>> parseText(std::string str)
    {
        std::vector<std::vector<std::string>> data;
        int lastPos = 0;
        int it = 0;
        bool last = false;

        if (std::count(str.begin(), str.end(), ';') == 0)
        {
            last = true;
        }

        while (!str.empty())
        {
            std::string proc = str.substr(0, str.find(';'));
            if (proc.empty())
            {
                proc = str.substr(lastPos, str.size());
            }
            lastPos = str.find(lastPos, ';');
            if (proc.empty())
            {
                return data;
            }

            std::string name = proc.substr(0, proc.find('('));
            proc.erase(proc.begin(), proc.begin() + proc.find('(') + 1);
            proc.pop_back();

            std::vector<std::string> params = parseParameters(proc);
            data.push_back(std::vector<std::string>());
            data[it].push_back(name + "#name");

            for (const auto& p : params)
            {
                data[it].push_back(p);
            }

            it++;
            str.erase(0, str.find(';') + 1);
            if (str.find(';') == std::string::npos)
            {
                if (last)
                {
                    break;
                }
                last = true;
            }
        }

        return data;
    }

    std::vector<std::string> parseParameters(std::string str)
    {
        std::vector<std::string> data;

        while (!str.empty())
        {
            std::string temp = str.substr(0, str.find(','));
            str.erase(0, str.find(',') + 1);
            data.push_back(temp);
            if (str.find(',') == std::string::npos)
            {
                data.push_back(str);
                break;
            }
        }

        return data;
    }

    bool checkRoman(const std::string& str)
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            if (str[i] != 'I' && str[i] != 'V' && str[i] != 'X' && str[i] != '+' && str[i] != '-')
            {
                return false;
            }
        }

        return true;
    }

    enum type
    {
        PROC_NAME = 1,
        ROMAN_NUM = 2,
        ID = 3
    };
    std::string text;
    std::vector<std::pair<std::string, type>> variables;
    bool checkRule;
};

int main()
{
    std::string text;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    Analyst obj(text);
    obj.analyse();
    obj.save();

    return 0;
}