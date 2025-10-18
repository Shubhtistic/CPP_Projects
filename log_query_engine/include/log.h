// this class has an simple struct which is our log object
#pragma once
#include <string>
#include <chrono>

struct log
{

    std::string timestamp;
    std::string log_level;
    std::string message;
    std::string ip_address;

    // new member to store the parsed time object
    std::chrono::system_clock::time_point timestamp_obj;
    log(const std::string &ts, const std::string &lvl, const std::string &ip, const std::string &msg,
        const std::chrono::system_clock::time_point &ts_obj) // <-- Add new parameter
        : timestamp(ts), log_level(lvl), ip_address(ip), message(msg),
          timestamp_obj(ts_obj)
    {
    }
};