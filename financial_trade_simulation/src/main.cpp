#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "Portfolio.h"
#include "Stock.h"
#include "Bond.h"
#include <sstream>

int main()
{
    std::vector<std::unique_ptr<Asset>> market;
    auto apple_stock = std::make_unique<Stock>("AAPL", 175.5);
    market.push_back(std::move(apple_stock));
    // this varaible become emoy after std::move

    market.push_back(std::make_unique<Bond>("US-T-BOND", 1000.0, 0.05));
    // no extra variiable required
    market.push_back(std::make_unique<Stock>("GOOG", 135.25));

    Portfolio my_portfolio(10000.00);
    while (true)
    {
        my_portfolio.display();
        std::cout << "Enter Commands (buy [Symbol] [Quantity], buy [Symbol] [Quantity], tick , exit): \n";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string command_given;
        ss >> command_given;

        if (command_given == "exit" or command_given == "Exit")
        {
            std::cout << "Existing Simulation Goodbye -_-\n";
            break;
        }
        else if (command_given == "tick" or command_given == "Tick")
        {
            my_portfolio.pass_time();
            std::cout << "You decided to advance time .....\n";
        }

        else if (command_given == "buy" || command_given == "Buy" || command_given == "Sell" || command_given == "sell")
        {
            std::string symbol;
            int quantity;
            ss >> symbol >> quantity;
            // we are readind reaming parts

            if (ss.fail() || quantity <= 0)
            {
                std::cerr << "Error invalid command format or quantity.\n";
                std::cout << "lets try again \n";
                continue;
            }

            Asset *target_asset = nullptr;
            for (const auto &asset_ptr : market)
            {
                if (asset_ptr->get_symbol() == symbol)
                {
                    target_asset = asset_ptr.get();
                    // we got raw pointer from get method and store it in target asset ptr variable
                    break;
                }
            }

            // If we find the target asset ptr this if block runs
            if (target_asset)
            {
                if (command_given == "buy" || command_given == "Buy")
                {
                    my_portfolio.buy(target_asset, quantity);
                }
                else
                { // for our othrwise condition
                    my_portfolio.sell(target_asset, quantity);
                }
            }
            else
            {
                std::cerr << "Error: Asset with symbol '" << symbol << "' not found.\n";
            }
        }
        else
        {
            std::cerr << "Error: Unknown command '" << command_given << "'.\n";
        }
    }

    return 0;
}
