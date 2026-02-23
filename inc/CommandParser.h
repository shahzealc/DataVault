#pragma once

#include <string>
#include <optional>
#include <algorithm>
#include "Command.h"

class CommandParser
{
public:
    std::optional<Command> parse(const std::string &line);
};

// Helper function to detect and convert value type
static std::variant<std::string, int, double, bool> parseValue(const std::string &value)
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

    // Check for boolean
    std::string lowerValue = value;
    std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    if (lowerValue == "true")
    {
        return true;
    }
    else if (lowerValue == "false")
    {
        return false;
    }

    // Default to string
    return value;
}
