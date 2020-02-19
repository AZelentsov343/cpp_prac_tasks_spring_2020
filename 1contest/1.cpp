class Sum {
public:
    Sum(int a, int b) {
        sum = a + b;
    }

    Sum(const Sum s, int c) {
        sum = s.get() + c;
    }

    int get() const {
        return sum;
    }

private:
    int sum;
};
