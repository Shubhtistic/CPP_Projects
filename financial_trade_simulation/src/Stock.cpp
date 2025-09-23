#include "Stock.h"
#include <random>
Stock::Stock(const std::string &symbol1, double &price) : Asset(symbol1, price) {}

double Stock::get_value() const
{
    return current_price;
}
double Stock::tick()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<double> my_dist(-1.0, 1.0);
    double tick_value = my_dist(rng);

    /*
    double volatile_range=0.05;
    we assume 5% max change i.e 0.05
    */

    double percentage_change = 0.05 * tick_value;
    current_price = current_price * (1.0 + percentage_change);

    return 0.0;
    // A stock pays no cash (-_- stonkssss)
}
