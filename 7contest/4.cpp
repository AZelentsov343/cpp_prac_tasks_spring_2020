Turing machine

(S, '0') → (S, '0', R)
(S, '1') → (A, '1', R)
(S, '#') → (S, '#', S)
(A, '0') → (A, '0', R)
(A, '1') → (S, '1', R)
(A, '#') → (B, '#', L)
(B, '0') → (B, '0', L)
(B, '1') → (B, '1', L)
(B, '#') → (C, '#', R)
(C, '0') → (C, '0', R)
(C, '1') → (D, '0', S)
(D, '0') → (D, '0', S)


#include <iostream>
#include <string>

enum State {A, B, C, D, S};

int main() {
    std::string machine;
    std::cin >> machine;
    ssize_t i = 0;
    State state = S;


    while (i >= 0 and i < static_cast<ssize_t >(machine.length())) {
        if (state == S) {
            if (machine[i] == '1') {
                state = A;
            }
            i++;
        } else if (state == A) {
            if (machine[i] == '0') {
                i++;
            } else if (machine[i] == '1') {
                state = S;
                i++;
            } else if (machine[i] == '#') {
                state = B;
                i--;
            }

        } else if (state == B) {
            if (machine[i] == '0') {
                i--;
            } else if (machine[i] == '1') {
                i--;
            } else if (machine[i] == '#') {
                state = C;
                i++;
            }

        } else if (state == C) {
            if (machine[i] == '0') {
                i++;
            } else if (machine[i] == '1') {
                machine[i] = '0';
                state = D;
                break;
            }
        } else if (state == D) {
            break;
        }
    }

    std::cout << machine << std::endl;

    return 0;
}
