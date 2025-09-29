#include <vector>
#include <memory>
#include "Asset.h"
#include "Portfolio.h"
#include <sstream>

class Simulation
{
private:
    std::vector<std::unique_ptr<Asset>> market_sim;
    // stores unique ptr's to Asset Base class
    Portfolio market_portfolio;

public:
    Simulation();
    void start_cash();
    void buy_something();
    void read_at_start();
};