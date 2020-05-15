Дано прямоугольное поле из гексагональных элементов (см. рис) размером m строк на n столбцов клеток.
Координаты шестиугольников определяются, как показано на рисунке.

hexagons
Из некоторой клетки можно перейти за один ход в любую из шести соседних клеток.

Расстояние между двумя клетками — это минимальное число ходов,
за которое можно перейти из одной клетки в другую.

В пространстве имен Game напишите шаблонный класс Coord, параметризованный типом координат.
Класс должен содержать открытый тип value_type,
открытые поля row, col и открытый конструктор от 0, 1 или 2 аргументов.

В пространстве имен Game напишите шаблонную функцию dist, принимающую три параметра:
размеры поля, две координаты клеток, которая вычисляет расстояние между двумя клетками.


#include <cmath>
#include <algorithm>

namespace Game {

template<typename value_type>
class Coord {
public:
    explicit Coord(value_type row = 0, value_type col = 0) : row(row), col(col) {};
    value_type row, col;
};

template<typename value_type>
value_type dist(Coord<value_type> field, Coord<value_type> first, Coord<value_type> second) {
    value_type distance_square = abs(first.col - second.col);
    value_type angle_moves = distance_square / 2;

    value_type addition(0);

    if (distance_square % 2 && second.col % 2 && ((second.row > first.row && second.col > first.col)
    || (second.row > first.row && second.col < first.col))) {
        ++addition;
    } else if (distance_square % 2 && first.col % 2 && ((second.row < first.row && second.col < first.col)
    || (second.row < first.row && second.col > first.col))) {
        ++addition;
    }

    value_type rows = abs(first.row - second.row);
    return distance_square + rows - std::min(rows, angle_moves + addition);
}
} //namespace Game
