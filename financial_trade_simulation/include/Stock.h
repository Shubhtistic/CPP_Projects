#pragma once
#include "Asset.h"

class Stock : public Asset
{
public:
    Stock(const std::string &symbol1, double price);
    virtual double tick() override;
    virtual double get_value() const override;
};