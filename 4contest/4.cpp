Написать шаблонную функцию myremove, принимающую две пары итераторов: диапазон элементов,
содержащих номера удаляемых элементов, диапазон элементов, содержащих элементы, подлежащие удалению.
Элементы, подлежащие удалению, в диапазоне нумеруются с нуля.
Номера элементов отражают позиции элементов на момент начала работы программы.
Если номер повторяется более одного раза, все вхождения, кроме первого, игнорируются.
Если номер элемента недопустим, он игнорируется.

Функция возвращает итератор на конец сжатой последовательности во втором контейнере.

Для удаляемых элементов может быть запрещено копирование.


#include <vector>
#include <algorithm>
#include <iterator>

template <typename type_index, typename type_mas>
type_mas myremove(type_index begin_num, type_index end_num, type_mas begin, type_mas end) {

    std::vector<ssize_t> to_delete;
    for (auto it = begin_num; it != end_num; ++it) {
        to_delete.push_back(*it);
    }

    std::sort(to_delete.begin(), to_delete.end());
    auto new_end_num = std::unique(to_delete.begin(), to_delete.end());
    auto num_it = to_delete.begin();

    while (*num_it < 0) {
        ++num_it;
    }

    ssize_t deleted = 0;
    bool valid = true;
    if (num_it == new_end_num) {
        valid = false;
    }
    for (auto i = begin; i != end; ++i) {
        if (valid && (std::distance(begin, i) == (*num_it))) {
            ++num_it;
            deleted++;
            if (num_it == new_end_num) {
                valid = false;
            }
        } else if (!valid && deleted == 0) {
            break;
        } else if (deleted) {
            std::swap(*(i - deleted), *i);
        }
    }
    return end - deleted;
}