Напишите программу, моделирующую работу детерминированного конечного автомата (ДКА).
Описание автомата и входная строка вводятся на стандартном потоке ввода.
Результат работы автомата над данной строкой выводится на стандартный поток вывода.

Описание автомата задаётся в следующей форме.
Сначала задаётся функция перехода автомата.
Функция перехода задаётся в виде троек

CUR CHAR NEW
где CUR — идентификатор исходного состояния — произвольная символьная строка,
не содержащая пробельные символы.
CHAR — символьная строка длиной ровно 1 символ.
NEW — идентификатор целевого состояния — произвольная символьная строка,
не содержащая пробельные символы.
Элементы описания перехода могут отделятся друг от друга произвольным количеством пробельных символов.
Описание функции перехода завершается строкой END в качестве идентификатора исходного состояния.
Элементы CHAR и NEW отсутствуют.

Далее перечисляются заключительные состояния автомата.
Каждое состояние — это символьная строка.
Список состояний завершается символьной строкой END.

Далее задаётся начальное состояние автомата — символьная строка.
Затем задаётся проверяемое слово — символьная строка.
Все элементы входного файла могут отделяться друг от друга произвольным количеством пробельных символов.

Можете предполагать, что входные данные корректны,
то есть удовлетворяют спецификации и действительно задают детерминированный конечный автомат.

Результат работы автомата должен быть напечатан в следующем виде.
Сначала напечатайте число 1, если данный автомат допускает данную цепочку,
и 0 в противном случае. Затем напечатайте количество символов,
прочитанных во входной цепочке к моменту принятия автоматом решения
(текущий символ не считается прочитанным).
Наконец, напечатайте идентификатор состояния, в котором в данный момент находился автомат.

Examples

Input

A a A
A b B
B a C
B b B
C a C
END
B C END
A
aaabbbbba

Output
1
9
C

Input
A a A
A b B
B a C
B b B
C a C
END
B C END
A
abab

Output
0
3
C



#include <iostream>
#include <string>
#include <map>
#include <unordered_set>


int main() {

    std::string cur, newState;

    char curChar;

    std::map<std::pair<std::string, char>, std::string> rules;

    while (std::cin >> cur && cur != "END") {
        std::cin >> curChar >> newState;
        rules.insert({{cur, curChar}, newState});
    }

    std::unordered_set<std::string> endStates;

    while (std::cin >> cur && cur != "END") {
        endStates.insert(cur);
    }

    std::cin >> cur;

    std::string word;

    std::cin >> word;

    for (size_t i = 0; i < word.size(); ++i) {
        auto search = rules.find({cur, word[i]});
        if (search == rules.end()) {
            std::cout << 0 << std::endl << i << std::endl << cur << std::endl;
            return 0;
        } else {
            cur = search->second;
        }
    }

    if (endStates.find(cur) == endStates.end()) {
        std::cout << 0 << std::endl;
    } else {
        std::cout << 1 << std::endl;
    }
    std::cout << word.size() << std::endl << cur << std::endl;

    return 0;
}
