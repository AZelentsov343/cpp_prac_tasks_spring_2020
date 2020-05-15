
Дан язык L={(0^k1^m)^n}, k > 0, m > 0, n > 0 }.
То есть язык состоит из слов (цепочек) из символов 0 и 1, таких,
что первая группа нулей и единиц далее повторяется с тем же числом нулей и единиц произвольное число раз.

На стандартном потоке подаются строки, разделяющиеся пробельными символами.
Для каждой строки на стандартный поток вывода напечатайте 1, если строка принадлежит языку, и 0 в противном случае.

Examples

        Input

01
010101
000011000011000011 00001100011000011
Output

1
1
1
0


Если вводить всю строку целиком через std::cin >> string, а не посимвольно, ловишь Memory limit exceeded


#include <iostream>
#include <cctype>


int main() {

    int next;

    while (true) {
        while ((next = getchar()) && isspace(next)) {}
        if (next == EOF) {
            break;
        }

        if (next != '0') {
            while ((next = getchar()) && next != EOF && !isspace(next)) {}
            std::cout << 0 << std::endl;
            continue;
        }
        int zeros_count = 1;
        while ((next = getchar()) && next == '0') {
            zeros_count++;
        }
        if (next != '1') {
            if (!isspace(next) and next != EOF) {
                while ((next = getchar()) && next != EOF && !isspace(next)) {}
            }
            std::cout << 0 << std::endl;
            continue;
        }
        int ones_count = 1;
        while ((next = getchar()) && next == '1') {
            ones_count++;
        }
        if (next == EOF) {
            std::cout << 1 << std::endl;
            break;
        }

        if (isspace(next)) {
            std::cout << 1 << std::endl;
            continue;
        }
        if (next != '0') {
            if (!isspace(next)) {
                while ((next = getchar()) && next != EOF && !isspace(next)) {}
            }
            std::cout << 0 << std::endl;
            continue;
        }
        bool flagOK = true;
        bool exited_with_space = false;
        while (true) {
            for (int i = 1; i < zeros_count; ++i) {
                next = getchar();
                if (next == EOF) {
                    flagOK = false;
                    break;
                }
                if (next != '0') {
                    flagOK = false;
                    break;
                }
            }
            if (not flagOK) {
                exited_with_space = isspace(next);
                break;
            }
            for (int i = 0; i < ones_count; ++i) {
                next = getchar();
                if (next == EOF) {
                    flagOK = false;
                    break;
                }
                if (next != '1') {
                    flagOK = false;
                    break;
                }
            }
            if (not flagOK) {
                exited_with_space = isspace(next) or (next == EOF);
                break;
            }
            next = getchar();
            if (next == EOF or isspace(next)) {
                break;
            }
            if (next != '0') {
                flagOK = false;
                exited_with_space = isspace(next) or next == EOF;
                break;
            }
        }
        if (flagOK) {
            std::cout << 1 << std::endl;
        } else if (!exited_with_space) {
            while ((next = getchar()) && next != EOF && !isspace(next)) {}
            std::cout << 0 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }

    }
    return 0;
}
