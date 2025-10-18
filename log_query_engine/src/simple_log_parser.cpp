#include "simple_log_parser.h"
#include <chrono>
#include <iomanip>

std::optional<log> simple_log_parser::parse_line(const std::string &line)
{
    std::smatch matches;
    // smatch is an type of container it will catch our substrings we get from regex pattern
    if (std::regex_match(line, matches, simple_pattern))
    {
        // with this line we try to match pur entire line against the pattern
        // if we are inside this block it means line was valid log entry

        // match_results will contain the full match at index 0,
        // Our regex has 4 groups.
        // 3+1 -> 1 optional for ip address
        // a successful match will have a size of 5.
        if (matches.size() == 5)
        {
            // matches[i] is like an pointer kind of like viweing so its not an string
            // with .str() we convert ino an string
            // without .str() its just an reference
            std::string timestamp = matches[1].str();
            std::string level = matches[2].str();
            std::string message = matches[3].str();
            std::string ip_found = "";
            if (matches[4].matched)
            {
                // as ip is optional i.e if exits the match block contains it
                // else the match block is empty but still created
                // If it matched, we extract the IP string.
                ip_found = matches[4].str();
            }
            // parse time stamp
            std::tm tm = {}; // Zero initialize tm struct
            std::stringstream ss(timestamp);
            // Define the expected format based on your regex capture
            const char *time_format = "%Y-%m-%d %H:%M:%S";

            // Use get_time to parse the string into the tm struct
            // get_time except an c style string as a second arg
            // he we used char* time_format
            ss >> std::get_time(&tm, time_format);
            // get_time is an part of <iomanip>

            // is parsing failed
            if (ss.fail())
            {
                return std::nullopt;
                // we simply skip this log entry if timestamp is invalid
            }

            // we convert our tm into an time point
            // the mktime assumes local time
            // most of the logs are  in utc form so we will also assume utc time
            std::time_t time_c = timegm(&tm);
            // converts as utc

            if (time_c == -1)
            { // check if timegm failed
                // make time failed we cant populate our time variable now
                // return nullopt;
                return std::nullopt;
            }
            auto time_point = std::chrono::system_clock::from_time_t(time_c);
            return log(timestamp, level, message, ip_found, time_point);
        }
    }
    return std::nullopt;
    // we return an enpty signal, saying that parsing failed
}
