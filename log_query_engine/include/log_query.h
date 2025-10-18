#pragma once
#include "log_vector.h"
// this class only does analysis of the log_vector does not own it

class log_query
{

    const log_vector &ref;
    // const refereance to log_vector obj
public:
    log_query(const log_vector &l) : ref(l) {}
    // by this we take an reference of log_vector class so we can perform analysis on it

    size_t count_all();
    size_t count_where(const std::string &field, const std::string &op, const std::string &value) const;
    std::vector<log> list_where(const std::string &field, const std::string &op, const std::string &value) const;

    std::vector<std::pair<std::string, size_t>> topN(const std::string &field, size_t n) const;
};