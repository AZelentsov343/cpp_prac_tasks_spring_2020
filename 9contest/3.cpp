На вход подается описание грамматики в следующем виде: каждое правило состоит из двух символьных строк,
разделяемых произвольным количеством пробельных символов.
Грамматика представляет собой последовательность правил.
Таким образом, на вход подается четное число строк,
разделяемых произвольным количеством пробельных символов.

В строках допускаются:

Заглавные латинские буквы, обозначающие нетерминалы.
Строчные латинские буквы и цифры, обозначающие терминалы.
Символ подчеркивания, обозначающий пустую правую часть (эпсилон).
Символ подчеркивания может находится только в правой части правила,
в этом случае он является единственным символом в правой части.

Начальный нетерминал грамматики всегда 'S'.

Гарантируется, что входная грамматика — контекстно-свободная (в том числе укорачивающая),
то есть удовлетворяет правилам, описанным в задаче 'is-context-free'.

На стандартный поток вывода напечатайте:

2 если грамматика является контекстно-свободной,
но не неукорачивающей контекстно-свободной и не регулярной.
21 если грамматика является неукорачивающей контестно-свободной,
но не является регулярной.
31 если грамматика является леволинейной регулярной грамматикой, но не является левоавтоматной
311 если грамматика является левоавтоматной грамматикой
32 если грамматика является праволинейной регулярной грамматикой, но не является правоавтоматной
321 если грамматика являеся правоавтоматной грамматикой

В случае неоднозначности выводите меньший номер.

В леволинейной или праволинейной грамматике в правой части правил допускается
произвольное (в том числе нулевое) количество терминальных символов.
В лево- или право-автоматной грамматике в правой части правил
всегда должен присутствовать ровно один терминал.
Но в автоматной грамматике в качестве исключения допускаются
два правила для вывода пустой цепочки из S вида:

S _
S A
В этом случае грамматика со стартовым нетерминалом A должна быть автоматной в строгом смысле,
а нетерминал S не должен использоваться в правых частях правил.


Максимально ебучая задача, условие изложено непонятнее некуда, но вот решение


#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cctype>

int main() {
    bool was_s_empty = false;
    bool was_s_right = false;
    bool had_empty = false;

    bool left_regular = true;
    bool right_regular = true;
    bool left_auto = true;
    bool right_auto = true;

    bool auto_first_ex = false;
    bool auto_second_ex = false;

    char rule1;
    std::string rule2;

    while (std::cin >> rule1) {
        std::cin >> rule2;

        int countAZ = 0;
        for (char& c : rule2) {
            if (isupper(c)) {
                countAZ++;
            }
        }

        // non shortening
        if (rule2 == "_") {
            if (rule1 == 'S') {
                was_s_empty = true;
            } else {
                had_empty = true;
            }
        }

        if (rule2.find('S') != std::string::npos) {
            was_s_right = true;
        }

        //left regular
        if (not ((countAZ == 1 && isupper(rule2[0])) || countAZ == 0)) {
            left_regular = false;
        }

        //right_regular
        if (not ((countAZ == 1 && isupper(rule2[rule2.size() - 1])) || countAZ == 0)) {
            right_regular = false;
        }

        //auto
        if (rule1 != 'S') {
            //left auto
            if (not((rule2.size() == 2 && countAZ == 1 && isupper(rule2[0])) ||
                    (countAZ == 0 && rule2.size() == 1))) {
                left_auto = false;
            }

            //right auto
            if (not((rule2.size() == 2 && countAZ == 1 && isupper(rule2[1])) ||
                    (countAZ == 0 && rule2.size() == 1))) {
                right_auto = false;
            }
        } else {
            if (rule2 == "_") {
                if (auto_first_ex) {
                    left_auto = false;
                    right_auto = false;
                } else {
                    auto_first_ex = true;
                }
            } else if (rule2.size() == 1 && isupper(rule2[0])) {
                if (auto_second_ex) {
                    left_auto = false;
                    right_auto = false;
                } else {
                    auto_second_ex = true;
                }
            } else {
                if (auto_first_ex or auto_second_ex) {
                    left_auto = false;
                    right_auto = false;
                }
                if (not((rule2.size() == 2 && countAZ == 1 && isupper(rule2[0])) ||
                        (countAZ == 0 && rule2.size() == 1))) {
                    left_auto = false;
                }

                if (not((rule2.size() == 2 && countAZ == 1 && isupper(rule2[1])) ||
                        (countAZ == 0 && rule2.size() == 1))) {
                    right_auto = false;
                }
            }
        }
    } // while

    if (auto_second_ex and !auto_first_ex) {
        left_auto = false;
        right_auto = false;
    }

    if (auto_first_ex and was_s_right) {
        left_auto = false;
        right_auto = false;
    }

    if (left_auto && !had_empty) {
        std::cout << "311" << std::endl;
    } else if (right_auto && !had_empty) {
        std::cout << "321" << std::endl;
    } else if (left_regular) {
        std::cout << "31" << std::endl;
    } else if (right_regular) {
        std::cout << "32" << std::endl;
    } else if ((!had_empty && !was_s_empty) || (!had_empty && (was_s_empty && !was_s_right))) {
        std::cout << "21" << std::endl;
    } else {
        std::cout << "2" << std::endl;
    }

    return 0;
}