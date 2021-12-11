/*Даны неотрицательные целые числа N, K и массив целых чисел из диапазона [0,109] размера N.
 * Требуется найти K-ю порядковую статистику, т.е.
 * напечатать число, которое бы стояло на позиции с индексом K ∈[0,N−1] в отсортированном массиве.

Реализуйте алгоритм QuickSelect (среднее время работы O(N)).

Входные данные
В первой строке записаны N и K.

В N последующих строках записаны числа последовательности.

Выходные данные
K-я порядковая статистика.*/

#include <iostream>
#include <vector>

template<class T>
void swap(T* obj1, T* obj2) {
    static T tmp;
    tmp = *obj1;
    *obj1 = *obj2;
    *obj2 = tmp;
}

template<class T, class Comparator>
T* partition (long long pivotIndex, T* array, long long size) {

    static Comparator compare;
    T* pivot = array + pivotIndex;
    T pivotValue = *pivot;
    T* store = array;
    swap<T>(pivot, array + size - 1);

    for (long long i = 0; i < size - 1; ++i) {
        if (compare((array + i), &pivotValue)) {
            swap<T>(array + i, store);
            ++store;
        }
    }

    swap<T>(store, array + size - 1);
    return store;

}

template<class T, class Comparator>
T quickSelect (long long index, T* array, long long size) {
    T* pos = array;
    while(true) {
        if (size <= 0) {
            return *pos;
        }
        pos = partition<T, Comparator>((std::rand() % size), array, size); // NOLINT(cert-msc50-cpp)
        if (index < (pos - array)) {
            size = pos - array;
        } else {
            if (index > (pos - array)) {
                size = ((array + size) - pos) - 1;
                index -= pos - array + 1;
                array = pos + 1;
            } else {
                return *pos;
            }
        }
    }
}

class isLess {
public:
    bool operator() (const long long* obj1, const long long* obj2) {
        return *obj1 <= *obj2;
    }
};

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n = 0;
    long long k = 0;
    std::cin >> n;
    std::cin >> k;
    std::vector<long long> array(n);

    for (long long i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    std::cout << quickSelect<long long, isLess>(k, &(array[0]), n);

}
