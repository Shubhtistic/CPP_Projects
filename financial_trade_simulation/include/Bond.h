#pragma once
#include "Asset.h"

class Bond : public Asset
{
private:
    double interest_rate;

public:
    Bond(const std::string &symbol1, double price, double interest_rate);
    double tick() override;
    double get_value() const override;
    double get_interest_rate();
};