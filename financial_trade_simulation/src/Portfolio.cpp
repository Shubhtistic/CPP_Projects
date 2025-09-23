#include "Portfolio.h"
#include <iostream>
#include <iomanip>

bool Portfolio::buy(Asset *asset, int quantity)
{

    double total_value = quantity * asset->get_value();

    if (total_value >= total_cash)
    {
        std::cerr << "You have Insufficient funds\n";
        return false;
    }

    total_cash = total_cash - total_value;
    holdings[asset] = holdings[asset] + quantity;
    std::cout << "Success!!\n";

    return true;
}

bool Portfolio::sell(Asset *asset, int quantity)
{
    if (holdings.count(asset) == 0)
    {
        std::cerr << "You dont own this stock\n";
        return false;
    }
    if (holdings[asset] < quantity)
    {
        std::cerr << "Not Enough shares to sell -_-\n";
        return false;
    }
    double total_value_to_add = asset->get_value() * quantity;
    total_cash = total_cash + total_value_to_add;
    holdings[asset] = holdings[asset] - quantity;

    if (holdings[asset] == 0)
    {
        holdings.erase(asset);
    }

    std::cout << "Success!!!\n";
    return true;
}

void Portfolio::pass_time()
{
    double total_payouts = 0.0;
    for (auto const &holding_copy : holdings)
    {
        double payout = holding_copy.first->tick();
        total_payouts = total_payouts + (payout * holding_copy.second);
    }

    total_cash = total_cash + total_payouts;
}

void Portfolio::display() const
{

    std::cout << "THe Current Total Balance is "
              << total_cash << std::fixed << std::setprecision(3) << std::endl;

    std::cout << "============= HOLDINGS!! ================\n";
    if (holdings.empty())
    {
        std::cerr << "You have currently have no Holdings!!\n";
    }
    for (auto const &holdings1 : holdings)
    {
        std::cout << "Asset Symbol " << holdings1.first->get_symbol() << "\n";
        std::cout << "Quantity owned " << holdings1.second << "\n";
        std::cout << "Total Current Market value of holding " << holdings1.second * holdings1.first->get_value() << "\n";
    }
}
