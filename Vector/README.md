# Самописный вектор

Задача - реализовать класс **Vector** и все необходимые методы. [Алгоритм](https://ru.wikipedia.org/wiki/Динамический_массив).

## Ограничения

Запрещено использовать STL в любом виде. Выделение памяти - только через new и delete.

## Реализация итератора

Большой подзадачей является реализация своих итераторов, совместимых с *std::iterator*.

*Iterator* должен поддерживать операторы *std::random_access_iterator_tag*

Должен работать следующий код:

    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    auto it = ++vec.begin();
    for (int i = 3; i < 20; ++i) {
        vec.push_back(i);
    }
    std::cout << vec.size() << std::endl;       // 19
    std::cout << *it << std::endl;              // 2
    std::cout << *(++it) << std::endl;          // 3
    std::cout << *(--vec.end()) << std::endl;   // 19

За счет корректных методов *begin()* и *end()* должна работать следующая конструкция:

    Vector<double> vec;
    vec.push_back(1);
    vec.push_back(2.0);
    vec.push_back(3.5);

    // суть for (auto it = vec.begin(); it != vec.end(); ++it)
    for (const double& v : vec) {
        std::cout << v << std::endl;
    }

