#pragma once
#include <string>
#include <optional>
#include "log.h"
class log_parser
{
    std::string parser_name;

public:
    virtual std::optional<log> parse_line(const std::string &parsed) = 0;
    virtual std::string return_parser_name() const = 0;
    // each class will provide their own implemenatation of this

    virtual ~log_parser() = default;
};