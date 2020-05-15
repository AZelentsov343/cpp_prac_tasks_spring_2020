Реализуйте класс S следующим образом:

Класс хранит целое число (типа int).
Число считывается со стандартного потока ввода в конструкторе.
Число выводится на стандартный поток вывода в деструкторе.
Следующая программа:
using namespace std;
void func(S v)
{
    if (v) {
        func(move(v));
    }
}

int main()
{
    func(S());
}
считывает последовательность целых чисел и выводит на стандартный поток вывода их сумму.
Если входная последовательность пустая, программа не выводит ничего.
Проверка на переполнение не требуется.

Глобальные переменные, static, mutable запрещены.

Сдаваемый на проверку класс должен подключать необходимые заголовочные файлы.


#include <iostream>

class S {
public:
    S() {
        if (std::cin >> _data) {
            got_number = true;
            should_print = true;
        } else {
            _data = 0;
            got_number = false;
            should_print = false;
        }
    }

    ~S() {
        if (should_print and not got_number) {
            std::cout << _data << std::endl;
        }
    }

    S(S&& other) noexcept {
        int a;
        if (std::cin >> a) {
            _data = other._data + a;
            got_number = true;
        } else {
            _data = other._data;
            got_number = false;
        }
        should_print = true;
    }

    operator bool() {
        return got_number;
    }

private:
    int _data;
    bool got_number;
    bool should_print;
};