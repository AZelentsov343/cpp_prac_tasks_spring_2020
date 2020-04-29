Даны классы Figure, Rectangle, Square, Circle (см. предыдущие задачи).

Дополнительно для всех фигур определен метод to_string,
который возвращает строку std::string, описывающую данную фигуру.

Для класса Rectangle строка имеет вид

R WIDTH HEIGHT
Для класса Square строка имеет вид

S SIZE
Для класса Circle строка имеет вид

C RADUIS
Где WIDTH, HEIGHT, SIZE, RADUIS — соответствующие параметры фигуры.

Напишите программу. На стандартном потоке ввода подаются описания фигур,
строго по одной фигуре на строку текста. Строка описания фигуры имеет вид

TYPE PARAMS
Где TYPE — это R, S или C обозначающие соответствующие фигуры.
PARAMS — это параметры создания фигуры, без изменения передаваемые в функцию make.
Элементы в строке могут разделяться произвольным количеством пробельных символов.

На стандартный поток вывода выведите фигуры,
отсортированные в порядке возрастания площади фигур.
Если несколько фигур имеют равную площадь, сохраняется их относительный порядок из входных данных.

Указания

Не используйте глобальные переменные!

Для чтения строки текста из входного потока используйте std::getline.

Для покомпонентного чтения из строки можете использовать std::istringstream (опционально).

Для хранения фигур используйте std::vector. Для стабильной сортировки используйте stable_sort.

Не забывайте корректно освобождать всю динамическую память.

Реализуйте класс-фабрику классов для порождения объектов фигур.
Фабрика классов должна быть синглтоном.
Экземпляр синглтона должен возвращаться статической функцией factory_instance.

Дополнительно:

Для автоматического освобождения памяти можете использовать std::unique_ptr.

Чтобы не использовать if для проверки типа,
реализуйте фабрику классов на основе std::map и std::function.


#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>

class ClassFactory {
public:

    ClassFactory(const ClassFactory &) = delete;

    ClassFactory &operator=(const ClassFactory &) = delete;

    static ClassFactory &factory_instance() {
        static ClassFactory singleton;
        return singleton;
    }

    Figure *make(const std::string &str) {
        std::istringstream s(str);
        std::string type, next;
        s >> type;
        s >> next;

        if (type[0] == 'R') {
            std::string add;
            s >> add;
            return func_map['R'](next + " " + add);
        }
        return func_map[type[0]](next);
    }

private:

    std::map<char, std::function<Figure *(const std::string &)>> func_map;

    ClassFactory() {
        func_map['R'] = Rectangle::make;
        func_map['S'] = Square::make;
        func_map['C'] = Circle::make;
    }

    ~ClassFactory() = default;
};


bool compare(const std::unique_ptr<Figure> &first, const std::unique_ptr<Figure> &second) {
    return first->get_square() < second->get_square();
}

int main() {
    std::vector<std::unique_ptr<Figure>> figures;
    ClassFactory &factory = ClassFactory::factory_instance();
    std::string line;
    while (std::getline(std::cin, line)) {
        Figure *pointer = factory.make(line);

        figures.emplace_back(pointer);
    }

    std::stable_sort(figures.begin(), figures.end(), compare);

    for (auto &figure : figures) {
        std::cout << figure->to_string() << std::endl;
    }
}