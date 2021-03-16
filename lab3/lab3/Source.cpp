#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <regex>

class Analyst
{
public:
    Analyst() : checkRule(true) {};
    Analyst(const std::string& str) : text(str), checkRule(true), regular((
        "(\\w*)"
        "([\(])"
        "([\\a-zIVX\,]+)"
        "([\)])"
        )) {};
    ~Analyst() {};

    // methods

    void setText(const std::string& str)
    {
        variables.clear();
        text = str;
    }

    void analyse()
    {
        if (!checkRulesAndParse())
        {
            checkRule = false;
            return;
        }
        
    }

    void save()
    {
        if (!checkRule)
        {
            std::cout << "[INFO] Error is in expression!\n";
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

        std::cout << "[INFO] File \"result.xls\" was successfully generated!\n";
    }

private:

    bool checkRulesAndParse()
    {
        std::vector<std::string> procs;

        while (std::count(text.begin(), text.end(), ';') != 0)
        {
            size_t pos = text.find(';');

            std::string temp = text.substr(0, pos);
            text.erase(0, pos + 1);
            procs.push_back(temp);
        }

        procs.push_back(text);

        std::cmatch res;

        std::cout << "\n\n";
        for (size_t i = 0; i < procs.size(); i++)
        {
            if (std::regex_match(procs[i].c_str(), res, regular))
            {
                variables.push_back(std::make_pair(res[1], type::PROC_NAME));

                std::vector<std::string> params;
                std::string strParams = res[3];

                size_t pos = 0;
                while ((pos = strParams.find(',')) != std::string::npos) {
                    std::string token = strParams.substr(0, pos);
                    params.push_back(token);
                    strParams.erase(0, pos + 1);
                }
                params.push_back(strParams);

                for (size_t j = 0; j < params.size(); j++)
                {
                    if (islower(params[j][0]))
                    {
                        variables.push_back(std::make_pair(params[j], type::ID));
                    }
                    else
                    {
                        variables.push_back(std::make_pair(params[j], type::ROMAN_NUM));
                    }
                }

            }
            else
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
    std::regex regular;
    bool checkRule;
};

int main()
{
    std::string text = "";
    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    Analyst obj(text);
    obj.analyse();
    obj.save();

    return 0;
}