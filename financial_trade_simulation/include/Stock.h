#pragma once
#include "Asset.h"

class Stock : public Asset
{
public:
    Stock(const std::string &symbol_given, double price_given);
    virtual double tick() override;
    virtual double get_value() const override;
};