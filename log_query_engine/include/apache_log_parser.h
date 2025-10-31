#pragma once
#include "log_parser.h" // our abstract class
#include <regex>
#include <string>

class ApacheLogParser : public log_parser
{
public:
    ApacheLogParser();

    // The override keyword is a safety check that ensures we are
    // correctly implementing a virtual function from the base class.
    std::optional<log> parse_line(const std::string &line) override;

    std::string return_parser_name() const override;

private:
    std::regex apache_pattern_;

    std::optional<std::chrono::system_clock::time_point> parse_apache_timestamp(const std::string &timestamp_str);

    const std::string PARSER_NAME = "Apache Log Parser";
};