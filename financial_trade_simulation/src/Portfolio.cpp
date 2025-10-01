#include "Portfolio.h"

void Portfolio::set_cash(double cash)
{
    total_cash = cash;
}

bool Portfolio::buy(Asset *asset, int quantity)
{

    double total_value = quantity * asset->get_value();

    if (total_value >= total_cash)
    {
        return false;
    }

    total_cash = total_cash - total_value;
    holdings[asset] = holdings[asset] + quantity;

    return true;
}

bool Portfolio::sell(Asset *asset, int quantity)
{
    if (holdings.count(asset) == 0)
    {
        // std::cerr << "You dont own this stock\n";
        return false;
    }
    if (holdings[asset] < quantity)
    {
        // std::cerr << "Not Enough shares to sell -_-\n";
        return false;
    }
    double total_value_to_add = asset->get_value() * quantity;
    total_cash = total_cash + total_value_to_add;
    holdings[asset] = holdings[asset] - quantity;

    if (holdings[asset] == 0)
    {
        holdings.erase(asset);
    }

    // std::cout << "Success!!!\n";
    return true;
}

void Portfolio::pass_time()
{
    double total_payouts = 0.0;
    for (auto &holdings_copy : holdings)
    {
        double payout = holdings_copy.first->tick();
        total_payouts = total_payouts + (payout * holdings_copy.second);
    }

    total_cash = total_cash + total_payouts;
}
