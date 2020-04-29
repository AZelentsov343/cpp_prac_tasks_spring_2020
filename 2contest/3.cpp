# 3

В пространстве имен numbers реализуйте функцию eval с прототипом:

complex eval(const std::vector<std::string> &args, const complex &z);
Функции подается на вход польская инверсная запись выражения над комплексными числами с одной переменной и
значение переменной. В качестве результата функция возвращает вычисленное значение.

Каждый элемент польской записи находится в отдельном элементе вектора.

Возможные ошибки при вычислении игнорируйте.

Вы должны сдать только функцию eval.

В польской записи допускаются следующие элементы:

Запись комплексного числа в виде (RE,IM) (см. предыдущие задачи).
Обозначение переменной "z" (строчная латинская буква).
Знаки бинарных операций +, -, *, /.
Знак унарной операции !, которая заносит в стек элемент, находящийся на верхушке стека.
Знак унарной операции ;, которая удаляет элемент с верхушки стека.
Знак унарной операции ~, которая вычисляет комплексно-сопряженное число.
Знак унарной операции #, которая меняет знак у числа.
Обратите внимание, что польская запись z1 z2 - обозначает (z1 - z2), а не (z2 - z1)!

Каждая строка в массиве строк содержит ровно один элемент польской записи. Пробельные символы отсутствуют.

Реализуйте отображение из операций в действия с помощью отображения (std::map) анонимных функций.

#include <map>
#include <vector>

namespace numbers {

    auto plus = [](const complex& a, const complex& b) { return a + b; };
    auto minus = [](const complex& a, const complex& b) { return a - b; };
    auto multiply = [](const complex& a, const complex& b) { return a * b; };
    auto divide = [](const complex& a, const complex& b) { return a / b; };

    std::map<char, complex(*)(const complex&, const complex&)> funcs = {
            {'+', plus},
            {'-', minus},
            {'*', multiply},
            {'/', divide}
    };

    complex eval(const std::vector<std::string> &args, const complex &z) {
        complex_stack stack;

        complex z1;
        complex z2;

        for (auto const& s: args) {
            auto search = funcs.find(s[0]);
            if (search != funcs.end()) {
                z1 = +stack;
                stack = ~stack;
                z2 = +stack;
                stack = ~stack;
                z1 = search->second(z2, z1);
                stack = stack << z1;
            } else if (s[0] == '#') {
                z1 = +stack;
                stack = ~stack;
                stack = stack << (-z1);
            } else if (s[0] == '!') {
                z1 = +stack;
                stack = stack << z1;
            } else if (s[0] == 'z') {
                stack = stack << z;
            } else if (s[0] == '~') {
                z1 = +stack;
                stack = stack << (~z1);
            } else if (s[0] == ';') {
                stack = ~stack;
            } else {
                complex z3(s);
                stack = stack << z3;
            }
        }

        return +stack;
    }


}

