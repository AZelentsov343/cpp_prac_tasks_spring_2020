Написать функцию process, принимающую два параметра:

неизменяемый вектор целых чисел v1;
вектор целых чисел v2.
Функция должна удалить из вектора v2 элементы с номерами,
заданными в векторе v1. Элементы вектора нумеруются от 0.
Номера элементов вектора v2 отражают позиции элементов на момент начала работы программы.
Если номер повторяется в векторе v1 более одного раза, все вхождения, кроме первого, игнорируются.
Если число в векторе v1 не является допустимым номером элемента в векторе v2, оно игнорируется.

Для доступа к элементам векторов использовать только итераторы.

При необходимости допускается создавать локальную копию вектора v1.
Из стандартных алгоритмов допускается использовать std::sort, std::unique, std::swap.
  
#include <vector>
#include <algorithm>

void process(const std::vector<int> index, std::vector<int> &v) {
    std::vector<int> copied_index = index;

    std::sort(copied_index.begin(), copied_index.end());
    auto last = std::unique(copied_index.begin(), copied_index.end());

    int count = 0;
    auto x = copied_index.begin();
    for (; x < last && (*x) < 0; x++);
    if (x == last) {
        return;
    }

    for (auto it = v.begin(); it < v.end(); it++) {
        if (it - v.begin() == (*x)) {
            count++;
            if (x + 1 < last) {
                x++;
            }
        } else {
            if (count > 0) {
                std::swap(*it, *(it - count));
            }
        }
    }
    v.resize(v.size() - count);
}


