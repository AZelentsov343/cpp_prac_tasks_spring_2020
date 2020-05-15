Напишите шаблонную функцию myfilter, которая принимает объект контейнерного класса и функцию-предикат.
Функция возвращает новый объект того же самого контейнерного класса,
в который скопированы только те объекты исходного контейнерного класса,
которые удовлетворяют заданному предикату.

Стандартными алгоритмами пользоваться запрещено.


template <typename container_type, typename P>
container_type myfilter(const container_type& container, P pred) {
    container_type result{};
    for (auto const &el : container) {
        if (pred(el)) {
            result.insert(result.end(), el);
        }
    }
    return result;
}
