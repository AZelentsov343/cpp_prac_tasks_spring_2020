# 4
Программе в аргументах командной строки передаются:

Комплексное число C.
Вещественное число R.
Целое число N.
Остальные аргументы - запись функции одного комплексного аргумента в польской записи.
На стандартный поток вывода напечатайте комплексное число I -
результат вычисления криволинейного интеграла по замкнутому контуру - окружности с центром в точке C и радиусом R.

Для вычисления используйте метод прямоугольников. Для этого окружность делится на N частей.

В заголовочном файле cmc_complex.h находится реализация класса numbers::complex,
в заголовочном файле cmc_complex_stack.h находится реализация класса numbers::complex_stack,
в заголовочном файле cmc_complex_eval.h находится реализация функции eval.

#include <iostream>
#include <vector>
#include <cmath>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

int main(int argc, char *argv[]) {
    numbers::complex c(argv[1]);
    double r;
    sscanf(argv[2], "%lf", &r);
    int n;
    sscanf(argv[3], "%d", &n);

    std::vector<std::string> v;
    std::string s;
    for (int i = 4; i < argc; i++) {
        v.emplace_back(argv[i]);
    }

    numbers::complex z_prev;
    numbers::complex z_next;
    numbers::complex e;

    double arg = 2 * M_PI / n;
    double arg_e = M_PI / n;
    const numbers::complex wz(cos(arg), sin(arg));
    const numbers::complex we(cos(arg_e), sin(arg_e));


    numbers::complex result = 0.0;

    z_prev = r;
    for (int i = 0; i < n; i++) {
        z_next = z_prev * wz;
        e = z_prev * we;
        result += numbers::eval(v, e + c) * (z_next - z_prev);
        z_prev = z_next;
    }

    std::cout << result.to_string() << std::endl;


    return 0;
}
