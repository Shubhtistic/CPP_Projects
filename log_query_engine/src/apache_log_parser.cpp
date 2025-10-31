#include "apache_log_parser.h"
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <regex>

apache_log_parser::apache_log_parser()
    : apache_pattern(
          R"REGEX(^([\d.]+|[\da-fA-F:]+)\s+(\S+)\s+(\S+)\s+\[(.*?)\]\s+"((?:\\.|[^"\\])*)"\s+(\d{3})\s+(\d+|-)(?:\s+"((?:\\.|[^"\\])*)"\s+"((?:\\.|[^"\\])*)")?.*$)REGEX")
{
}

// This function parses the unique Apache timestamp format
std::optional<std::chrono::system_clock::time_point> apache_log_parser::parse_apache_timestamp(const std::string &timestamp_str)
{
    static const std::unordered_map<std::string, int> month_map = {
        {"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3}, {"May", 4}, {"Jun", 5}, {"Jul", 6}, {"Aug", 7}, {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}};

    std::stringstream ss(timestamp_str);
    std::tm tm = {};
    std::string month_str;

    // We read the day , then the slash, then the month string (ex. Oct)
    int day;
    char slash;
    if (!(ss >> day >> slash >> std::setw(3) >> month_str))
    {
        return std::nullopt;
    }

    if (month_map.find(month_str) == month_map.end())
    {
        return std::nullopt;
    }
    tm.tm_mon = month_map.at(month_str);

    // remaininy part of the string i.e after day/month
    // afer that there is an actual time stamp
    if (!(ss >> std::get_time(&tm, "/%Y:%H:%M:%S")))
    {
        return std::nullopt;
    }

    std::time_t time_c = timegm(&tm);
    if (time_c == -1)
    {
        return std::nullopt;
    }

    return std::chrono::system_clock::from_time_t(time_c);
}

std::string apache_log_parser::return_parser_name() const
{
    return parser_name;
}

// This is the core logic that attempts to parse one line of an Apache log.
std::optional<log> apache_log_parser::parse_line(const std::string &line)
{
    std::smatch matches;
    // regex mde container

    if (std::regex_match(line, matches, apache_pattern))
    {

        // we expect at least 8 matches (1 full + 7 captured groups)
        //  can be 10 if the optional referrer/user-agent are present
        if (matches.size() < 8)
        {
            return std::nullopt;
        }

        std::string ip = matches[1].str();
        std::string timestamp_str = matches[4].str();
        std::string request = matches[5].str();
        std::string status_str = matches[6].str();
        std::string bytes_str = matches[7].str();

        int status_code = 0;
        size_t bytes_sent = 0;
        try
        {
            status_code = std::stoi(status_str); // Convert status string to int
            // Convert bytes string to size_t. If it's "-", store 0.
            bytes_sent = (bytes_str == "-") ? 0 : std::stoull(bytes_str);
        }
        catch (const std::exception &e)
        {
            return std::nullopt;
        }

        auto time_point_opt = parse_apache_timestamp(timestamp_str);
        if (!time_point_opt.has_value())
        {
            return std::nullopt;
        }

        return log(
            timestamp_str,   // Original timestamp string
            "",              // level (empty)
            ip,              // ip_address
            "",              // message (empty)
            *time_point_opt, // timestamp_obj
            request,         // request
            status_code,     // status_code
            bytes_sent       // bytes_sent
        );
    }

    return std::nullopt;
}