Напишите шаблонный класс Range, который реализует поддержку диапазонов любых знаковых целых чисел.

Класс должен иметь поля low и high,
класс представляет целые значения в диапазоне [low,high] (границы включены).

Определите конструктор по умолчанию, от одного и двух целых аргументов.
Недостающие аргументы равны значению по умолчанию.
Если нарушено условие low <= high, должно выбрасываться исключение std::invalid_argument.

Определите явный (explicit) конструктор из строки std::string,
который преобразует строку в формате (LOW,HIGH) в значение класса,
где LOW, HIGH — значения типа носителя, причем low <= high.
В случае ошибки преобразования должно выбрасываться исключение std::invalid_argument.
В случае ошибки переполнения должно выбрасываться исключение std::range_error.
Пробельные символы в формате отсутствуют. (но это не точно)

Определите метод to_string для преобразования в строку std::string,
который использует формат преобразования, описанный выше.

Определите методы get_low, get_high.

Определите бинарные операции +, - и * и унарную операцию -.
Результатом операций является новый диапазон,
являющийся диапазоном наименьшей длины,
в который гарантированно попадают результаты выполнения соответствующей операции
над произвольными числами исходных диапазонов. Например, (1,2) + (-3, 4) == (-2, 6).

Если типом шаблона является знаковый стандартный тип (signed char, ..., long long),
при выполнении операций должно контролироваться переполнение.
В случае обнаружения переполнения должно выбрасываться исключение std::overflow_error.
Если типом шаблона является пользовательский тип, контроль переполнения возлагается на него.

Если типом шаблона является пользовательский тип,
для него должны быть определены все операции,
позволяющие использовать его вместо стандартного целого типа (в контексте реализации Range).
Кроме того, для него должен быть определен явный конструктор преобразования из std::string,
и операция вывода в поток.
Вам не нужно реализовывать такой пользовательский тип,
но класс Range будет тестироваться с таким пользовательским типом.

Если типом шаблона не является ни пользовательский,
ни стандартный знаковый тип программа не должна компилироваться.

Вспомогательные сущности (шаблоны, функции, классы, ...) поместите в отдельное пространство имен RangeImpl,
чтобы они не "засоряли" глобальное пространство имен.



#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include <type_traits>
#include <cinttypes>
#include <cerrno>
#include <limits>
#include <algorithm>


template <typename T>
class Range {
public:
    Range(T low = T{}, T high = T{}) {
        if (low > high) {
            throw std::invalid_argument("low must be <= than high");
        }
        this->low = low;
        this->high = high;
    }

    explicit Range(const std::string& str) {
        size_t n = str.size();
        if (str[0] != '(' or str[n - 1] != ')') {
            throw std::invalid_argument("");
        }

        size_t middle = str.find(',');
        if (middle == std::string::npos or middle <= 1 or middle + 1 >= n - 1) {
            throw std::invalid_argument("");
        }

        std::string low_str = str.substr(1, middle - 1);
        size_t low_size = low_str.size();
        std::string high_str = str.substr(middle + 1, n - 1 - (middle + 1));
        size_t high_size = high_str.size();

        if constexpr (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed) {
            const char *low_c_str = low_str.c_str();
            const char *high_c_str = high_str.c_str();

            char* end;
            errno = 0;
            intmax_t l = strtoimax(low_c_str, &end, 0);
            if (errno == ERANGE) {
                throw std::range_error("");
            }

            if (l > std::numeric_limits<T>::max() or l < std::numeric_limits<T>::min()) {
                throw std::range_error("");
            }

            if (end != low_c_str + low_size) {
                throw std::invalid_argument("");
            }


            errno = 0;
            intmax_t h = strtoimax(high_c_str, &end, 0);
            if (errno == ERANGE) {
                throw std::range_error("");
            }
            if (end != high_c_str + high_size) {
                throw std::invalid_argument("");
            }
            if (h > std::numeric_limits<T>::max() or h < std::numeric_limits<T>::min()) {
                throw std::range_error("");
            }

            if (l > h) {
                throw std::invalid_argument("");
            }

            low = l;
            high = h;
        } else {
            low = T(low_str);
            high = T(high_str);
            if (low > high) {
                throw std::invalid_argument("");
            }
        }

    }

