#pragma once
#include <string>

class Asset
{
protected:
    std::string symbol;
    double current_price;

public:
    Asset(const std::string &symbol1, double &current_price1) : symbol(symbol), current_price(current_price1) {}

    virtual void tick() = 0;
    virtual double get_value() const = 0;
    std::string get_symbol();
};