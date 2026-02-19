#pragma once

#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include <fstream>
#include "Command.h"
#include "CommandParser.h"
#include "Status.h"

class Database
{
public:
    Database()
    {
        loadFromFile();
    }
    ~Database()
    {
        saveToFile();
    }

    Status execute(const Command &cmd);

private:
    std::fstream datastore;
    std::unordered_map<std::string, std::variant<std::string, int, double>> data;

    void saveToFile();
    void loadFromFile();
};
