Дан язык L={αβ}, где α={3,4}^n, β={1,2}^m, n >= 0, m >= 0.

На стандартном потоке подаются строки, разделяющиеся пробельными символами.
Для каждой строки на стандартный поток вывода напечатайте 1, если строка принадлежит языку, и 0 в противном случае.


#include <iostream>
#include <string>

int is_from_L(const std::string& s) {
    bool changed = false;
    for (const char& c : s) {
        if (not changed) {
            if (c == '1' or c == '2') {
                changed = true;
            } else if (c != '3' and c != '4') {
                return 0;
            }
        } else {
            if (c != '1' and c != '2') {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    std::string s;
    while (std::cin >> s) {
        std::cout << is_from_L(s) << std::endl;
    }

    return 0;
}