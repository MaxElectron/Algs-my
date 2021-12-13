
#include <iostream>
#include <vector>
 
template<class T>
void swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}
 
template<class T, class Comparator>
T* medianOfThree(T* a, T* b, T* c) {
    static Comparator comparator;
    if (comparator(b, a)) {
        swap<T>(a, b);
    }
    if (comparator(c, a)) {
        swap<T>(a, c);
    }
    if (comparator(c, b)) {
        swap<T>(c, b);
    }
    return b;
}
 
template<class T, class Comparator>
void partition (T* beginning, int size, T* &pivotLow, T* &pivotHigh) {
 
    static Comparator compare;
    T pivotValue = *pivotLow;
    T* store = beginning;
    swap<T>(pivotLow, beginning);
    pivotLow = beginning;
    pivotHigh = pivotLow;
 
    for (T* ptr = beginning + 1; ptr < beginning + size; ++ptr) {
        if (compare.isEqual(ptr, &pivotValue)) {
            swap(ptr, pivotHigh + 1);
            ++pivotHigh;
            continue;
        }
        if (compare(ptr, &pivotValue)) {
            swap(ptr, pivotLow);
            ++pivotLow;
            swap(ptr, pivotHigh + 1);
            ++pivotHigh;
            continue;
        }
    }
 
}
 
template<class T, class Comparator>
void quickSort(T* beginning, int size) {
    if (size == 1) {
        return;
    }
    T* low = beginning;
    T* high = beginning + size - 1;
    T* mid = beginning + (size / 2);
    T* pivotLow = medianOfThree<T, Comparator>(low, mid, high);
    T* pivotHigh = pivotLow;
    if (size <= 3) {
        return;
    }
    partition<T, Comparator>(beginning, size, pivotLow, pivotHigh);
    quickSort<T, Comparator>(beginning, (pivotLow - beginning));
    quickSort<T, Comparator>(pivotHigh, size - (pivotHigh - beginning));
}
 
class isLess {
public:
    bool operator() (const long long* obj1, const long long* obj2) {
        return *obj1 <= *obj2;
    }
    bool isEqual (const long long* obj1, const long long* obj2) {
        return *obj1 == *obj2;
    }
};
 
int main() {
 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    int size;
    std::cin >> size;
    std::vector<long long> toSort(size);
 
    for (int i = 0; i < size; ++i) {
        std::cin >> toSort[i];
    }
 
    quickSort<long long, isLess>(&toSort[0], size);
 
    for (int i = 0; i < size; ++i) {
        std::cout << toSort[i] << ' ';
    }
 
    std::cout << '\n';
 
}
