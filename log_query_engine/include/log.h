// this class has an simple struct which is our log object
#pragma once
#include <string>

struct log
{

    std::string timestamp;
    std::string log_level;
    std::string message;
    std::string ip_address;

    log(const std::string &t, const std::string &level, const std::string &msg, const std::string &ip) : timestamp(t), log_level(level), message(msg), ip_address(ip) {}
};