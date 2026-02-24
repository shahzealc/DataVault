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
        data[cmd.getKey()] = cmd.getValue();
        return Status::Ok("Value set");
    case CommandType::GET:
        if (data.find(cmd.getKey()) != data.end())
        {
            const auto &val = data[cmd.getKey()];
            if (std::holds_alternative<std::string>(val))
                return Status::Ok(std::get<std::string>(val));
            else if (std::holds_alternative<int>(val))
                return Status::Ok(std::to_string(std::get<int>(val)));
            else if (std::holds_alternative<double>(val))
                return Status::Ok(std::to_string(std::get<double>(val)));
            else if (std::holds_alternative<bool>(val))
                return Status::Ok(std::get<bool>(val) ? "true" : "false");
        }
        return Status::Error("Key not found");
    case CommandType::DEL:
        data.erase(cmd.getKey()) == 1 ? Status::Ok("Deleted") : Status::Error("Key not found");
    case CommandType::COUNT:
        return Status::Ok(std::to_string(data.size()));
    case CommandType::LIST:
    {
        std::string result = "\n";
        for (const auto &[key, value] : data)
        {
            result += key + " = ";
            if (std::holds_alternative<std::string>(value))
                result += std::get<std::string>(value);
            else if (std::holds_alternative<int>(value))
                result += std::to_string(std::get<int>(value));
            else if (std::holds_alternative<double>(value))
                result += std::to_string(std::get<double>(value));
            else if (std::holds_alternative<bool>(value))
                result += std::get<bool>(value) ? "true" : "false";
            result += "\n";
        }
        return Status::Ok(result.empty() ? "No entries" : result);
    }
    case CommandType::TYPE:
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
    case CommandType::EXISTS:
        return data.find(cmd.getKey()) != data.end() ? Status::Ok("true") : Status::Ok("false");
    case CommandType::SEARCH:
    {
        std::string result;
        for (const auto &[key, value] : data)
        {
            if (std::holds_alternative<std::string>(value) && std::get<std::string>(value).find(cmd.getKey()) != std::string::npos)
                result += "\n" + key + " = " + std::get<std::string>(value);
            else if (std::holds_alternative<int>(value) && std::to_string(std::get<int>(value)).find(cmd.getKey()) != std::string::npos)
                result += "\n" + key + " = " + std::to_string(std::get<int>(value));
            else if (std::holds_alternative<double>(value) && std::to_string(std::get<double>(value)).find(cmd.getKey()) != std::string::npos)
                result += "\n" + key + " = " + std::to_string(std::get<double>(value));
        }
        return Status::Ok(result.empty() ? "No matches" : result);
    }
    case CommandType::CLEAR:
        data.clear();
        return Status::Ok("Database cleared");
    case CommandType::HELP:
        return Status::Ok("Commands: SET key value | GET key | DEL key | COUNT | LIST | TYPE key | EXISTS key | CLEAR | SEARCH key | HELP | EXIT");
    default:
        throw std::runtime_error("Unsupported command");
    }
}
