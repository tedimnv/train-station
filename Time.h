#pragma once
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>

class Time
{
    int day;
    int month;
    int year;
    int hour;
    int minute;

};

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

static const char * TIME_FORMAT= "%d/%m/%Y %H:%M";

static inline TimePoint parseTime(std::istream & is)
{
    std::tm tm = {};
    is >> std::get_time(&tm, TIME_FORMAT);
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

static inline TimePoint getCurrentTime()
{
    return std::chrono::system_clock::now();
}

static inline void printTime(TimePoint tp)
{
    std::time_t time_t = std::chrono::system_clock::to_time_t(tp);
    std::cout << std::put_time(std::localtime(&time_t), TIME_FORMAT);
}

// split("12/05/2022", '/') -> ["12", "05", "2022"]
// split("10:11", ':') -> ["10", "11"]
static inline std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::istringstream ss(str);
    std::string word;
    std::vector<std::string> result;
    while(std::getline(ss, word, delimiter))
    {
        result.push_back(word);
    }
    return result;
}