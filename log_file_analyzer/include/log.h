#pragma once
#include <string>
class log
{
    std::string time_stamp;
    std::string level;
    std::string info;

public:
log::log(std::string time_stamp_given, std::string level_given, std::string info_given) : time_stamp(time_stamp_given), level(level_given), info(info_given) {}

};