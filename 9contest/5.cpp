На вход подается описание КС-грамматики в следующем формате:

<левая часть> <правая часть>

где <...> – строки, состоящие из цифр, строчных и заглавных латинских символов,
а также символа ‘_’, означающего пустую цепочку (эпсилон).

Строчные символы и цифры – терминальные (из Т).
Заглавные – нетерминальные (из N).
Правила грамматики задаются не в сокращенной форме.

На выходе программа должна вывести:
правила эквивалентной грамматики без недостижимых символов не в сокращенной форме.

Пример

Вход

S a
S Bc
D e

Выход

S a
S Bc



#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>


int main() {

    std::vector<std::pair<char, std::string>> rules;

    char rule1;
    std::string rule2;

    while (std::cin >> rule1) {
        std::cin >> rule2;
        rules.emplace_back(rule1, rule2);
    }

    std::unordered_set<char> v;
    v.insert('S');

    bool v_changed = true;

    while (v_changed) {
        v_changed = false;
        for (auto& rule : rules) {
            if (v.find(rule.first) != v.end()) {
                for (char& c : rule.second) {
                    if (c >= 'A' and c <= 'Z' and v.find(c) == v.end()) {
                        v.insert(c);
                        v_changed = true;
                    }
                }
            }
        }
    }

    for (auto& rule : rules) {
        if (v.find(rule.first) != v.end()) {
            std::cout << rule.first << ' ' << rule.second << std::endl;
        }
    }

    return 0;
}
