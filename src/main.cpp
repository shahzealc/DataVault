#include <iostream>
#include <string>
#include <optional>
#include "Database.h"
#include "CommandParser.h"
#include "Command.h"

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

            if (!cmdOpt.has_value()) {
                std::cout << "Invalid command\n";
                continue;
            }

            const Command& cmd {cmdOpt.value()};

            if (cmd.getType() == CommandType::EXIT) {
                std::cout << "Shutting down MiniDB...\n";
                break;
            }

            // Execute command
            auto result = db.execute(cmd);

            std::cout << (result.success ? "Success: " : "Error: ") << result.message << "\n";

        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << "\n";
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}
