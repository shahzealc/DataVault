#pragma once

#include <string>
#include <variant>
#include <optional>

enum CommandType
{
    SET,
    GET,
    DEL,
    COUNT,
    CLEAR,
    HELP,
    EXIT,
};

class Command
{
public:
    void setType(CommandType t) { type = t; }
    CommandType getType() const { return type; }
    void setKey(const std::string &k) { key = k; }
    const std::string &getKey() const { return key; }
    void setValue(const std::variant<std::string, int, double> &v) { value = v; }
    const std::variant<std::string, int, double> &getValue() const { return value; }

private:
    CommandType type;
    std::string key;
    std::variant<std::string, int, double> value;
};
