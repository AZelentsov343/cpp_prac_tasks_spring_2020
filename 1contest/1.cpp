# 1
Напишите класс Sum таким образом, чтобы конструкция Sum(a, b).get() возвращала сумму двух целых параметров a, b. 
Конструкция Sum(Sum(a,b),c).get() должна возвращать сумму a, b и c.


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
