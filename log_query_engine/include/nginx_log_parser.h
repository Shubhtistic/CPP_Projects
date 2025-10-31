#pragma once
#include "log_parser.h"
#include <regex>
#include <string>

class nginx_log_parser : public log_parser
{
public:
    nginx_log_parser();

    std::optional<log> parse_line(const std::string &line) override;
    std::string return_parser_name() const override;

private:
    std::regex nginx_pattern;

    std::optional<std::chrono::system_clock::time_point> parse_nginx_timestamp(const std::string &timestamp_str);
    const std::string parser_name="NGINX Log Parser";
};