Программе на стандартном потоке ввода подаётся последовательность вещественных чисел —
результат серии экспериментов.
Последовательность содержит не менее 10 чисел.
Вычислите и выведите на стандартный поток вывода среднее арифметическое для нормализованной выборки.
Вещественные числа должны быть напечатаны с 10 десятичными знаками после точки.

Нормализованная выборка —
это выборка, у которой отброшены первые и последние 10% измерений (при вычислении 10% дробная часть отбрасывается),
затем у оставшейся выборки отбрасываются 10%
минимальных и максимальных значений
(вычисление 10% ведется от оставшейся после первого отбрасывания части выборки, дробная часть при этом отбрасывается).
Итого, в вычислениях участвует 64% от исходной выборки.

Для вычисления среднего арифметического используйте алгоритм for_each.
Не используйте глобальные переменные.
Не используйте анонимные (lambda) функции.
При нарушении ограничений решения будут дисквалифицированы.

Используйте минимальное число копирований элементов вектора.

Обратите внимание, что алгоритм for_each возвращает в качестве результата класс-функтор,
переданный ему третьим параметром.
Это можно использовать для накопления результата вычисления в классе-функторе.


#include <iostream>
#include <algorithm>
#include <vector>

class Count_avg {
public:
    explicit Count_avg(double sum = 0, size_t size = 0) : sum(0), cur_num(0), size(size) {}

    void operator()(double a) {
        cur_num++;
        sum += a;
        if (cur_num == size) {
            std::cout << (sum / size) << std::endl;
        }
    }

private:
    double sum;
    size_t cur_num;
    size_t size;
};


void normalize(std::vector<double> &v) {
    size_t ten_percent = v.size() / 10;
    v.erase(v.begin(), v.begin() + ten_percent);
    v.erase(v.end() - ten_percent, v.end());
}



int main() {
    std::vector <double> sampling;
    double sample;
    while (std::cin >> sample) {
        sampling.emplace_back(sample);
    }

    normalize(sampling);

    std::sort(sampling.begin(), sampling.end());

    normalize(sampling);

    Count_avg functor(0, sampling.size());

    for_each(sampling.begin(), sampling.end(), functor);
}