    std::string to_string() const {
        if constexpr (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed) {
            std::ostringstream s("");
            s << '(' << intmax_t (low) << ',' << intmax_t (high) << ')';
            return s.str();
        } else {
            std::ostringstream s("");
            s << '(' << low << ',' << high << ')';
            return s.str();
        }
    }

    T get_low() const {
        return low;
    }

    T get_high() const {
        return high;
    };

    friend typename std::enable_if<(std::is_integral<T>::value && std::is_signed<T>::value) ||
                                   std::is_class<T>::value, Range<T>>::type
    operator+(const Range<T>& first, const Range<T>& second) {
        if constexpr (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed) {
            T new_low;
            T new_high;
            if (__builtin_add_overflow(first.get_low(), second.get_low(), &new_low)) {
                throw std::overflow_error("overflow in +");
            } else if (__builtin_add_overflow(first.get_high(), second.get_high(), &new_high)) {
                throw std::overflow_error("overflow in +");
            } else {
                return Range<T>(new_low, new_high);
            }
        } else {
            return Range<T>(first.get_low() + second.get_low(), first.get_high() + second.get_high());
        }
    }

    friend typename std::enable_if<(std::is_integral<T>::value && std::is_signed<T>::value) ||
                                   std::is_class<T>::value, Range<T>>::type
    operator-(const Range<T>& first, const Range<T>& second) {
        if constexpr (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed) {
            T new_low;
            T new_high;
            if (__builtin_sub_overflow(first.get_low(), second.get_high(), &new_low)) {
                throw std::overflow_error("overflow in -");
            } else if (__builtin_sub_overflow(first.get_high(), second.get_low(), &new_high)) {
                throw std::overflow_error("overflow in -");
            } else {
                return Range<T>(new_low, new_high);
            }
        } else {
            return Range<T>(first.get_low() - second.get_high(), first.get_high() - second.get_low());
        }
    }

    friend typename std::enable_if<(std::is_integral<T>::value && std::is_signed<T>::value) ||
                                   std::is_class<T>::value, Range<T>>::type
    operator*(const Range<T>& first, const Range<T>& second) {
        if constexpr (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed) {
            T a, b, c, d;
            if (__builtin_mul_overflow(first.get_low(), second.get_low(), &a)) {
                throw std::overflow_error("overflow in *");
            } else if (__builtin_mul_overflow(first.get_high(), second.get_high(), &b)) {
                throw std::overflow_error("overflow in *");
            } else if (__builtin_mul_overflow(first.get_low(), second.get_high(), &c)) {
                throw std::overflow_error("overflow in *");
            } else if (__builtin_mul_overflow(first.get_high(), second.get_low(), &d)) {
                throw std::overflow_error("overflow in *");
            } else {
                return Range<T>(std::min<T>(std::min<T>(a, b), std::min<T>(c, d)),
                                std::max<T>(std::max<T>(a, b), std::max<T>(c, d)));
            }
        } else {
            T a = first.get_low() * second.get_low();

            T b = first.get_low() * second.get_high();

            T c = first.get_high() * second.get_low();

            T d = first.get_high() * second.get_high();
            return Range<T>(std::min<T>(std::min<T>(a, b), std::min<T>(c, d)),
                            std::max<T>(std::max<T>(a, b), std::max<T>(c, d)));
        }
    }

    friend typename std::enable_if<(std::is_integral<T>::value && std::is_signed<T>::value) ||
                                   std::is_class<T>::value, Range<T>>::type
    operator-(const Range<T>& first) {
        if constexpr (std::numeric_limits<T>::is_integer && std::numeric_limits<T>::is_signed) {
            T a;
            T b;
            if (__builtin_mul_overflow(first.get_low(), -1, &a)) {
                throw std::overflow_error("overflow in unary -");
            } else if (__builtin_mul_overflow(first.get_high(), -1, &b)) {
                throw std::overflow_error("overflow in unary -");
            } else {
                return Range<T>(std::min<T>(a, b), std::max<T>(a, b));
            }
        } else {
            T a = -first.get_low();
            T b = -first.get_high();
            return Range<T>(std::min<T>(a, b), std::max<T>(a, b));
        }
    }


private:
    T low;
    T high;

};