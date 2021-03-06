Опишите абстрактный класс Figure, который будет корнем полиморфной иерархии классов,
описывающих двухмерные фигуры.

Класс должен определять метод get_square для перекрытия в производных классах.
Метод будет возвращать площадь соответствующей фигуры.


class Figure {
public:
    virtual double get_square() const = 0;
    virtual ~Figure() = default;
};
