Дан язык L, порождаемый следующей грамматикой:
S → C0 | C1
A → A0 | A1 | 0 | 1
B → A1 | 1
C → B0 | B1

На стандартном потоке подаются строки, разделяющиеся пробельными символами.
Для каждой строки на стандартный поток вывода напечатайте 1,
если строка принадлежит языку, и 0 в противном случае.

Для анализа строк используйте лексический анализатор (конечный автомат).



#include <iostream>
#include <string>


enum State {
    H, A, AB, AC, ABC, AS, ABS, ACS, ABCS
};


int analyze(const std::string& s) {
    State state = H;
    for (const char& c : s) {
        if (c != '0' and c != '1') {
            return 0;
        }
        switch (state) {
            case H:
                state = c == '0' ? A : AB; break;
            case A:
                state = c == '0' ? A : AB; break;
            case AB:
                state = c == '0' ? AC : ABC; break;
            case AC:
                state = c == '0' ? AS : ABS; break;
            case ABC:
                state = c == '0' ? ACS : ABCS; break;
            case AS:
                state = c == '0' ? A : AB; break;
            case ABS:
                state = c == '0' ? AC : ABC; break;
            case ACS:
                state = c == '0' ? AS : ABS; break;
            case ABCS:
                state = c == '0' ? ACS : ABCS; break;
        }
    }
    return state == AS or state == ABS or state == ACS or state == ABCS;
}


int main() {
    std::string sequence;
    while (std::cin >> sequence) {
        std::cout << analyze(sequence) << std::endl;
    }
}