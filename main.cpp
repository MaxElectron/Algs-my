/*Дано число N и последовательность из N целых чисел. 
Найти вторую порядковую статистику на заданных диапазонах.

Для решения задачи используйте структуру данных Sparse Table. 
Требуемое время обработки каждого диапазона O(1). 
Время подготовки структуры данных O(nlogn).

Входные данные
В первой строке заданы 2 числа: 
размер последовательности N и количество диапазонов M.

Следующие N целых чисел задают последовательность. 
Далее вводятся M пар чисел - границ диапазонов.

Выходные данные
Для каждого из M диапазонов напечатать 
элемент последовательности - 2ю порядковую статистику. 
По одному числу в строке.*/

#include <iostream>
#include <vector>
 
long long nextPowerOfTwo(unsigned long long a) {
    a--;
    a |= a >> 1;
    a |= a >> 2;
    a |= a >> 4;
    a |= a >> 8;
    a |= a >> 16;
    a |= a >> 32;
    a++;
    return a; // NOLINT(cppcoreguidelines-narrowing-conversions)
}
 
long long powerOfTwo(long long a) {
    long long ans = 0;
    while (a != 0) {
        a = a >> 1;
        ++ans;
    }
    --ans;
    return ans;
}
 
template <typename T, class Foo>
class SparseTable {
private:
 
    std::vector<T> data;
    long long width;
    long long height;
    /*
     0     1       2    ...
     w   w + 1   w + 2  ...
     ...
     */
 
    Foo foo;
 
    T& get (long long row, long long column);
    
public:
    
    explicit SparseTable(std::vector<T> base);
 
    T request (long long left, long long right);
 
};
 
template<class T, class Foo>
T &SparseTable<T, Foo>::get(long long int row, long long int column) {
    return data[width * row + column];
}
 
template<class T, class Foo>
SparseTable<T, Foo>::SparseTable(std::vector<T> base) {
    // assign variables
    width = base.size();
    height = powerOfTwo(nextPowerOfTwo(width));
    data = std::vector<T> (height * width, foo.neutral());
 
    //build the table
    for (long long i = 0; i < width; ++i) {
        get(0, i) = base[i];
    }
    for (long long i = 1; i < height; ++i) {
        for (long long j = 0; j + (1 << i) <= width; ++j) {
            get(i, j) = foo(get(i - 1, j), get(i - 1, j + (1 << (i - 1))));
        }
    }
}
 
template<typename T, class Foo>
T SparseTable<T, Foo>::request(long long int left, long long int right) {
    long long row = powerOfTwo(nextPowerOfTwo(right - left + 1)) - 1;
    if (row < 0) {
        row = 0;
    }
    long long columnLeft = left;
    long long columnRight = right - (1 << row) + 1;
    return foo(get(row, columnLeft), get(row, columnRight));
}
 
class secondMin {
public:
    std::pair<long long, long long> operator() (std::pair<long long, long long> a, std::pair<long long, long long> b) {
        if (a.first > b.first) {
            return b;
        }
        return a;
    }              
    
    static std::pair<long long, long long> neutral() {
        return {INT64_MAX, 0};
    }
};
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    long long size, queries, tmp;
    std::cin >> size >> queries;
    std::vector<std::pair<long long, long long>> base(size);
    for (long long i = 0; i < base.size(); ++i) {
        std::cin >> tmp;
        base[i] = std::pair(tmp, i + 1);
    }
    SparseTable<std::pair<long long, long long>, secondMin> table (base);
    long long left, right;
    for (int i = 0; i < queries; ++i) {
        std::cin >> left >> right;
        tmp = table.request(left - 1, right - 1).second;
        if (tmp == right) {
            std::cout << table.request(left - 1, right - 2).first << '\n';
            continue;
        }
        if (tmp == left) {
            std::cout << table.request(left, right - 1).first << '\n';
            continue;
        }
        std::cout << std::min(table.request(left - 1, tmp - 2).first,
                              table.request(tmp, right - 1).first) << '\n';
    }
}
