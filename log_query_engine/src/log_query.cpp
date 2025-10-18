#include "log_query.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <optional>
#include <iomanip>
#include <chrono>

#include <iterator>
// for std::back_inserter, some compilers automatically import  std::back_inserter if <algorithm> is used
// but its an strict practice to include, <iterator>  what if some compiler doesnt support this

#include <utility>
// for pair data structure, see below example
// std::pair<int, std::string> p1(1, "One")  ------> using constructor
// auto p2 = std::make_pair(2, "Two");       ----->  using make_pair

// -------------------------------------------------------------------------------------------------------------------------
// we decied to use timestamp based search also for which we used chrono and its functions
// now lets make an function an helper function
// we will use namespace for that
// In C++, a namespace is a way to group identifiers (functions, variables, classes) under a name to avoid name collisions
// we can simply say namespace_name::internal_function
// and this will be limited to our this .cpp file only
// if we use an normal function it will have global linkage
// i.e if we include this in other programs the normal function will be visible

namespace
{ // this is an optional function return time point or nullopt
    std::optional<std::chrono::system_clock::time_point> parse_time_stamp(const std::string &timestamp)
    {
        std::tm tm = {};
        std::stringstream ss(timestamp);
        const char *time_format = "%Y-%m-%d %H:%M:%S";
        ss >> std::get_time(&tm, time_format);
        if (ss.fail() || ss.rdbuf()->in_avail() != 0)
        { // ss.rdbuf() gives you the underlying stream buffer.
            // in_avail() returns the number of characters left unread in the buffer
            // so we check if it failed
            // and then we chcek if there is also any remaining text or something of that sort
            return std::nullopt; // Parsing failed or extra characters found
        }
        std::time_t time_c = timegm(&tm);
        if (time_c == -1)
        {
            return std::nullopt;
            // Conversion failed
        }
        return std::chrono::system_clock::from_time_t(time_c);
    }
}

size_t log_query::count_all()
{
    auto vector_logs = ref.get_logs();
    return vector_logs.size();
    // std::vector::size() always returns a size_t, which is unsigned.
    // If you assign it to an int
    // works for small arrays but not for very big arrays may cause overflow
}

size_t log_query::count_where(const std::string &field, const std::string &op, const std::string &value) const
{
    const auto &all_logs = ref.get_logs();

    std::optional<std::chrono::system_clock::time_point> user_time_point;
    bool is_timestamp_query = (field == "timestamp");
    if (is_timestamp_query)
    {
        user_time_point = parse_time_stamp(value);
        if (!user_time_point)
        {
            return 0;
            // Invalid date format provided by user
        }
    }

    //----------------------------------------------------------------------------------
    // count_if will iterate over the vector and calls lambda for each element of the vector(one log object)
    // and if lambda returns true
    // count increases by 1
    // [=] is the capture clause it means lambda has access to all outer elements
    // [] -> cannot use any variables from the outer function (scope)
    size_t count_found = std::count_if(all_logs.begin(), all_logs.end(),

                                       [=](const log &lg) { // we used log &lg because each element inside the vector is a log obj
                                                            // so for every element lamda receives reference to log object
                                           if (field == "level")
                                           {
                                               return lg.log_level == value;
                                               // If we query by level, compare log level
                                               // This comparison returns true or false.
                                           }
                                           else if (is_timestamp_query)
                                           {
                                               // Ensure user_time_point was parsed successfully before using it
                                               if (!user_time_point)
                                                   return false; // Should not happen due to check above, but safe

                                               // Compare the time_point objects directly
                                               if (op == ">")
                                               {
                                                   return lg.timestamp_obj > user_time_point.value();
                                               }
                                               else if (op == "<")
                                               {
                                                   return lg.timestamp_obj < user_time_point.value();
                                               }
                                               else if (op == "=" || op == "==")
                                               {
                                                   return lg.timestamp_obj == user_time_point.value();
                                               }

                                               else if (op == ">=")
                                               {
                                                   return lg.timestamp_obj >= user_time_point.value();
                                               }
                                               else if (op == "<=")
                                               {
                                                   return lg.timestamp_obj <= user_time_point.value();
                                               }

                                               return false; // unknown operator
                                           }
                                           else if (field == "ip_address")
                                           {
                                               return lg.ip_address == value;
                                           }

                                           // if we query by something else that we dont have,
                                           // so we return true.
                                           return false;
                                       });

    // (const log& lg) is the paramete for each element in the
    // vector std::count_if will call this lambda and pass the
    // log entry into this parameter.
    return count_found;
    // return final count
}

