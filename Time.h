#pragma once

class Time
{
    int day;
    int month;
    int year;
    int hour;
    int minute;

    // някак да направя функции за сравнение, конвертиране, изчисление на разлики, текущ час
};

void dateTimeToTimePoint(std::string date, std::string time)
{
    auto dateComponents = split(date, '/');
    auto timeComponents = split(time, ':');
    std::mt = 
    {
        0,
        0,
        std::atoi(timeComponents[0])
        
    }
    return;
}

// split("12/05/2022", '/') -> ["12", "05", "2022"]
// split("10:11", ':') -> ["10", "11"]
std::vector<std::string> split(const std::string& str, char delimiter)
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