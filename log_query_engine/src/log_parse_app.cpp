#include "log_parse_app.h"
#include "simple_log_parser.h"
// our very first parser
#include <iostream>
#include <limits>
#include <memory>
#include <utility>
#include <fstream>    // used for file opening
#include <filesystem> // to work with log file paths

log_parse_app::log_parse_app() : query_engine(log_store)
{
    // we do this because our log_query obj needs an reference to the log_vector_obj
    // so whenever the log_parse_app obj is instanciated the log_query object is in valid state

    // now lets push some parser into the vector
    auto simple_parser = std::make_unique<simple_log_parser>();
    // make an simple log parser on the heap and gives it unique ptr to simple parser

    // now we push back this into our vector of parsers
    // IMP NOTE: with unique ptrs we need to use std::move because unique ptrs can be copied they can only be moved
    // std::move transfers ownership to new ptr and assigns old ptr to 'nullptr'
    available_parsers.push_back(std::move(simple_parser));
}

void log_parse_app::load_logFile()
{
    std::cout << "Please enter an path to the file you want to do analysis on.\n";
    std::string file_string;
    if (!std::getline(std::cin, file_string) || file_string.empty())
    {
        std::cerr << "Error: Invalid file path entered.\n";
        return;
    }

    std::filesystem::path file_path(file_string);
    if (!std::filesystem::exists(file_path))
    {
        std::cerr << "Oops!! Such file path does not exist\n";
        return;
    }

    log_parser *selected_parser = select_parser();
    // the function which allows user to select which parser to call based type of log file

    if (selected_parser == nullptr)
    {
        std::cout << "No parser selected. Returning to main menu..........\n";
        return;
    }

    log_store = log_vector();
    // this replaces the old log_store with new by using default constructor of log_vector

    std::ifstream log_file(file_path);
    if (!log_file.is_open())
    {
        std::cerr << "Error: Could not open file: " << file_path << "\n";
        return; // going back to main menu
    }

    std::cout << "Loading and parsing file: " << file_path << " ...\n";

    std::string line;
    int total_lines_read = 0;
    int lines_parsed_successfully = 0;

    while (std::getline(log_file, line))
    {
        total_lines_read++;
        std::optional<log> parsed_log = selected_parser->parse_line(line);
        if (parsed_log.has_value())
        {
            log_store.add_one_log(parsed_log.value());
            lines_parsed_successfully++;
        }
    }

    std::cout << "Finished processing file.\n";
    std::cout << "  Total lines read: " << total_lines_read << "\n";
    std::cout << "  Logs parsed successfully: " << lines_parsed_successfully << "\n";

    // what if file format was wrong
    // like user opened a csv file instead of log file
    // then it wont simply process nothing
    // why we used total_line_read
    // if it opens any file it will be automatically greater than, if it parses or not is dependant on the file
    if (total_lines_read > 0 && lines_parsed_successfully == 0)
    {
        std::cerr << "Warning: No log entries were successfully parsed.\n";
        std::cerr << "Please ensure you selected the correct parser format for this file.\n";
    }
}

log_parser *log_parse_app::select_parser()
{
    if (available_parsers.empty())
    {
        std::cerr << "Currenltly There are no log parsers configured.\n";
        return nullptr;
    }
    std::cout << "Please Enter the log format to use\n";
    for (int i = 0; i < available_parsers.size(); ++i)
    {
        std::cout << "  " << i + 1 << ". " << available_parsers[i]->return_parser_name() << "\n";
        if (available_parsers[i]->return_parser_name() == "Simple Log parser")
        {
            std::cout << " Format: [YYYY-MM-DD HH:MM:SS] LEVEL - Message [- IP: x.x.x.x] (IP is optional)\n";
        }

        // for apache log parser
        //    else if (parsers_[i]->getName() == "ApacheLogParser") {
        //      std::cout << "     Format: IP - - [DD/Mon/YYYY:HH:MM:SS +ZZZZ] \"Request\" Status Bytes\n";
        // }
    }

    std::cout << "From the Above list, Enter your choice (A Number): ";

    int choice_num = 0;
    std::string line;
    if (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        if (!(ss >> choice_num) || ss.rdbuf()->in_avail() != 0)
        {
            choice_num = 0;
        }
    }

    int index_chosen = choice_num - 1;
    if (index_chosen < available_parsers.size())
    {
        return available_parsers[index_chosen].get();
    }
    else
    {
        std::cerr << "Error: Invalid parser selection number.\n";
        return nullptr;
    }
}

