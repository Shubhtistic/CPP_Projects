#pragma once
#include "Asset.h"

class Bond : public Asset
{
private:
    double interest_rate;

public:
    Bond(const std::string &symbol_given, double price_given, double interest_rate_given);
    double tick() override;
    double get_value() const override;
};