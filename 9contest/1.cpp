Язык L задается с помощью грамматики:

S = aXPQ
P = YXP | ε
Q = UVQ | ε
aY = aa
aU = a0
0U = 00
0X = 0b
bX = bb
bV = b1
1V = 11
XY = YX
UY = YU
VY = YV
XU = UX
VU = UV
VX = XV
Нетерминальные символы обозначаются заглавными буквами,
а терминальные символы — строчными буквами и цифрами.
Начальный нетерминал — S.

На стандартном потоке подаются строки, разделяющиеся пробельными символами.
Для каждой строки на стандартный поток вывода напечатайте 1,
если строка принадлежит языку, и 0 в противном случае.

Указание: определите тип языка и преобразуйте грамматику к соответствующему типу.
Грамматику запишите в комментарии в начале программы.


#include <iostream>
#include <string>

/* KZ grammar
 * S = aXPQ | aXP | aXQ
 * P = YXP | YX
 * Q = UVQ | UV
 * aY = aa
 * aU = a0
 * 0U = 00
 * 0X = 0b
 * bX = bb
 * bV = b1
 * 1V = 11
 * XY = XA
 * XA = YA
 * YA = YX
 * XU = XD
 * XD = UD
 * UD = UX
 */

enum State {
    H, A, ZERO, B, ONE
};


int analyze(const std::string& s) {
    int count_a = 0;
    int count_b = 0;
    int count_zeros = 0;
    int count_ones = 0;
    State state = H;

    for (const char& c : s) {
        if (state == H) {
            if (c == 'a') {
                count_a = 1;
                state = A;
            } else {
                return 0;
            }
        } else if (state == A) {
            if (c == 'a') {
                count_a++;
            } else if (c == '0') {
                count_zeros = 1;
                state = ZERO;
            } else {
                return 0;
            }
        } else if (state == ZERO) {
            if (c == '0') {
                count_zeros++;
            } else if (c == 'b') {
                count_b = 1;
                state = B;
            } else {
                return 0;
            }
        } else if (state == B) {
            if (c == 'b') {
                count_b++;
            } else if (c == '1') {
                count_ones = 1;
                state = ONE;
            } else {
                return 0;
            }
        } else { // state == ONE
            if (c == '1') {
                count_ones++;
            } else {
                return 0;
            }
        }
    }
    return count_a > 0 && count_zeros > 0 && count_a == count_b && count_zeros == count_ones;
}


int main() {
    std::string sequence;
    while (std::cin >> sequence) {
        std::cout << analyze(sequence) << std::endl;
    }
}