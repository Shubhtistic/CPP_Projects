#pragma once
#include "Asset.h"
#include <map>

class Portfolio
{
    double total_cash;
    std::map<Asset *, int> holdings;

public:
    Portfolio(double start_cash) : total_cash(start_cash) {}

    bool buy(Asset *asset, int quantity);
    bool sell(Asset *asset, int quantity);

    void pass_time();
    void display() const;
};