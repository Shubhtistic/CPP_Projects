#include "Simulation.h"
#include <limits>
#include <iostream>
#include "Portfolio.h"
#include <fstream>
#include "Stock.h"
#include "Bond.h"
#include <sstream>
#include <string>

Simulation::Simulation()
{
    read_at_start();
}

void Simulation::read_at_start()
{
    std::ifstream market_csv("market_assets.csv");
    if (market_csv.is_open() == false)
    {
        std::cerr << "There is some issue Loading the Market Assets file\n"
                  << "Please check if you have accidently deleted it\n";
        return;
    }
    std::string line_from_file;
    std::getline(market_csv, line_from_file);
    // this is first line from our csv file
    // we will ignore this
    // ifstream acts like a bookmark in th while loop it will start readinf from the second line
    while (std::getline(market_csv, line_from_file))
    {
        std::stringstream stream(line_from_file);
        std::vector<std::string> store_tokens;
        std::string token;
        while (std::getline(stream, token, ','))
        {
            store_tokens.push_back(token);
        }
        if (store_tokens.size() == 4)
        {
            if (store_tokens[0] == "Stock")
            {
                double price = std::stod(store_tokens[2]);
                market_sim.push_back(std::make_unique<Stock>(store_tokens[1], price));
            }
            else if (store_tokens[0] == "Bond")
            {
                double price = std::stod(store_tokens[2]);
                double interest = std::stod(store_tokens[3]);
                market_sim.push_back(std::make_unique<Bond>(store_tokens[1], price, interest));
            }
        }
    }
}

bool Simulation::start_cash()
{

    while (true)
    {

        double real_cash;
        std::string temp_string_cash;
        std::string temp_cash;

        std::cout << "Please Enter A Cash Amount to start the simulation\n"
                  << "For Default just press Enter\n"
                  << "Default is set at 5000.0\n";
        std::getline(std::cin, temp_string_cash);
        std::stringstream cash(temp_string_cash);
        cash >> temp_cash;
        if (temp_cash.empty())
        {
            std::cout << "You did not enter anything Default(5000.0) will be used\n";
            // 5000 is hardcoded in class defn dont need to assign again

            return true;
        }
        try
        {
            real_cash = std::stod(temp_cash);
            // if any error stops here
            // anything after this wont run control goes to catch block
            market_portfolio.set_cash(real_cash);
            std::cout << "Set the cash as " << real_cash << " successfully\n";
            return true;
        }

        catch (const std::invalid_argument &)
        {
            std::cerr << "Error: Not a valid number.\n";
            std::cout << "Do you want to try again or exit\n"
                      << "Enter y for 'YES' and any other key for 'NO'\n"
                      << "If you say 'NO' you will get the default value(5000.0)\n";
            std::string input;
            std::getline(std::cin, input);
            std::stringstream test(input);
            test >> input;
            // just overide the old input param instaed of making a new one
            if (input.empty())
            {
                std::cout << "did not specify anything\nLets try Again!!\n";
                continue;
            }

            else if (input[0] == 'y' || input[0] == 'Y')
            {
                continue;
            }

            else
            {
                return true;
            }
        }
    }
    return true;
}

double Simulation::return_current_balance() const
{
    return market_portfolio.show_cash();
}
void Simulation::buy_assets()
{

    std::cout << "Welcome!! what do you want to buy,\n"
              << "Type in form of [Asset Symbol] [Quantity]\n";
    std::string given_input;
    std::getline(std::cin, given_input);
    if (given_input.empty())
    {
        std::cerr << "You did not enter anything!!\n";
        return;
    }
    else
    {
        std::stringstream stream(given_input);
        std::string asset_Symbol;
        std::string q;

        if (!(stream >> asset_Symbol))
        {
            std::cerr << "Exited, missing asset symbol or quantity\n";
            return;
        }
        if (!(stream >> q))
        {
            std::cerr << "Exited ,missing asset symbol or quantty\n";
            return;
        }
        try
        {
            size_t track_position;
            int quantity = std::stoi(q, &track_position);

            if (track_position != q.length())
            {
                std::cerr << "Error, quantity should be an number\n";
                return;
            }
            if (quantity < 1)
            {
                std::cerr << "Error occured, qunaity should be greater than 1\n";
                return;
            }

            Asset *found_or_not = nullptr;
            // now loop thorugh the Assets vector to find a match
            for (auto &market_sim_copy : market_sim)
            {
                if (market_sim_copy->get_symbol() == asset_Symbol)
                {
                    found_or_not = market_sim_copy.get();
                    break;
                }
            }

            if (found_or_not != nullptr)
            {
                std::cout << "The stock Was found Succesfully!!\n";

                if (market_portfolio.buy(found_or_not, quantity) == false)
                {
                    std::cerr << "You Have Insufficient Funds or Balance\n";
                }
                else
                {
                    std::cout << "Bought Successfully\n";
                    std::cout << "Your current Balance " << return_current_balance();
                }
            }
            else
            {
                std::cerr << "No Such Stock Exists!!!\n";
            }
        }
        catch (const std::exception &)
        {
            std::cerr << "The quantity is not an valid integer\n";
            return;
        }
    }
}

