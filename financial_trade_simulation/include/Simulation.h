#include <vector>
#include <memory>
#include "Asset.h"
#include "Portfolio.h"

class Simulation
{
private:
    std::vector<std::unique_ptr<Asset>> market_sim;
    // stores unique ptr's to Asset Base class
    Portfolio market_portfolio;
    void read_at_start();

    bool start_cash();
    void buy_assets();
    void sell_assets();
    void simulate_time_pass();

    void display_assets() const;
    double return_current_balance() const;
    void market_assets() const;

public:
    Simulation();
    void run_method();
};