# 3
Напишите класс Sub таким образом, чтобы для двух целых параметров (типа int) a, b конструкция Sub(a, b).value() возвращала разность a, b. 
Конструкция Sub(Sub(a,b),c).value() должна возвращать разность a − b − c.

В классе Sub должно быть определено не более трёх конструкторов.

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

