/*Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 300000.
  Отсортировать массив методом поразрядной сортировки LSD по байтам.

Входные данные
В первой строке вводится количество чисел в массиве N.
 На следующей строке через пробел вводятся N неотрицательных чисел.

Выходные данные
Выведите этот массив, отсортированный в порядке возрастания, в одну строчку через пробел.*/

#include <iostream>
#include <vector>

void sortByLSByte(unsigned long long* beginning, int size, unsigned long long magnitude) {
    std::vector<unsigned long long> buffer(size);
    std::vector<int> indexByByte(256, 0);
    //count bytes
    for (unsigned long long* ptr = beginning; ptr < beginning + size; ++ptr) {
        ++indexByByte[(*ptr / magnitude) % 256];
    }
    //recalculation
    int sum = 0;
    for (int i = 0; i < 256; ++i) {
        sum += indexByByte[i];
        indexByByte[i] = sum - indexByByte[i];
    }
    //do sort into buffer
    for (unsigned long long* ptr = beginning; ptr < beginning + size; ++ptr) {
        buffer[indexByByte[(*ptr / magnitude) % 256]] = *ptr;
        ++indexByByte[(*ptr / magnitude) % 256];
    }
    //do sort within each byte
    if (magnitude != 72057594037927936) { // 2 ^ 56 it is
        sortByLSByte(&buffer[0], size, magnitude * 256);
    }
    //copy from buffer
    int counter = 0;
    for (unsigned long long* ptr = beginning; ptr < beginning + size; ++ptr) {
        *ptr = buffer[counter];
        ++counter;
    }
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int size;
    std::cin >> size;
    std::vector<unsigned long long> toSort(size);

    for (int i = 0; i < size; ++i) {
        std::cin >> toSort[i];
    }

    sortByLSByte(&toSort[0], size, 1);

    for (int i = 0; i < size; ++i) {
        std::cout << toSort[i] << ' ';
    }

    std::cout << '\n';
}
