Дан абстрактный класс Figure (см. предыдущую задачу).

Опишите классы Rectangle, Square, Circle, наследующие класс Figure.
Классы должны хранить параметры фигуры, а площадь каждый раз должна вычисляться.
Для окружности хранится ее радиус.

Для создания объектов соответствующих классов каждый класс должен определять статический метод make,
который в качестве параметра принимает строку std::string.
Метод make возвращает указатель на объект, созданный в куче.

Для класса Rectangle строка содержит два вещественных числа, разделенных пробелами,
а для классов Square и Circle — одно вещественное число.

За ошибки компиляции будут сниматься баллы.


#include <sstream>
#include <string>
#include <cmath>

class Rectangle : public Figure {
public:

    Rectangle(double height, double width) : height(height), width(width) {};


    double get_square() const final {
        return height * width;
    }

    static Rectangle *make(const std::string &str) {
        std::stringstream s(str);
        double height, width;
        s >> height;
        s >> width;
        return new Rectangle(height, width);
    }

private:
    double height;
    double width;
};


class Square : public Figure {
public:

    explicit Square(double size) : size(size) {}

    double get_square() const final {
        return size * size;
    }

    static Square *make(const std::string &str) {
        std::stringstream s(str);
        double size;
        s >> size;
        return new Square(size);
    }

private:
    double size;
};


class Circle : public Figure {
public:
    explicit Circle(double radius) : radius(radius) {}

    double get_square() const final {
        return M_PI * radius * radius;
    }

    static Circle *make(const std::string &str) {
        std::stringstream s(str);
        double rad;
        s >> rad;
        return new Circle(rad);
    }

private:
    double radius;
};
