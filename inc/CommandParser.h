#pragma once

#include <string>
#include <optional>
#include "Command.h"

class CommandParser{
public:
    std::optional<Command> parse(const std::string& line);
};
