//
// Created by Administrator on 2021-03-15.
//

#ifndef CORDELIA_DB_STRINGHANDLER_H
#define CORDELIA_DB_STRINGHANDLER_H

#include <vector>
#include <sstream>
#include <algorithm>

class StringHandler{
public:
    std::vector<std::string> tokenize_getline(const std::string& data, const char delimiter = ' ');
    std::vector<std::string> tokenize_getline_str(const std::string& data, const std::string delimiter = "");
    std::string erase_str(std::string s, std::string delimiter = "");
    std::string toLower(std::string s);
    std::string toUpper(std::string s);
};

std::vector<std::string> StringHandler::tokenize_getline(const std::string& data, const char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(data);

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

std::vector<std::string> StringHandler::tokenize_getline_str(const std::string& data, const std::string delimiter) {
    std::vector<std::string> result;
    std::string s = data;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);

    return result;
}

std::string StringHandler::erase_str(std::string s, std::string delimiter)
{
    int ds = delimiter.size();
    while(s.find(delimiter) != std::string::npos)
    {
        s.erase(s.find(delimiter), ds);
    }

    return s;
}

std::string StringHandler::toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

std::string StringHandler::toUpper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return s;
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    std::string str = rtrim(ltrim(s));
    str.erase(std::find(str.begin(), str.end(), '\0'), str.end()); // NULL indicator remove
    return str;
}

#endif //CORDELIA_DB_STRINGHANDLER_H
