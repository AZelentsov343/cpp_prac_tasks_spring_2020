Используйте только средства и библиотеки Си++ (например, boost.Date_Time).
Библиотеками языка Си и POSIX пользоваться запрещено.

sum of modules of differences

Examples

        Input

1985-10-26
1955-11-05
1955-11-12
1985-10-26
2015-10-21
Output

32848
Input

1990-01-01
1991-01-01
1990-01-01
Output

730


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/date_parsing.hpp>


int main() {
    boost::gregorian::date previous(boost::gregorian::not_a_date_time);
    boost::gregorian::date current(boost::gregorian::not_a_date_time);
    boost::date_time::months_of_year months[] = {boost::gregorian::Jan, boost::gregorian::Feb,
                                                 boost::gregorian::Mar, boost::gregorian::Apr,
                                                 boost::gregorian::May, boost::gregorian::Jun,
                                                 boost::gregorian::Jul, boost::gregorian::Aug,
                                                 boost::gregorian::Sep, boost::gregorian::Oct,
                                                 boost::gregorian::Nov, boost::gregorian::Dec};

    long long days_abs = 0;
    std::string s;
    std::cin >> s;

    std::istringstream str1_begin(s.substr(0, 4));
    std::istringstream str2_begin(s.substr(5, 2));
    std::istringstream str3_begin(s.substr(8, 2));
    int year, num_month, day;
    str1_begin >> year;
    str2_begin >> num_month;
    str3_begin >> day;

    previous = boost::gregorian::date(year, months[num_month - 1], day);

    while (std::cin >> s) {

        std::istringstream str1(s.substr(0, 4));
        std::istringstream str2(s.substr(5, 2));
        std::istringstream str3(s.substr(8, 2));
        str1 >> year;
        str2 >> num_month;
        str3 >> day;

        current = boost::gregorian::date(year, months[num_month - 1], day);

        days_abs += std::abs((previous - current).days());

        previous = current;
    }

    std::cout << days_abs << std::endl;
}