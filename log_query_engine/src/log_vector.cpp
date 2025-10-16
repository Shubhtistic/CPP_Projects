#include "log_vector.h"
#include <vector>

void log_vector::add_one_log(log log_obj)
{
    log_container.push_back(log_obj);
}

const std::vector<log> &log_vector::get_logs() const
{
    return log_container;
    // this will return vector of logs as an const reference
}
