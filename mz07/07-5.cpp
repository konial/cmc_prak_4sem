#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

enum state {YEAR, MONTH, DAY};

void parse_date(int &year, int &month, int &day, const std::string &str)
{
    state st = YEAR;
    for (int i = 0; i < (int)str.size(); ++i) {
        switch (st) {
        case YEAR:
            if (str[i] == '-') {
                st = MONTH;
            }
            else {
                year *= 10;
                year += str[i] - '0';
            }
            break;
        case MONTH:
            if (str[i] == '-') {
                st = DAY;
            }
            else {
                month *= 10;
                month += str[i] - '0';
            }
            break;
        case DAY:
            day *= 10;
            day += str[i] - '0';
            break;
        }
    }
}

int main() {
    std::string str;
    boost::gregorian::date begin_date;
    unsigned duration = 0;
    bool flag = false;
    while (std::cin >> str) {
        int year = 0, month = 0, day = 0;
        parse_date(year, month, day, str);

        boost::gregorian::date end_date(year, month, day);
        if (flag) {
            if (end_date < begin_date) {
                boost::gregorian::date_period dif(end_date, begin_date);
                duration += dif.length().days();
            } else {
                boost::gregorian::date_period dif(begin_date, end_date);
                duration += dif.length().days();
            }
        }
        flag = true;
        begin_date = end_date;
    }
    std::cout << duration << std::endl;

    return 0;
}
