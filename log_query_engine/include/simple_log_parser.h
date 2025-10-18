#pragma once
#include <regex>
#include "log_parser.h"

class simple_log_parser : public log_parser
{
    std::regex simple_pattern;
    const std::string parser_name = "Simple Log parser";

public:
    simple_log_parser() : simple_pattern(R"(^\[(.*?)\]\s*(INFO|WARN|ERROR|DEBUG|FATAL)\s*-\s*(.*?)(?:\s*-\s*IP:\s*(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))?$)") {}
    std::optional<log> parse_line(const std::string &parsed) override;
    std::string return_parser_name() const override;
};