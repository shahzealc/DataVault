#include <string>

struct Status
{
    bool success;
    std::string message;

    static Status Ok()
    {
        return {true, "OK"};
    }

    static Status Ok(const std::string &msg)
    {
        return {true, msg};
    }

    static Status Error(const std::string &msg)
    {
        return {false, msg};
    }
};
