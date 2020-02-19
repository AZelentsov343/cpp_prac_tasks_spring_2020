#include <iostream>

class A {
public:
    A() {
        int a;
        std::cin >> a;
        num = a;
    }

    A(A &a) {
        int b;
        std::cin >> b;
        a.copied = true;
        num = a.num + b;
    }

    ~A() {
        if (!copied) {
            std::cout << num << std::endl;
        }
    }

    int num;
    bool copied = false;
};
