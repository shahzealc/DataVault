#include <iostream>
#include <string>
#include <optional>
#include "Database.h"
#include "CommandParser.h"

int main() {
    Database db;
    CommandParser parser;

    std::cout << "MiniDB started. Type HELP for commands.\n";

    std::string line;

    while (true) {
        std::cout << "> ";

        if (!std::getline(std::cin, line))
            break;

        if (line.empty())
            continue;

        try {
            // Parse command
            auto cmdOpt = parser.parse(line);

            if (!cmdOpt) {
                std::cout << "Invalid command\n";
                continue;
            }

            const Command& cmd = *cmdOpt;

            // Exit command handled early
            if (cmd.type == CommandType::Exit) {
                std::cout << "Shutting down MiniDB...\n";
                break;
            }

            // Execute command
            auto result = db.execute(cmd);

            // Print result
            if (result.has_value())
                std::cout << *result << "\n";

        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << "\n";
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}
