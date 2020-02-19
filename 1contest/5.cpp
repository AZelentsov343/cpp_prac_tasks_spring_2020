#include <iostream>

class Holder;

int main() {
    int count;
    std::cin >> count;
    auto a = new Holder[count]();


    for (int i = 0; i < count / 2; i++) {
        a[i].swap(a[count - (i + 1)]);
    }

    delete[] a;
    return 0;
}

