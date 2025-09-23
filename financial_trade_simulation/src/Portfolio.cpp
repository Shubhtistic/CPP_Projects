#include "Portfolio.h"
#include <iostream>

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
    total_cash = total_cash _ + total_value_to_add;
    holdings[asset] = holdings[asset] - quantity;

    if (holdings.count(asset) == 0)
    {
        holdings.erase(asset);
    }

    std::cout << "Success!!!\n";
    return true;
}
