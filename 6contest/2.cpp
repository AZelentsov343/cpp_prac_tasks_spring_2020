Дано прямоугольное поле размером m строк на n столбцов клеток.
Левая нижняя клетка поля имеет координаты (0,0), правая верхняя клетка поля — (m - 1,n - 1).

Поле закольцовано в тор, то есть склеены верхняя и нижняя границы поля и правая и левая границы поля.

Из некоторой клетки можно перейти за один ход в любую из восьми соседних клеток.
Например, из клетки (1,2) можно перейти в клетки (0,2), (2,2), (1,1), (1,3), (0, 1), (0, 3), (2, 1), (2, 3).

Расстояние между двумя клетками — это минимальное число ходов,
за которое можно перейти из одной клетки в другую.

Напишите шаблонный класс Coord, параметризованный типом координат.
Класс должен содержать открытый тип value_type,
открытые поля row, col и открытый конструктор от 0, 1 или 2 аргументов.

Напишите шаблонну функцию dist, принимающую три параметра:
размеры поля, две координаты клеток, которая вычисляет расстояние между двумя клетками.


#include <cmath>
#include <algorithm>

template <typename value_type>
class Coord {
public:
    explicit Coord(value_type row = 0, value_type col = 0) : row(row), col(col) {};
    value_type row, col;
};


template <typename value_type>
value_type dist_btw_coord(value_type r1, value_type r2, value_type m) {
    value_type first_var = abs(r1 - r2);
    value_type second_var;
    if (r1 >= r2) {
        second_var = (m + r2) - r1;
    } else {
        second_var = (m + r1) - r2;
    }
    return std::min(first_var, second_var);
}

template <typename value_type>
value_type dist(Coord<value_type> field, Coord<value_type> a, Coord<value_type> b) {
    value_type vert = dist_btw_coord(a.row, b.row, field.row);

    value_type horiz = dist_btw_coord(a.col, b.col, field.col);
    return std::max(vert, horiz);
}
