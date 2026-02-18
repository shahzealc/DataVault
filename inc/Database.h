#pragma once

#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include "Command.h"

class Database
{
public:
    std::optional<std::string> execute(const Command& cmd);
private:
    std::unordered_map<std::string, std::variant<std::string, int, double>> data;
};
