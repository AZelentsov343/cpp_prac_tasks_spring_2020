На вход подается описание грамматики в следующем виде: каждое правило состоит из двух символьных строк,
разделяемых произвольным количеством пробельных символов.
Грамматика представляет собой последовательность правил.
Таким образом, на вход подается четное число строк, разделяемых произвольным количеством пробельных символов.

В строках допускаются:

Заглавные латинские буквы, обозначающие нетерминалы.
Строчные латинские буквы и цифры, обозначающие терминалы.
Символ подчеркивания, обозначающий пустую правую часть (эпсилон).
Символ подчеркивания может находится только в правой части правила,
в этом случае он является единственным символом в правой части.

Начальный нетерминал грамматики всегда 'S'.

На стандартный поток вывода напечатайте:

-1 если входное описание грамматики не является грамматикой,
то есть не содержит правил, содержит только терминалы в левой части какого-либо правила,
не содержит правила с единственным нетерминалом 'S' в левой части.
2 если грамматика является контекстно-свободной, но не неукорачивающей контекстно-свободной.
23 если грамматика является неукорачивающей контестно-свободной.
10 в противном случае

В неукорачивающей КС-грамматике допускается единственная пустая правая часть правила для S при условии,
что S не встречается в правой части никаких правил.

В контекстно-свободной грамматике пустые правые части допускаются везде.

Examples

        Input

S abS
S ceA
A zA
A b

Output

23



#include <iostream>
#include <string>


int main() {
    std::string rule[2];
    int had_start = 0;
    int had_empty = 0;
    int is_ks = 1;
    int is_not_gram = 0;
    size_t count = 0;
    size_t count_AZ = 0;

    while (std::cin >> rule[0]) {
        std::cin >> rule[1];
        count++;

        if (rule[0] == "S") {
            had_start = 1;
        }

        if (rule[1] == "_") {
            had_empty = 1;
        }

        count_AZ = 0;
        for (const char& c : rule[0]) {
            if (c >= 'A' && c <= 'Z') {
                count_AZ++;
            }
        }

        if (count_AZ == 0) {
            is_not_gram = 1;
        }

        if (count_AZ != 1 or rule[0].size() > 1) {
            is_ks = 0;
        }
    }

    if (count == 0 or not had_start or is_not_gram) {
        std::cout << -1 << std::endl;
        return 0;
    }
    if (is_ks and not had_empty) {
        std::cout << 23 << std::endl;
        return 0;
    } else if (is_ks) {
        std::cout << 2 << std::endl;
        return 0;
    }

    std::cout << 10 << std::endl;
    return 0;
}