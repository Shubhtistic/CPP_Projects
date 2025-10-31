#pragma once
#include "log_parser.h" // our abstract class
#include <regex>
#include <string>

class apache_log_parser : public log_parser
{
public:
    apache_log_parser() : apache_pattern(R"(^([\d.]+|[\da-fA-F:]+)\s+(\S+)\s+(\S+)\s+\[(.*?)\]\s+\"(.*?)\"\s+(\d{3})\s+(\d+|-)(?:\s+\"(.*?)\"\s+\"(.*?)\")?.*$)") {}

    // The override keyword is a safety check that ensures we are
    // correctly implementing a virtual function from the base class.
    std::optional<log> parse_line(const std::string &line) override;

    std::string return_parser_name() const override;

private:
    std::regex apache_pattern;

    std::optional<std::chrono::system_clock::time_point> parse_apache_timestamp(const std::string &timestamp_str);

    const std::string parser_name = "Apache Log Parser";
};