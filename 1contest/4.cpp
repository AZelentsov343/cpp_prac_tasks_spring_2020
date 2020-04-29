# 4
На стандартном потоке ввода задаётся непустая последовательность вещественных чисел.

На стандартный поток вывода напечатайте среднее значение элементов последовательности и среднее квадратичное отклонение. Числа выводите с 10 знаками после десятичной точки.

Используйте средства ввода-вывода языка Си++. Для вывода числа используйте setprecision.

Не храните введенную последовательность чисел в памяти, то есть не используйте vector, list и т. п.

#include <iostream>
#include <iomanip>
#include <cmath>


int main() {
    long double mean = 0.0, stddev = 0.0;
    long double a;
    long long count = 0;
    while (true) {
        std::cin >> a;
        if (std::cin.eof()) {
            break;
        }

        stddev += a * a;
        mean += a;
        count++;
    }

    mean /= (long double)(count);

    stddev /= (long double)(count);
    stddev -= mean * mean;
    stddev = sqrt(stddev);

    std::cout << std::fixed;
    std::cout << std::setprecision(10) << mean << std::endl;
    std::cout << std::setprecision(10) << stddev << std::endl;
    return 0;
}

