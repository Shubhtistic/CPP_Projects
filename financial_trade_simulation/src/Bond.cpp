#include "Bond.h"
#include <random>

Bond::Bond(const std::string &symbol1, double price, double interest_rate1) : Asset(symbol1, price), interest_rate(interest_rate1) {}

double Bond::tick()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<double> my_dist(0.0, 1.0);
    double tick_value = my_dist(rng);
    double payout_probabiliity = 0.15;
    double payment = 0.0;
    // 0.15 means 15%
    if (tick_value < payout_probabiliity)
    {
        payment = current_price * interest_rate;
    }

    return payment;
}

double Bond::get_value() const
{
    return current_price;
}

double Bond::get_interest_rate()
{
    return interest_rate;
}