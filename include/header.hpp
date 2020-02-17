// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <picosha2.h>
#include <thread>
#include <vector>
#include <mutex>
#include <cstring>
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/expressions/keyword.hpp>

#define SIZE_OF_RAND_STR 9
#define WHAT_YOU_NEED "0000"
#define SIZE_FILE 10*1024*1024
#define DIRECTORY "/tmp/log_%N.log"

using std::vector;
using std::string;
using std::mutex;
using std::thread;
namespace logging = boost::log;

class my_hash {
public:
    my_hash();
    explicit my_hash(unsigned input_num_of_threads);

//------------------------------------------------------

    void start();

//------------------------------------------------------

    void my_func();
    string random_string(const int len);
    void log_init();

//------------------------------------------------------

    vector<thread> multithread;
    unsigned num_of_threads;
    mutex my_lock;
};

#endif // INCLUDE_HEADER_HPP_
