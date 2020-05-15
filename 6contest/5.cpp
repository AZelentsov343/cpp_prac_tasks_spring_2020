В пространстве имен Equations определите шаблонную функцию quadratic,
решающую уравнение az2+bz+c=0 в поле комплексных чисел над любым вещественным типом,
поддерживаемым в заголовочном файле <complex>.
Функция принимает массив (std::array) v из трех
элементов комплексных коэффициентов уравнения (c - v[0], b - v[1], a - v[2]),
функция возвращает пару std::pair из булевского значения и вектора корней.
Булевское значение (first) равно false, если корней уравнения бесконечно много.
В противном случае first равно true и в векторе second возвращается вектор корней,
содержащий 0 элементов, если корней нет; 1 элемент,
если уравнение имеет один корень (то есть линейное);
2 элемента, если уравнение имеет два корня (возможно, равные).

Если на вход передается массив (std::array) другого размера или
массив не комплексных чисел - поведение функции не определено.

Дополнительно (по указанию преподавателя)
предусмотрите EPS для сравнения std::norm() с нулем равным 32 * epsilon() (см. std::numeric_limits).

Пример использования функции:

int main()
{
    using namespace std::complex_literals;

    std::array v1{ 1.0 + 2.0i, 2.0 + 0i, 3 + 1.3i };

    auto [res, v2] = Equations::quadratic(v1);
    std::cout << res;
}
Или для стандарта C++11:

int main()
{
    std::array<std::complex<double>, 3> v1{
            std::complex<double>(1.0, 2.0),
            std::complex<double>(2.0, 0),
            std::complex<double>(3, 1.3)
    };

    auto res = Equations::quadratic(v1);
    std::cout << res.first;
}

#####конец условия

#include <algorithm>
#include <complex>
#include <array>
#include <vector>

namespace Equations {

template <typename T>
std::pair<bool, std::vector<std::complex<T>>> quadratic(std::array<std::complex<T>, 3>& arr) {
    std::vector<std::complex<T>> v;
    auto a = arr[2];
    auto b = arr[1];
    auto c = arr[0];
    constexpr typename std::complex<T> zero(0, 0);
    constexpr typename std::complex<T> two(2, 0);
    constexpr typename std::complex<T> four(4, 0);

    if (a == zero) { //linear
        if (b == zero) {
            if (c == zero) { // 0 = 0
                return {false, v};
            } else { // no roots
                return {true, v};
            }
        } else { // b*x + c = 0 -> x = -c/b
            v.emplace_back(-c/b);
            return {true, v};
        }
    } else { //non-linear
        auto D = std::sqrt(b * b -  four * a * c);
        v.emplace_back((-b + D)/(two*a));
        v.emplace_back((-b - D)/(two*a));
        return {true, v};
    }
}

} //namespace Equations




