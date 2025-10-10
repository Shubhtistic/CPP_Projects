#pragma once
#include <string>
class log
{
    std::string time_stamp;
    std::string level;
    std::string info;

public:
    log(std::string time_stamp_given, std::string level_given, std::string info_given);
};