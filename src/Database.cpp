#include "inc/Database.h"
#include "inc/Command.h"
#include <optional>
#include <string>
#include <stdexcept>

std::optional<std::string> Database::execute(const Command &cmd)
{
    switch (cmd.getType())
    {
    case CommandType::SET:
        data[cmd.getKey()] = cmd.getValue();
        return "OK";
    case CommandType::GET:
        if (data.find(cmd.getKey()) != data.end())
        {
            const auto &val = data[cmd.getKey()];
            if (std::holds_alternative<std::string>(val))
                return std::get<std::string>(val);
            else if (std::holds_alternative<int>(val))
                return std::to_string(std::get<int>(val));
            else if (std::holds_alternative<double>(val))
                return std::to_string(std::get<double>(val));
        }
        return "NULL";
    case CommandType::DEL:
        data.erase(cmd.getKey());
        return "OK";
    case CommandType::COUNT:
        return std::to_string(data.size());
    case CommandType::CLEAR:
        data.clear();
        return "OK";
    default:
        throw std::runtime_error("Unsupported command");
    }
}
