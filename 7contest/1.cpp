На стандартном потоке ввода подается последовательность строк,
состоящих из непробельных символов и разделенных пробельными символами.
Напечатайте эту последовательность в обратном порядке по одной строке на одной строке выходного текстового файла.

Не используйте ни массивов, ни других контейнерных классов (вектор).
Допускается без изменений хранить входную строку в std::string.
Выход из рекурсии должен выполняться с помощью исключения.
Выход из рекурсивной функции с помощью явного или неявного return запрещен.
Печать строки должна выполняться в деструкторе некоторого класса при обработке исключения (свертке стека).


#include <iostream>
#include <string>
#include <exception>

class StrangeRecursion {
public:
    explicit StrangeRecursion(std::string  s) : _data(std::move(s)) {}

    ~StrangeRecursion() {
        std::cout << _data << std::endl;
    }

private:
    std::string _data;
};

void very_strange_rec() {
    std::string data;
    if (std::cin >> data) {
        try {
            very_strange_rec();
        } catch (StrangeRecursion& st) {
            throw StrangeRecursion(data);
        } catch (std::exception& ex) {
            throw StrangeRecursion(data);
        }
    } else {
        throw std::exception();
    }
}

int main() {
    std::string first;
    std::cin >> first;
    try {
        very_strange_rec();
    }
    catch (StrangeRecursion& st) {}
    catch (std::exception& ex) {}
    std::cout << first << std::endl;
}