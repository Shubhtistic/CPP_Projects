#pragma once
#include <vector>
#include <memory>
#include <string>
#include "log_vector.h"
#include "log_query.h"
#include "log_parser.h"
#include "simple_log_parser.h"

class log_parse_app
{
private:
    log_vector log_store;
    // to hold all the log data
    log_query query_engine;
    // to perform log analysis
    std::vector<std::unique_ptr<log_parser>> available_parsers;
    // this vector can hold any tyoe of log parser derived from log_parser.h abstract class

    void load_logFile();
    // to load an log file and parse it
    log_parser *select_parser();
    // pointer to log_parse abtract class so it can return any class derived from log_parser interface
    void run_queryLoop();

public:
    log_parse_app();
    // we will define this in .cpp
    void run();
};
