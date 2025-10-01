#pragma once
#include <string>

class Asset
{
protected:
    std::string symbol;
    double current_price;

public:
    Asset(const std::string &symbol_given, double current_price_given) : symbol(symbol_given), current_price(current_price_given) {}

    virtual double tick() = 0;
    virtual double get_value() const = 0;
    std::string get_symbol() const { return symbol; }
    virtual ~Asset() {};
};