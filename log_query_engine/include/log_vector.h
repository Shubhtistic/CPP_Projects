#pragma once
#include <vector>
#include "log.h"

class log_vector
{
    std::vector<log> log_container;

public:
    void add_one_log(log log_obj);
    const std::vector<log>& get_logs() const;
};