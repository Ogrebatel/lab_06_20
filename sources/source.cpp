// Copyright 2018 Your Name <your_email>

#include <header.hpp>

my_hash::my_hash():
        num_of_threads(thread::hardware_concurrency()){}

my_hash::my_hash(unsigned input_num_of_threads):
        num_of_threads(input_num_of_threads){}

void my_hash::start(){
    log_init();
    for (unsigned i = 0; i < num_of_threads; ++i)
        multithread.emplace_back(thread(&my_hash::my_func, this));

    for (unsigned i = 0; i < num_of_threads; ++i)
        multithread[i].join();
}

void my_hash::my_func()
{
    string s;
    while(true) {
        s = random_string(rand() % SIZE_OF_RAND_STR + 1);
        string sha = picosha2::hash256_hex_string(s);
        bool is_right_format =
                (sha.find(WHAT_YOU_NEED) == (sha.size() - strlen(WHAT_YOU_NEED)));

        my_lock.lock();

        if(is_right_format) {
            BOOST_LOG_TRIVIAL(info) << sha << " " << s;
            my_lock.unlock();
            break;
        } else{
            BOOST_LOG_TRIVIAL(trace) << sha << " " << s;
            my_lock.unlock();
        }

    }
}

string my_hash::random_string(const int len) {

    static const char alph[] =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "1234567890";
    string s;
    for (int i = 0; i < len; ++i) {
        char tmp = alph[rand() % (sizeof(alph) - 1)];
        s = s + tmp;
    }
    return s;
}

void my_hash::log_init()
{
    boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
    logging::add_file_log // расширенная настройка
            (
                    logging::keywords::file_name = "./log_%N.log",
                    logging::keywords::rotation_size = SIZE_FILE,
                    logging::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point{0, 0, 0},
                    logging::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
            );

    logging::add_console_log
            (
                    std::cout,
                    logging::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%]: %Message%"
            );
    logging::add_common_attributes();
}
