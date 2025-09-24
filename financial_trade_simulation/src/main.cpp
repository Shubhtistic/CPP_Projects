#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "Portfolio.h"
#include "Stock.h"
#include "Bond.h"

int main()
{
    std::vector<std::unique_ptr<Asset>> market;
    auto apple_stock = std::make_unique<Stock>("AAPL", 175.5);
    market.push_back(std::move(apple_stock));
    market.push_back(std::make_unique<Bond>("US-T-BOND", 1000.0, 0.05));
    market.push_back(std::make_unique<Stock>("GOOG", 135.25));
    std::cout << "hii its working";

    return 0;
}