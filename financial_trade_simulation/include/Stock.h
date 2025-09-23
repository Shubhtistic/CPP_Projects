#pragma once
#include "Asset.h"

class Stock : public Asset
{
public:
    Stock(const std::string &symbol1, double &price);
    void tick() override;
    double get_value() const override;
};