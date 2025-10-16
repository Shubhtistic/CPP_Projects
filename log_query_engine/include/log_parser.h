#pragma once
#include<string>
#include<optional>
#include "log.h"
class log_parser{
    public:
    virtual std::optional<log> parse_line(const std::string& parsed)=0;

    virtual ~log_parser()=default;

};