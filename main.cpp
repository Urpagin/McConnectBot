#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "botcraft/Game/ConnectionClient.hpp"
#include "botcraft/Utilities/Logger.hpp"


struct Args {
    bool help = false;
    std::string address{};
    std::string login{};

    int return_code = 0;
};

struct InputArgs {
    int botNumber{};
    std::string address{};
    std::string loginPrefix{};
};

struct UserInstruction {
    int code{};
    std::string cmd_arg{};
    std::string raw{};

    void setCode(int num) {
        code = num;
        ++id;
    }

    unsigned long long id{0};
};


Args ParseCommandLine(int argc, char *argv[]);

int runClient(const Args &args);

UserInstruction instruction;

int main(int argc, char *argv[]) {
    InputArgs iArgs;
    while (!iArgs.botNumber && std::empty(iArgs.loginPrefix) && std::empty(iArgs.address)) {
        std::cout << "Info: there is a 5 second delay between each bot connection! (otherwise it won't work for some reason :/)\n" << std::endl;

        std::cout << "Number of bots (positive integer): ";
        std::cin >> iArgs.botNumber;

        std::cout << "MC Server address (<addr:port>): ";
        std::cin >> iArgs.address;

        std::cout << "Username prefix (then a count will be added at the end): ";
        std::cin >> iArgs.loginPrefix;
    }


    try {

        // well the code is shite, but it works, because I just rushed it. I'll rewrite it... someday.....
        std::vector<Args> args_vec;
        for (size_t i{0}; i < iArgs.botNumber; ++i) {
            Args arg_temp;
            arg_temp.address = iArgs.address;
            arg_temp.login = iArgs.loginPrefix + std::to_string(i);
            args_vec.emplace_back(arg_temp);
        }

        // Init logging, log everything >= Info, only to console, no file
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Info);
        Botcraft::Logger::GetInstance().SetFilename("");
        // Add a name to this thread for logging
        Botcraft::Logger::GetInstance().RegisterThread("main");

        for (const Args &a: args_vec) {
            std::thread(runClient, a).detach();
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        std::string helpStr =
                "Available Commands:\n"
                "  /disconnect - Disconnects all the bots\n"
                "  /exit       - Exits the program & disconnects all the bots\n"
                "  /say <msg>  - Sends <msg> in chat\n"
                "  /cmd <args>  - Sends the command with <args>\n"
                "  /help       - Displays this help message\n";

        std::cout << helpStr << std::endl;


        while (true) {
            std::cout << "$ ";
            std::getline(std::cin, instruction.raw);

            if (instruction.raw == "/exit") {
                break;
            } else if (instruction.raw == "/disconnect") {
                instruction.setCode(-1);
            } else if (instruction.raw.starts_with("/say ")) {
                size_t pos = instruction.raw.find("/say ");
                instruction.setCode(1);
                instruction.cmd_arg = instruction.raw.substr(pos + 5); // Skip "/say "

            } else if (instruction.raw.starts_with("/cmd ")) {
                size_t pos = instruction.raw.find("/cmd ");
                instruction.setCode(2);
                instruction.cmd_arg = instruction.raw.substr(pos + 5); // Skip "/cmd "

            } else if (instruction.raw == "/help") {
                std::cout << helpStr << std::endl; // Simply reprint the help string
            } else {
                std::cout << "Unknown command. Type \"/help\" for help." << std::endl;
            }
        }


        return 0;
    }
    catch (std::exception &e) {
        LOG_FATAL("Exception: " << e.what());
        return 1;
    }
    catch (...) {
        LOG_FATAL("Unknown exception");
        return 2;
    }
}

int runClient(const Args &args) {
    try {
        Botcraft::ConnectionClient client;
        LOG_INFO("Starting connection process");
        client.Connect(args.address, args.login);

        bool executed{false};
        // Arbitrary number, just has to be different from instruction.id
        unsigned long long executed_id{std::numeric_limits<unsigned long long>::max()};

        while (true) {
            // if id did not change, do nothing
            if (executed_id == instruction.id) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }
            executed_id = instruction.id;

            switch (instruction.code) {
                case -1:
                    client.Disconnect();
                    return 0;
                case 1:
                    client.SendChatMessage(instruction.cmd_arg);
                case 2:
                    client.SendChatCommand(instruction.cmd_arg);
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));
            //client.Disconnect();
        }
    }
    catch (std::exception &e) {
        LOG_FATAL("Exception: " << e.what());
        return 1;
    }
    catch (...) {
        LOG_FATAL("Unknown exception");
        return 2;
    }
}