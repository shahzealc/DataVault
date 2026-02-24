#include "Database.h"
#include "Command.h"
#include <optional>
#include <string>
#include <stdexcept>

void Database::saveToFile()
{
    datastore.open("datastore.txt", std::ios::out | std::ios::trunc);
    if (datastore.is_open())
    {
        for (const auto &[key, value] : data)
        {
            if (std::holds_alternative<std::string>(value))
                datastore << key << "=" << std::get<std::string>(value) << "\n";
            else if (std::holds_alternative<int>(value))
                datastore << key << "=" << std::get<int>(value) << "\n";
            else if (std::holds_alternative<double>(value))
                datastore << key << "=" << std::get<double>(value) << "\n";
        }
        datastore.close();
    }
}

void Database::loadFromFile()
{
    datastore.open("datastore.txt", std::ios::in);
    if (datastore.is_open())
    {
        std::string line;
        while (std::getline(datastore, line))
        {
            auto delimPos = line.find('=');
            if (delimPos != std::string::npos)
            {
                std::string key = line.substr(0, delimPos);
                std::string value = line.substr(delimPos + 1);
                data[key] = parseValue(value);
            }
        }
        datastore.close();
    }
}

std::string Database::valueToString(const std::variant<std::string, int, double, bool> &val)
{
    if (std::holds_alternative<std::string>(val))
        return std::get<std::string>(val);
    else if (std::holds_alternative<int>(val))
        return std::to_string(std::get<int>(val));
    else if (std::holds_alternative<double>(val))
        return std::to_string(std::get<double>(val));
    else if (std::holds_alternative<bool>(val))
        return std::get<bool>(val) ? "true" : "false";
    return "";
}

Status Database::handleSet(const Command &cmd)
{
    data[cmd.getKey()] = cmd.getValue();
    return Status::Ok("Value set");
}

Status Database::handleGet(const Command &cmd)
{
    if (data.find(cmd.getKey()) != data.end())
    {
        return Status::Ok(valueToString(data[cmd.getKey()]));
    }
    return Status::Error("Key not found");
}

Status Database::handleDel(const Command &cmd)
{
    if (data.erase(cmd.getKey()) == 1)
        return Status::Ok("Deleted");
    return Status::Error("Key not found");
}

Status Database::handleCount(const Command &cmd)
{
    return Status::Ok(std::to_string(data.size()));
}

Status Database::handleList(const Command &cmd)
{
    std::string result = "\n";
    for (const auto &[key, value] : data)
    {
        result += key + " = " + valueToString(value) + "\n";
    }
    return Status::Ok(result.empty() ? "No entries" : result);
}

Status Database::handleType(const Command &cmd)
{
    if (data.find(cmd.getKey()) != data.end())
    {
        const auto &val = data[cmd.getKey()];
        if (std::holds_alternative<std::string>(val))
            return Status::Ok("string");
        else if (std::holds_alternative<int>(val))
            return Status::Ok("int");
        else if (std::holds_alternative<double>(val))
            return Status::Ok("double");
        else if (std::holds_alternative<bool>(val))
            return Status::Ok("bool");
    }
    return Status::Error("Key not found");
}

Status Database::handleExists(const Command &cmd)
{
    return data.find(cmd.getKey()) != data.end() ? Status::Ok("true") : Status::Ok("false");
}

Status Database::handleSearch(const Command &cmd)
{
    std::string result;
    for (const auto &[key, value] : data)
    {
        std::string valStr = valueToString(value);
        if (valStr.find(cmd.getKey()) != std::string::npos)
            result += "\n" + key + " = " + valStr;
    }
    return Status::Ok(result.empty() ? "No matches" : result);
}

Status Database::handleIncr(const Command &cmd)
{
    if (data.find(cmd.getKey()) != data.end())
    {
        auto &val = data[cmd.getKey()];
        if (std::holds_alternative<int>(val))
        {
            val = std::get<int>(val) + 1;
            return Status::Ok("Value incremented");
        }
        return Status::Error("Value is not an integer");
    }
    data[cmd.getKey()] = 1;
    return Status::Ok("Key created with value 1");
}

Status Database::handleDecr(const Command &cmd)
{
    if (data.find(cmd.getKey()) != data.end())
    {
        auto &val = data[cmd.getKey()];
        if (std::holds_alternative<int>(val))
        {
            val = std::get<int>(val) - 1;
            return Status::Ok("Value decremented");
        }
        return Status::Error("Value is not an integer");
    }
    data[cmd.getKey()] = -1;
    return Status::Ok("Key created with value -1");
}

Status Database::handleIncrBy(const Command &cmd)
{
    if (data.find(cmd.getKey()) != data.end())
    {
        auto &val = data[cmd.getKey()];
        if (std::holds_alternative<int>(val))
        {
            val = std::get<int>(val) + std::get<int>(cmd.getValue());
            return Status::Ok("Value incremented");
        }
        return Status::Error("Value is not an integer");
    }
    data[cmd.getKey()] = std::get<int>(cmd.getValue());
    return Status::Ok("Key created with value " + std::to_string(std::get<int>(cmd.getValue())));
}

Status Database::handleDecrBy(const Command &cmd)
{
    if (data.find(cmd.getKey()) != data.end())
    {
        auto &val = data[cmd.getKey()];
        if (std::holds_alternative<int>(val))
        {
            val = std::get<int>(val) - std::get<int>(cmd.getValue());
            return Status::Ok("Value decremented");
        }
        return Status::Error("Value is not an integer");
    }
    data[cmd.getKey()] = -std::get<int>(cmd.getValue());
    return Status::Ok("Key created with value " + std::to_string(-std::get<int>(cmd.getValue())));
}

Status Database::handleClear(const Command &cmd)
{
    data.clear();
    return Status::Ok("Database cleared");
}

Status Database::handleHelp(const Command &cmd)
{
    return Status::Ok("Commands: SET key value | GET key | DEL key | COUNT | LIST | TYPE key | EXISTS key | CLEAR | SEARCH key | INCR key | DECR key | INCRBY key value | DECRBY key value | HELP | EXIT");
}

Status Database::execute(const Command &cmd)
{
    static int commandCount = 0;
    if (commandCount % 5 == 0)
    {
        saveToFile();
    }

    ++commandCount;

    switch (cmd.getType())
    {
    case CommandType::SET:
        return handleSet(cmd);
    case CommandType::GET:
        return handleGet(cmd);
    case CommandType::DEL:
        return handleDel(cmd);
    case CommandType::COUNT:
        return handleCount(cmd);
    case CommandType::LIST:
        return handleList(cmd);
    case CommandType::TYPE:
        return handleType(cmd);
    case CommandType::EXISTS:
        return handleExists(cmd);
    case CommandType::SEARCH:
        return handleSearch(cmd);
    case CommandType::INCR:
        return handleIncr(cmd);
    case CommandType::DECR:
        return handleDecr(cmd);
    case CommandType::INCRBY:
        return handleIncrBy(cmd);
    case CommandType::DECRBY:
        return handleDecrBy(cmd);
    case CommandType::CLEAR:
        return handleClear(cmd);
    case CommandType::HELP:
        return handleHelp(cmd);
    default:
        throw std::runtime_error("Unsupported command");
    }
}
