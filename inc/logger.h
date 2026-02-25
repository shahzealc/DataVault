#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

class Logger
{
public:
    static Logger &getInstance()
    {
        static Logger instance;
        return instance;
    }
    void log(const std::string &message)
    {
        auto now{std::chrono::system_clock::now()};
        auto time{std::chrono::system_clock::to_time_t(now)};
        std::ofstream logFile(filename, std::ios::app);
        if (logFile.is_open())
        {
            std::string t = std::ctime(&time);
            t.pop_back(); // remove trailing newline
            logFile << t << ": " << message << '\n';
            logFile.close();
        }
    }

private:
    std::string filename{"logger.txt"};
    Logger() {}
    Logger(const Logger &) = delete;
    void operator=(const Logger &) = delete;
};
