#include "utility.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
/*
Splits a string using the specified delimiter and returns the substrings as a vector. 
*/
std::vector<std::string> Utils::splitString(std::string s, std::string delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) 
    {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

void Utils::print(std::string str, bool newLine)
{
    std::cout << str;
    if (newLine) std::cout << std::endl;
}

bool Utils::promptInput(std::string infoText, std::string &inpStr, const std::vector<std::string> &validStrings)
{
    std::cout << infoText;
    std::cin >> inpStr;
    if (validStrings.size() > 0)
    {
        if (std::find(validStrings.begin(), validStrings.end(), inpStr) == validStrings.end())
        {
            std::cout << "'" + inpStr + "' is not valid.";
            return false;
        }
    }
    return true;
}

bool Utils::promptInteger(std::string infoText, int& inpInt, const std::vector<int>& validInts, int base, int minVal, int maxVal)
{
    std::string intStr;
    promptInput(infoText, intStr);
    try
    {
        inpInt = std::stoi(intStr, nullptr, base);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cout << "Invalid integer, try again!" << std::endl;
        return false;
    }
    catch (const std::out_of_range& oor)
    {
        std::cout << "Integer out of range, try again!" << std::endl;
        return false;
    }

    if (inpInt > maxVal || inpInt < minVal)
    {
        std::cout << "Integer not within valid range: [" + std::to_string(minVal) + ", " + std::to_string(maxVal) + "]"  << std::endl;
        return false;
    }

    if (validInts.size() > 0)
    {
        if (std::find(validInts.begin(), validInts.end(), inpInt) == validInts.end())
        {
            std::cout << "'" + std::to_string(inpInt) + "' is not valid.";
            return false;
        }
    }

    return true;
}

namespace Utils
{
    void Timer::start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    int64_t Timer::stop()
    {
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - m_start);
        m_elapsed = duration.count();
        
        return m_elapsed;
    }
}