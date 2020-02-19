class Sub {
public:
    Sub(int a, int b) {
        num = a - b;
    }

    Sub(Sub s, int b) {
        num = s.value() - b;
    }

    Sub(int a, Sub s) {
        num = a - s.value();
    }

    int value() const {
        return num;
    }

private:
    int num;
};