std::vector<log> log_query::list_where(const std::string &field, const std::string &op, const std::string &value) const
// this function return an vector which has all the matching infos
{

    std::optional<std::chrono::system_clock::time_point> user_time_point;
    bool is_timestamp_query = (field == "timestamp");
    if (is_timestamp_query)
    {
        user_time_point = parse_time_stamp(value);
        if (!user_time_point)
        {
            return {};
            // we return an empty vector
        }
    }
    std::vector<log> matches_found;
    auto &reference = ref.get_logs();
    // reference of our log_vector to search for
    // std::back_inserter(matches_founnd) allows copy_if to add new elements to the end of your results.
    // std::copy_if directly inserts matching elements into matches_found via the std::back_inserter.
    std::copy_if(reference.begin(), reference.end(), std::back_inserter(matches_found), [=](const log &lg)
                 {
                     if (field == "level")
                     {
                         return lg.log_level == value;
                         // if matches add that log obj to the back of result vector
                     }
                     else if (is_timestamp_query) {
                        if (!user_time_point) return false;
                        if (op == ">")  return lg.timestamp_obj > *user_time_point;
                        if (op == "<")  return lg.timestamp_obj < *user_time_point;
                        if (op == "=" || op == "==") return lg.timestamp_obj == *user_time_point;
                        if (op == ">=") return lg.timestamp_obj >= *user_time_point;
                        if (op == "<=") return lg.timestamp_obj <= *user_time_point;
                        return false; // Unknown operator
                     }
                    else if (field == "ip_address") {
                        return lg.ip_address == value;
                    }

                 

                     return false; });
    return matches_found;
    // dont return this by ref as it is an local varible of the function
    // we will encounter dangling reference is we return by reference
}

std::vector<std::pair<std::string, size_t>> log_query::topN(const std::string &field, size_t n) const
{
    auto &all_logs_ref = ref.get_logs();
    std::unordered_map<std::string, size_t> topn_hash;
    for (const auto &logs : all_logs_ref)
    {
        if (field == "ip_address")
        {
            // std::cout << "DEBUG: Processing IP = '" << logs.ip_address << "'\n";

            if (!logs.ip_address.empty())
            {
                topn_hash[logs.ip_address]++;
                // we cleverly log objects without ips
                // increases count
                // if doenst exist creates one and increments

                // std::cout << "added " << logs.ip_address << "\n";
                // to check if we really are adding non empty ips
            }
        }
        else if (field == "level")
        {
            topn_hash[logs.log_level]++;
            // Use the correct member name
        }
        else if (field == "message")
        {
            topn_hash[logs.message]++;
            // Use the correct member name
        }
    }

    // now lets create an vector to sort the keys of the map
    // we cant sort the map
    // we simply copy the key value pairs of the map into the vector of pairs
    // it happens easily as the key value pairs are copied into the pairs
    // each individual key value becomes the individual pair of vector

    std::vector<std::pair<std::string, size_t>> sortedN(topn_hash.begin(), topn_hash.end());
    // very imp we forgot to populate this vector and used sort which gave us an error
    // fix :- we simply populated it with all the key-value pairs into the pair elements of the object

    std::sort(sortedN.begin(), sortedN.end(),
              [](const auto &a, const auto &b)
              {
        // a and b are two pair objects from our vectr.
        // We want to sort by the count, which is the .second element of the pair.
        // a.second > b.second sorts in descending (highest to lowest) order.
        // Normally, std::sort sorts ascending (a < b).
        //By using a.second > b.second we do it in descending
        return a.second > b.second; });

    // reduce the vector to size of top n results
    if (sortedN.size() > n)
    {
        // If the vector is larger than n, resize it to be only n elements long.
        sortedN.resize(n);
    }
    return sortedN;
}
