Напишите шаблонную функцию myapply,
которая принимает два итератора на начало и конец обрабатываемой последовательности, и функцию f.
Шаблонная функция myapply применяет заданную функцию ко все элементам в заданном диапазоне итерации.

Напишите функцию myfilter2,
которая принимает два итератора на начало и конец обрабатываемой последовательности, и предикат f.
Функция myfilter2 возвращает вектор ссылок на элементы входной обрабатываемой последовательности,
которые удовлетворяют заданному предикату.

Если к вектору ссылок, который вернула функция myfilter2, применить myapply,
то в случае модификации элементов последовательности в функции, переданной в myapply,
на самом деле изменятся элементы, обрабатываемой последовательности,
переданной при получении вектора ссылок в функцию myfilter2.

Шаблонные функции должны быть применимы к массивам.

Используйте std::reference_wrapper. Стандартными алгоритмами пользоваться запрещено.


#include <vector>
#include <functional>

template <typename IT, typename F>
void myapply(IT begin, IT end, F func) {
    for (auto it = begin; it != end; ++it) {
        func(*it);
    }
}

template <typename pointer_type, typename P>
auto myfilter2(pointer_type *begin, pointer_type *end, P f) {

    std::vector<std::reference_wrapper<pointer_type>> result;

    for (auto pointer = begin; pointer != end; ++pointer) {
        if (f(*pointer)) {
            result.push_back(*pointer);
        }
    }

    return result;
}

template <typename IT, typename P>
auto myfilter2(IT begin, IT end, P f) {

    std::vector<std::reference_wrapper<typename IT::value_type>> result;

    for (auto it = begin; it != end; ++it) {
        if (f(*it)) {
            result.push_back(*it);
        }
    }
    return result;
}
