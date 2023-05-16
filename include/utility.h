#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>
#include <climits>
#include <chrono>

namespace Utils
{
    std::vector<std::string> splitString(std::string s, std::string delimiter);
    void print(std::string str, bool newLine=true);
    bool promptInput(std::string infoText, std::string& inpStr, const std::vector<std::string>& validStrings={});
    bool promptInteger(std::string infoText, int& inpInt, const std::vector<int>& validInts={}, int base=10, int minVal=INT32_MIN, int maxVal=INT32_MAX);
} // Utils

namespace Utils
{
    class Timer
    {
        public:
            Timer() = default;
            void start();
            int64_t stop();
        private:
            std::chrono::_V2::system_clock::time_point m_start;
            int64_t m_elapsed;
    };
}

#endif /* UTILITY_H */
