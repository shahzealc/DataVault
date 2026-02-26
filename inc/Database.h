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
    std::unordered_map<std::string, std::variant<std::string, int, double, bool>> data;

    void saveToFile();
    void loadFromFile();
    
    // Command handlers
    Status handleSet(const Command &cmd);
    Status handleGet(const Command &cmd);
    Status handleDel(const Command &cmd);
    Status handleCount(const Command &cmd);
    Status handleList(const Command &cmd);
    Status handleType(const Command &cmd);
    Status handleExists(const Command &cmd);
    Status handleSearch(const Command &cmd);
    Status handleIncr(const Command &cmd);
    Status handleDecr(const Command &cmd);
    Status handleIncrBy(const Command &cmd);
    Status handleDecrBy(const Command &cmd);
    Status handleClear(const Command &cmd);
    Status handleHelp(const Command &cmd);
    Status handleAppend(const Command &cmd);
    Status handleRename(const Command &cmd);
    
    // Helper methods
    std::string valueToString(const std::variant<std::string, int, double, bool> &val);
};
