#pragma once
#include <regex>
#include "log_parser.h"

class simple_log_parser : public log_parser
{
    std::regex simple_pattern;

public:
    simple_log_parser():simple_pattern(R"(^\[(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}(?:\.\d{1,3})?)\]\s*(INFO|WARN|ERROR|DEBUG|FATAL)\s*-\s*(.*)$)"){}
    std::optional<log> parse_line(const std::string &parsed) override;
};