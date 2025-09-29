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

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
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

void Simulation::start_cash()
{
    double temp_cash;
    while (true)
    {

        std::cout << "Please Enter A Cash Amount to start the simluation\n"
                  << "Note: Please make sure to enter a Suitable amount\n"
                  << "Reccomended:- 100000 \n";
        std::cin >> temp_cash;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You have not entred Appropriate Cash\n"
                      << "Do u want to Try or exit\n"
                      << "Enter y for 'YES' and any other key for 'NO'\n";
            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            market_portfolio.set_cash(temp_cash);
        }
    }
}

void Simulation::buy_something()
{
}