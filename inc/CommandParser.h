#pragma once

#include <string>
#include <optional>
#include "Command.h"

class CommandParser{
public:
    std::optional<Command> parse(const std::string& line);
};

// Helper function to detect and convert value type
static std::variant<std::string, int, double> parseValue(const std::string &value)
{
    try
    {
        // parse integer first
        size_t pos;
        int intVal = std::stoi(value, &pos);
        if (pos == value.length())
        {
            return intVal;
        }
    }
    catch (...)
    {
    }

    try
    {
        // parse as double
        size_t pos;
        double doubleVal = std::stod(value, &pos);
        if (pos == value.length())
        {
            return doubleVal;
        }
    }
    catch (...)
    {
    }

    // Default to string
    return value;
}
