# 5
Дан класс Holder:

#include <iostream>

class Holder
{
    int value = 0;

public:
    Holder()
    {
        std::cin >> value;
    }

    ~Holder()
    {
        std::cout << value << std::endl;
    }

    void swap(Holder &other)
    {
        int tmp = value;
        value = other.value;
        other.value = tmp;
    }
};
Напишите функцию main, которая считает сначала целое число count — количество целых чисел в последовательности целых чисел, затем саму последовательность целых чисел, которая должна быть сохранена в памяти в объектах класса Holder. Затем последовательность введенных чисел должна быть выведена на стандартный поток вывода в том же порядке, в котором числа были введены.

Запрещается использовать стандартную библиотеку языка Си++ (то есть подключать любые заголовочные файлы), кроме однократного чтения параметра count:

int main()
{
    int count;
    std::cin >> count;

    // далее стандартную библиотеку использовать нельзя
}
Копирование и перенос объектов класса Holder запрещены.

На проверку сдавайте только функцию main.

#include <iostream>

class Holder;

int main() {
    int count;
    std::cin >> count;
    auto a = new Holder[count]();


    for (int i = 0; i < count / 2; i++) {
        a[i].swap(a[count - (i + 1)]);
    }

    delete[] a;
    return 0;
}

