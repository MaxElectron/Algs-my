/*Реализуйте структуру данных из n элементов a1,a2…an, поддерживающую следующие операции:
 
присвоить элементу ai значение j;
найти знакочередующуюся сумму на отрезке от l до r включительно (al−al+1+al+2−…±ar).
Входные данные
В первой строке входного файла содержится натуральное число n (1≤n≤105) — длина массива.
 Во второй строке записаны начальные значения элементов (неотрицательные целые числа, не превосходящие 104).
 
В третьей строке находится натуральное число m (1≤m≤105) — количество операций.
 В последующих m строках записаны операции:
 
операция первого типа задается тремя числами 0 i j (1≤i≤n, 1≤j≤104).
операция второго типа задается тремя числами 1 l r (1≤l≤r≤n).
Выходные данные
Для каждой операции второго типа выведите на отдельной строке соответствующую знакочередующуюся сумму.*/
 
#include <iostream>
#include <vector>
 
template <typename T, class Arithmetic>
class [[maybe_unused]] Fenwick {
private:
 
    std::vector<T> data;
    Arithmetic foo;
 
public:
 
    [[maybe_unused]] explicit Fenwick(std::vector<T> base);
 
    [[maybe_unused]] void change(long long index, T value);
 
    [[maybe_unused]] [[maybe_unused]] void set(long long index, T value);
 
    [[maybe_unused]] T sum(long long index);
 
    [[maybe_unused]] T sum(long long left, long long right); // []
 
};
 
template<typename T, class Arithmetic>
[[maybe_unused]] Fenwick<T, Arithmetic>::Fenwick(std::vector<T> base) {
    data = std::vector<T> (base.size(), foo.neutral());
    for (long long i = 0; i < base.size(); ++i) {
        change(i, base[i]);
    }
}
 
template<typename T, class Arithmetic>
[[maybe_unused]] void Fenwick<T, Arithmetic>::change(long long index, T value) {
    while (index < data.size()) {
        data[index] = foo(data[index], value);
        index |= index + 1;
    }
}
 
template<typename T, class Arithmetic>
[[maybe_unused]] void Fenwick<T, Arithmetic>::set(long long index, T value) {
    change(index, foo(value, foo.opposite(sum(index, index))));
}
 
template<typename T, class Arithmetic>
[[maybe_unused]] T Fenwick<T, Arithmetic>::sum(long long index) {
    T ans = foo.neutral();
    while (index >= 0) {
        ans = foo(ans, data[index]);
        index = (index & (index + 1)) - 1;
    }
    return ans;
}
 
template<typename T, class Arithmetic>
[[maybe_unused]] T Fenwick<T, Arithmetic>::sum(long long left, long long right) {
    if (left > right) {
        return foo.neutral();
    }
    if (left == 0) {
        return sum(right);
    }
    return foo(sum(right), foo.opposite(sum(left - 1)));
}
 
template <typename T>
class Digits {
public:
    T operator() (T a, T b) {
        return a + b;
    }
 
    T neutral () {
        return 0;
    }
 
    T opposite (T a) {
        return -a;
    }
};
 
int main() {
 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int baseSize;
    std::cin >> baseSize;
 
    std::vector<long long> baseEven ((baseSize / 2) + (baseSize % 2));
    std::vector<long long> baseOdd (baseSize / 2);
    for (int i = 0; i < baseSize; ++i) {
        if (i % 2 == 0) {
            std::cin >> baseEven[i / 2];
        } else {
            std::cin >> baseOdd[i / 2];
        }
    }
 
    Fenwick<long long, Digits<long long>> evenTree(baseEven);
    Fenwick<long long, Digits<long long>> oddTree(baseOdd);
 
    int queriesAmount;
    std::cin >> queriesAmount;
 
    int query, a, b;
    for (int i = 0; i < queriesAmount; ++i) {
        std::cin >> query >> a >> b;
        --a;
        if (query == 1) {
            --b;
            switch (a % 2 + ((b % 2) * 2)) {
                case 0:
                    std::cout << evenTree.sum(a / 2, b / 2) -
                    oddTree.sum(a / 2, b / 2 - 1) << '\n';
                    break;
                case 1:
                    std::cout << oddTree.sum(a / 2, b / 2 - 1) -
                    evenTree.sum(a / 2 + 1, b / 2) << '\n';
                    break;
                case 2:
                    std::cout << evenTree.sum(a / 2, b / 2) -
                    oddTree.sum(a / 2, b / 2) << '\n';
                    break;
                case 3:
                    std::cout << oddTree.sum(a / 2, b / 2) -
                    evenTree.sum(a / 2 + 1, b / 2) << '\n';
                    break;
                default:
                    break;
            }
        }
        if (query == 0) {
            if (a % 2 == 0) {
                evenTree.set(a / 2, b);
            } else {
                oddTree.set(a / 2, b);
            }
        }
    }
 
}
