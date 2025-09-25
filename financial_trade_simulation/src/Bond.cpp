#include "Bond.h"
#include <random>

Bond::Bond(const std::string &symbol_given, double price_given, double interest_rate_given) : Asset(symbol_given, price_given), interest_rate(interest_rate_given) {}

double Bond::tick()
{
    static std::mt19937 rng(std::random_device{}());
    // random_device{} creates an unnamed random_device object
    // () -> this immediately calls the object
    // in short random_device{}() create an random device obj and then destroy it after use
    // output of random device becomes seed for mt19937
    // mt19937 pseduo num generator
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
