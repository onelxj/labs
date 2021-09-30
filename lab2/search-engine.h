#pragma once
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

struct SearchEngine
{
    SearchEngine() = default;

    void SetPath(const std::string& path)
    {
        path_ = path;
    }

    void Analyze()
    {
        std::ifstream file(path_);

        while (!file.eof())
        {
            std::string line;
            getline(file, line);

            if (line == "")
            {
                result_.push_back(local_);
                local_.clear();
                continue;
            }

            auto data = Parse(line);

            for (const auto& value : data)
            {
                if (!CheckWord(value))
                {
                    continue;
                }
                addValue(local_, value);
                addValue(stats_, value);
            }
        }

        key_word_ = GetMax(stats_).first;
        std::cout << key_word_ << "\n";
        for (const auto& value : result_)
        {
            std::cout << "\t" << GetMaxOther(value).first << "\n";
        }
    }

private:
    std::vector<std::string> Parse(const std::string& input)
    {
        std::vector<std::string> res;
        std::string word;

        for (size_t i = 0; i < input.size(); ++i)
        {
            if (isalpha(input[i]))
            {
                word += input[i];
            }

            if (input[i] == ' ')
            {
                res.push_back(word);
                word.clear();
            }
        }

        res.push_back(word);

        return res;
    }

    std::pair<std::string, size_t> GetMax(const std::map<std::string, size_t>& stats)
    {
        size_t max = 0;
        std::pair<std::string, size_t> local_max;

        for (const auto& value : stats)
        {
            if (value.second > max)
            {
                local_max = value;
                max = value.second;
            }
        }

        return local_max;
    }

    std::pair<std::string, size_t> GetMaxOther(const std::map<std::string, size_t>& stats)
    {
        size_t max = 0;
        std::pair<std::string, size_t> local_max;

        for (const auto& value : stats)
        {
            if (value.first == "" || value.first == key_word_)
                continue;
            if (value.second > max)
            {
                local_max = value;
                max = value.second;
            }
        }

        return local_max;
    }

    void addValue(std::map<std::string, size_t>& stats, const std::string& value)
    {
        auto it = std::find_if(stats.begin(), stats.end(), [&value](std::pair<std::string, size_t> p)
            { return p.first == value; });
        if (it != stats.cend())
        {
            ++it->second;
        }
        else
        {
            stats.insert({ value, 1 });
        }
    }

    bool CheckWord(const std::string& word)
    {
        return word != "and" && word != "a" && word != "the" && word != "of" && word != "is"
            && word != "for" && word != "to" && word != "on" && word != "or" && word != "in"
            && word != "that" && word != "as" && word != "are" && word != "such" && word != "have";
    }

    std::map<std::string, size_t> stats_;
    std::map<std::string, size_t> local_;
    std::vector<std::map<std::string, size_t>> result_;
    std::string path_;
    std::string key_word_;
};