void log_parse_app::run_queryLoop()
{

    std::cout << "\n--- Entering Query Mode ---";
    std::cout << "\nType 'help' for available commands or 'back' to return to the main menu.\n";

    std::string line;
    while (true)
    {
        std::cout << "\n> ";

        if (!std::getline(std::cin, line) || line.empty())
        {
            if (std::cin.eof())
            { // Handle Ctrl+D (end of input)
                std::cout << "\nExiting query loop.\n";
                break;
            }
            continue; // Ignore empty lines, loop again
        }
        std::stringstream ss(line);
        std::string command;
        std::vector<std::string> args;
        std::string token;

        if (!(ss >> command))
        {
            continue;
        }

        while (ss >> token)
        {
            args.push_back(token);
            // reads in loop one by one
        }

        if (command == "back" || command == "exit" || command == "quit")
        {
            std::cout << "Returning to main menu.\n";
            break;
        }
        else if (command == "help")
        {
            std::cout << "\n--- Available Commands ---\n\n";
            std::cout << "  COUNT [WHERE <field> <op> <value>]\n";
            std::cout << "    Counts logs. Optionally filters with WHERE.\n";
            std::cout << "    Example: COUNT WHERE level = ERROR\n";
            std::cout << "    Example: COUNT WHERE timestamp < \"2025-10-18 12:00:00\"\n\n";

            std::cout << "   LIST <field|> [WHERE <field> <op> <value>]\n";
            std::cout << "    Displays logs matching a WHERE clause. Use '*' or field name.\n";
            std::cout << "    Example: LIST * WHERE level = WARN\n";
            std::cout << "    Example: LIST message WHERE ip_address = 192.168.1.10\n\n";

            std::cout << "  TOP <N> <field>\n";
            std::cout << "    Shows the top N most frequent values for a field.\n";
            std::cout << "    Example: TOP 5 ip_address\n";
            std::cout << "    Example: TOP 3 level\n\n";

            std::cout << "    help\n";
            std::cout << "    Displays this message.\n\n";

            std::cout << "    back   |   exit   |  quit  \n";
            std::cout << "    Returns to the main menu.\n\n";

            std::cout << "--- Fields & Operators ---\n";
            std::cout << "    Fields for WHERE: `level`, `timestamp`, `ip_address`\n";
            std::cout << "    Fields for TOP:   `level`, `ip_address`, `message`\n";
            std::cout << "    Operators for WHERE:\n";
            std::cout << "    - Use `=`, `==` for `level` (case-insensitive handled internally) and `ip_address` (case-sensitive).\n";
            std::cout << "    - Use `=`, `==`, `>`, `<`, `>=`, `<=` ONLY for `timestamp`.\n";
            std::cout << "      (Using >, <, etc. on other fields will likely show no results).\n";
            std::cout << "  Timestamp Format: `\"YYYY-MM-DD HH:MM:SS\"`\n";
            continue;
        }
        else if (command == "COUNT")
        {
            if (args.empty())
            { // Simple COUNT
                int total = query_engine.count_all();
                std::cout << "Total log entries: " << total << "\n";
            }
            else if (args.size() == 4 && args[0] == "WHERE")
            { // COUNT WHERE
                // Args: WHERE, field, op, value -> indices 0, 1, 2, 3
                size_t count = query_engine.count_where(args[1], args[2], args[3]);
                std::cout << "Matching log entries: " << count << "\n";
            }
            else
            {
                std::cerr << "Error: Invalid COUNT command format. Use 'COUNT' or 'COUNT WHERE <field> <op> <value>'.\n";
            }
        }
        else if (command == "LIST")
        {
            if (args.size() >= 4 && args[1] == "WHERE")
            {
                std::string field_to_list = args[0];
                std::string condition_field = args[2];
                std::string condition_opr = args[3];
                std::string condition_value = args[4];

                std::vector<log> results = query_engine.list_where(condition_field, condition_opr, condition_value);
                if (results.empty())
                {
                    std::cout << "No matching log entries found.\n";
                }
                else
                {
                    std::cout << "Found " << results.size() << " matching log entries:\n";

                    bool print_all_fields = false;
                    if (field_to_list != "*" &&
                        field_to_list != "timestamp" &&
                        field_to_list != "level" &&
                        field_to_list != "ip_address" &&
                        field_to_list != "message")
                    {
                        std::cerr << "\nWarning: Unknown field '" << field_to_list
                                  << "' specified for LIST. Displaying all fields instead.\n";
                        print_all_fields = true; // Set flag to print everything
                    }
                    else if (field_to_list == "*")
                    {
                        print_all_fields = true;
                    }

                    for (const auto &log : results)
                    {
                        std::cout << "  "; // Indent each log entry

                        if (print_all_fields)
                        {
                            // Print all fields
                            std::cout << log.timestamp << " | " << log.log_level << " | "
                                      << (log.ip_address.empty() ? "-" : log.ip_address)
                                      << " | " << log.message;
                        }
                        else if (field_to_list == "timestamp")
                        {
                            std::cout << log.timestamp;
                        }
                        else if (field_to_list == "level")
                        {
                            std::cout << log.log_level;
                        }
                        else if (field_to_list == "ip_address")
                        {
                            std::cout << (log.ip_address.empty() ? "-" : log.ip_address); // Print '-' if IP is empty
                        }
                        else if (field_to_list == "message")
                        {
                            std::cout << log.message;
                        }

                        std::cout << "\n";
                    }
                }
            }
            else
            {
                std::cerr << "Error: Invalid LIST command format. Use 'LIST <field|*> WHERE <field> <op> <value>'.\n";
            }
        }
        else if (command == "TOP")
        {
            if (args.size() == 2)
            { // TOP N field
                // Args: N, field -> indices 0, 1
                try
                {
                    // Use std::stoull for size_t string to long long int
                    size_t n = std::stoull(args[0]);
                    if (n == 0)
                        throw std::invalid_argument("N must be > 0");
                    std::string field = args[1];
                    auto top_results = query_engine.topN(field, n);

                    if (top_results.empty())
                    {
                        std::cout << "No results found for top " << n << " " << field << ".\n";
                    }
                    else
                    {
                        std::cout << "Top " << (top_results.size() < n ? top_results.size() : n)
                                  << " results for field '" << field << "':\n";
                        for (const auto &pair : top_results)
                        {
                            std::cout << "  " << pair.first << ": " << pair.second << "\n";
                        }
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    std::cerr << "Invalid number provided must be an positive number(integer)\n";
                }
                catch (const std::out_of_range &e)
                {
                    std::cerr << "Error Number provided is too big\n";
                }
            }
            else
            {
                std::cerr << "Error: Invalid TOP command format. Use 'TOP <N> <field>'.\n";
            }
        }
        else
        {
            std::cerr << "Error: Unknown command '" << command << "'. Type 'help' for options.\n";
        }
        // End of query while loop
    }
}

void log_parse_app::run()
{
    std::cout << "--- Welcome to the C++ Log Query Engine ---" << std::endl;

    // The main application loop. Continues until the user chooses to exit.
    while (true)
    {
        // 1. Display the main menu options.
        std::cout << "\n           --- Main Menu ---          \n";
        std::cout << "1. Load a New Log File\n";
        std::cout << "2. Analyze Loaded Data\n";
        std::cout << "3. Exit\n";
        std::cout << "Please enter your choice: ";
        int choice = 0;
        std::string line;

        // using getline + stringstream for input
        if (std::getline(std::cin, line))
        {
            std::stringstream ss(line);
            if (!(ss >> choice) || ss.rdbuf()->in_avail() != 0)
            {
                choice = 0;
                // if invalid we the also keep choice variabe in invalid state
            }
        }

        switch (choice)
        {
        case 1:
            // Call the private helper function to handle loading.
            load_logFile();
            break;
        case 2:
            // check if data was loaded
            if (log_store.get_logs().empty())
            {
                std::cerr << "\nError:- No log Data is loaded until now, please load an file first\n";
            }
            else
            {
                // Call the private helper function to run the query loop.
                run_queryLoop();
            }
            break;
        case 3:
            std::cout << "\nExiting Log Query Engine. Goodbye!\n";
            return;
        default:
            std::cerr << "\nError: You entered a wrong option please choose a number between 1-3\n";
            break;
        }
    }
}