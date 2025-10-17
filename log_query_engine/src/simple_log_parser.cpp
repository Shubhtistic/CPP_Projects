#include "simple_log_parser.h"

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
        // a successful match will have a size of 4.
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

            return log(timestamp, level, message, ip_found);
        }
    }
    return std::nullopt;
    // we return an enpty signal, saying that parsing failed
}
