#include "CommandParser.h"
#include "Command.h"
#include <optional>
#include <string>
#include <sstream>
#include <variant>
#include <algorithm>

std::optional<Command> CommandParser::parse(const std::string &line)
{
    std::istringstream iss(line);   
    std::string cmdStr;
    iss >> cmdStr;

    std::transform(cmdStr.begin(), cmdStr.end(), cmdStr.begin(),
                   [](unsigned char c){ return std::toupper(c); });

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
