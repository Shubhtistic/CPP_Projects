// this class has an simple struct which is our log object
#pragma once
#include <string>

struct log
{

    std::string timestamp;
    std::string log_level;
    std::string message;

    log(const std::string &t, const std::string &level,const std::string &msg) : timestamp(t), log_level(level), message(msg) {}
};