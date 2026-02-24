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
        parseSet(iss, cmd);
    }
    else if (cmdStr == "GET")
    {
        parseGet(iss, cmd);
    }
    else if (cmdStr == "DEL")
    {
        parseDel(iss, cmd);
    }
    else if (cmdStr == "COUNT")
    {
        cmd.setType(CommandType::COUNT);
    }
    else if (cmdStr == "CLEAR")
    {
        cmd.setType(CommandType::CLEAR);
    }
    else if (cmdStr == "LIST")
    {
        cmd.setType(CommandType::LIST);
    }
    else if (cmdStr == "TYPE")
    {
        parseType(iss, cmd);
    }
    else if (cmdStr == "EXISTS")
    {
        parseExists(iss, cmd);
    }
    else if (cmdStr == "SEARCH")
    {
        parseSearch(iss, cmd);
    }
    else if (cmdStr == "INCR")
    {
        parseIncr(iss, cmd);
    }
    else if (cmdStr == "DECR")
    {
        parseDecr(iss, cmd);
    }
    else if (cmdStr == "INCRBY")
    {
        parseIncrBy(iss, cmd);
    }
    else if (cmdStr == "DECRBY")
    {
        parseDecrBy(iss, cmd);
    }
    else if(cmdStr == "APPEND")
    {
        parseAppend(iss, cmd);
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

void CommandParser::parseSet(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::SET);
    std::string key, value;
    iss >> key;
    std::getline(iss, value);
    cmd.setKey(key);
    cmd.setValue(parseValue(value));
}

void CommandParser::parseGet(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::GET);
    std::string key;
    iss >> key;
    cmd.setKey(key);
}

void CommandParser::parseDel(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::DEL);
    std::string key;
    iss >> key;
    cmd.setKey(key);
}

void CommandParser::parseType(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::TYPE);
    std::string key;
    iss >> key;
    cmd.setKey(key);
}

void CommandParser::parseExists(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::EXISTS);
    std::string key;
    iss >> key;
    cmd.setKey(key);
}

void CommandParser::parseSearch(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::SEARCH);
    std::string key;
    iss >> key;
    cmd.setKey(key);
}

void CommandParser::parseIncr(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::INCR);
    std::string key;
    iss >> key;
    cmd.setKey(key);
}

void CommandParser::parseDecr(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::DECR);
    std::string key;
    iss >> key;
    cmd.setKey(key);
}

void CommandParser::parseIncrBy(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::INCRBY);
    std::string key;
    int amount;
    iss >> key >> amount;
    cmd.setKey(key);
    cmd.setValue(amount);
}

void CommandParser::parseDecrBy(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::DECRBY);
    std::string key;
    int amount;
    iss >> key >> amount;
    cmd.setKey(key);
    cmd.setValue(amount);
}

void CommandParser::parseAppend(std::istringstream &iss, Command &cmd)
{
    cmd.setType(CommandType::APPEND);
    std::string key, value;
    iss >> key;
    std::getline(iss, value);
    cmd.setKey(key);
    cmd.setValue(parseValue(value));
}
