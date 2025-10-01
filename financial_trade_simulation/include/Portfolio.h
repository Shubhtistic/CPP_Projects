#pragma once
#include <memory>
#include "Asset.h"
#include <map>

class Portfolio
{
    double total_cash = 5000.0;
    std::map<Asset *, int> holdings;

public:
    void set_cash(double cash);

    bool buy(Asset *asset, int quantity);
    bool sell(Asset *asset, int quantity);

    void pass_time();
    inline const std::map<Asset *, int> &display() const { return holdings; }
    inline double show_cash() const { return total_cash; }
    // this is an inline function , this returns an const referance
    // we need to catch this const reference with an referance to aviod copy of it
};