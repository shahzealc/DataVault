#include <CommandParser.h>
#include <Command.h>
#include <optional>
#include <string>
#include <sstream>
#include <variant>

// Helper function to detect and convert value type
static std::variant<std::string, int, double> parseValue(const std::string &value)
{
    try
    {
        // Try to parse as integer first
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
        // Try to parse as double
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

std::optional<Command> CommandParser::parse(const std::string &line)
{
    std::istringstream iss(line);
    std::string cmdStr;
    iss >> cmdStr;

    Command cmd;

    if (cmdStr == "SET")
    {
        cmd.setType(CommandType::SET);
        std::string key, value;
        iss >> key >> value;
        cmd.setKey(key);
        cmd.setValue(parseValue(value));
    }
    else if (cmdStr == "GET")
    {
        cmd.setType(CommandType::GET);
        std::string key;
        iss >> key;
        cmd.setKey(key);
    }
    else if (cmdStr == "DEL")
    {
        cmd.setType(CommandType::DEL);
        std::string key;
        iss >> key;
        cmd.setKey(key);
    }
    else if (cmdStr == "COUNT")
    {
        cmd.setType(CommandType::COUNT);
    }
    else if (cmdStr == "CLEAR")
    {
        cmd.setType(CommandType::CLEAR);
    }
    else if (cmdStr == "HELP")
    {
        cmd.setType(CommandType::HELP);
    }
    else if (cmdStr == "EXIT")
    {
        cmd.setType(CommandType::EXIT);
    }
    else
    {
        return std::nullopt;
    }

    return cmd;
}