void Simulation::sell_assets()
{

    std::cout << "Welcome!! what do you want to Sell,\n"
              << "Type in form of [Asset Symbol] [Quantity]\n";
    std::string given_input;
    std::getline(std::cin, given_input);
    if (given_input.empty())
    {
        std::cerr << "You did not enter anything!!\n";
        return;
    }
    else
    {
        std::stringstream stream(given_input);
        std::string asset_Symbol;
        std::string q;

        if (!(stream >> asset_Symbol))
        {
            std::cerr << "Exiting, missing asset symbol or quantity\n";
            return;
        }
        if (!(stream >> q))
        {
            std::cerr << "Exiting ,missing asset symbol or quantty\n";
            return;
        }
        try
        {
            size_t track_position;
            int quantity = std::stoi(q, &track_position);

            if (track_position != q.length())
            {
                std::cerr << "Error, quantity should be an number\n";
                return;
            }
            if (quantity < 1)
            {
                std::cerr << "Error occured, quantity should be greater than 1\n";
                return;
            }

            Asset *found_or_not = nullptr;
            // now loop thorugh the Assets vector to find a match
            for (auto &market_sim_copy : market_sim)
            {
                if (market_sim_copy->get_symbol() == asset_Symbol)
                {
                    found_or_not = market_sim_copy.get();
                    break;
                }
            }

            if (found_or_not != nullptr)
            {
                std::cout << "The stock Was found Succesfully!!\n";

                if (market_portfolio.sell(found_or_not, quantity) == false)
                {
                    std::cerr << "You Have Insufficient Funds or Balance\n";
                }
                else
                {
                    std::cout << "Sold Successfully!!\n";
                    std::cout << "Your current Balance " << return_current_balance();
                }
            }
            else
            {
                std::cerr << "No Such Stock Exists!!!\n";
            }
        }
        catch (const std::exception &)
        {
            std::cerr << "The quantity is not an valid integer\n";
            return;
        }
    }
}

void Simulation::display_assets() const
{

    const auto &temp_map_holder = market_portfolio.display();
    // catching the reference we threw(returned) from the display function
    if (temp_map_holder.empty())
    {
        std::cerr << "OOPS!! You dont have any stocks\n";
        std::cout << "----------------------------------------------------------------------------------------\n";

        return;
    }
    else
    {
        std::cout << "Your current Balance " << return_current_balance();
        std::cout << "----------------------------------------------------------------------------------------\n";
        std::cout << "THE ASSETS ARE AS BELOW\n";
        for (const auto &abc : temp_map_holder)
        {

            std::cout << "Asset: " << abc.first->get_symbol() << " Quantity: " << abc.second << "\n";
        }
    }
}

void Simulation::simulate_time_pass()
{
    market_portfolio.pass_time();
    std::cout << "Your updated Balance " << return_current_balance();
    std::cout << "\n----------------------------------------------------------------------------------------\n";
}

void Simulation::market_assets() const
{
    std::cout << "\n------------------ MARKET PRICES -------------------\n";
    for (const auto &asset_ptr : market_sim)
    {
        std::cout << "  Symbol: " << asset_ptr->get_symbol()
                  << " Price: $" << asset_ptr->get_value() << "\n";
    }
    std::cout << "----------------------------------------------------\n";
}

void Simulation::run_method()
{
    std::cout << "WELCOME!!\n";
    std::cout << "I Made this project as a small representation of real financial trade systems\n";
    if (start_cash())
    {
        while (true)
        {

            std::cout << "\n---------------------- MENU -------------------------\n";
            std::cout << "1. Buy An Asset\n";
            std::cout << "2. Sell An Asset\n";
            std::cout << "3. Show Current Balance\n";
            std::cout << "4. Simulate Time Pass\n";
            std::cout << "5. Display All Assets\n";
            std::cout << "6. Currently available assets in market\n";

            std::cout << "7. Exit\n";
            std::cout << "Enter Your Choice: ";
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);

            int user_choice = 0;

            // 2. Try to parse an integer from the line.
            if (ss >> user_choice)
            {
                // we only enter here if ss is an int gien to user choice
                switch (user_choice)
                {
                case 1:
                    buy_assets();
                    break;
                case 2:
                    sell_assets();
                    break;
                case 3:
                    std::cout << "Your current Balance: " << return_current_balance() << "\n";
                    break;
                case 4:
                    simulate_time_pass();
                    break;
                case 5:
                    display_assets();
                    break;

                case 6:
                    market_assets();
                    break;

                case 7:
                    std::cout << "Thanks for using my project\nGOODBYE!!\n";
                    return;
                default:
                    std::cerr << "Error: Please enter a number between 1 and 6.\n";
                    break;
                }
            }
            else
            {
                // fail parse
                std::cerr << "Error: Invalid input. Please enter a number.\n";
                continue;
            }
        }
    }
}
