/*Реализуйте двоичную кучу.
 
Обработайте запросы следующих видов:
 
insert x — вставить целое число x в кучу;
getMin — вывести значение минимального элемента в куче (гарантируется, что к этому моменту куча не пуста);
extractMin — удалить минимальный элемент из кучи,
 выводить его не нужно (гарантируется, что к этому моменту куча не пуста);
decreaseKey i Δ — уменьшить число, вставленное на i-м запросе,
 на целое число Δ≥0 (гарантируется, что i-й запрос был осуществлён ранее,
 являлся запросом добавления, а добавленное на этом шаге число всё ещё лежит в куче).
 Обратите внимание, число i равно номеру запроса среди всех запросов, а не только среди запросов добавления!
Можете считать, что в любой момент времени все числа, хранящиеся в куче,
 попарно различны, а их количество не превышает 105.
 
Входные данные
В первой строке содержится число q (1≤q≤106), означающее число запросов.
 
В следующих q строках содержатся запросы в описанном выше формате.
 Добавляемые числа x и поправки Δ лежат в промежутке [−109,109], а Δ≥0.
 
Выходные данные
На каждый запрос вида getMin выведите ответ в отдельной строке.*/
 
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
 
template<class T, class Comparator>
class Heap{
private:
 
    std::vector<unsigned long long> keys;
    std::vector<T> containedObjects;
    std::vector<unsigned long long> containedKeys;
    unsigned long long queries = 0;
    Comparator comparator;
    
    T* getFirst() {
        if (size() == 0) {
            return nullptr;
        } else {
            return &containedObjects[0];
        }
    }
 
    T* getLast() {
        if (size() == 0) {
            return nullptr;
        } else {
            return &containedObjects[size() - 1];
        }
    }
 
    void swap(T* obj1, T* obj2) {
        //swap values
        T tmpObj = *obj1;
        *obj1 = *obj2;
        *obj2 = tmpObj;
 
        //swap key values
        unsigned long long tmpVal = containedKeys[obj1 - getFirst()];
        containedKeys[obj1 - getFirst()] = containedKeys[obj2 - getFirst()];
        containedKeys[obj2 - getFirst()] = tmpVal;
 
        //swap key pointers
        unsigned long long tmpPtr = keys[containedKeys[obj1 - getFirst()]];
        keys[containedKeys[obj1 - getFirst()]] = keys[containedKeys[obj2 - getFirst()]];
        keys[containedKeys[obj2 - getFirst()]] = tmpPtr;
    }
 
    bool isRoot(T* obj) {
        if (obj - getFirst() == 0) {
            return true;
        } else {
            return false;
        }
    }
 
    int downwardsDegree(T* obj) {
 
//
//                 ...
//                  |
//                 (i)  <-  of this one
//               /     \
//        (2i + 1)     (2i + 2)
//        /      \     /      \
//      ...     ...   ...     ...
//
 
//      obj - first = index of obj
 
        if (size() > ((obj - getFirst()) * 2) + 2) {
            return 2;
        }
 
        if (size() == ((obj - getFirst()) * 2) + 2) {
            return 1;
        }
 
        if (size() < ((obj - getFirst()) * 2) + 2) {
            return 0;
        }
        return 0;
    }
 
    T* firstChildOf(T* obj) {
        if (downwardsDegree(obj) >= 1) {
            return getFirst() + ((obj - getFirst()) * 2) + 1;
        } else {
            return nullptr;
        }
    }
 
    T* secondChildOf(T* obj) {
        if (downwardsDegree(obj) >= 2) {
            return getFirst() + ((obj - getFirst()) * 2) + 2;
        } else {
            return nullptr;
        }
    }
 
    T* parentOf(T* obj) {
        if (isRoot(obj)) {
            return nullptr;
        } else {
            return getFirst() + (((obj - getFirst()) - ((obj - getFirst() + 1) % 2)) / 2);
        }
    }
 
    void siftDown(T* obj) {
        switch (downwardsDegree(obj)) {
            case 0:
                //reached bottom of the heap
                break;
 
            case 1:
 
                //obj has only one child, consequently the child is at the bottom
                if (!comparator(obj, firstChildOf(obj))) {
                    //if obj can't be on top of its only child we should swap them
                    assert(comparator(firstChildOf(obj), obj));
                    swap(obj, firstChildOf(obj));
                }
 
                //reached bottom of the heap
                break;
 
            case 2:
 
                //obj has two children
                if (comparator(firstChildOf(obj), secondChildOf(obj))) {
 
                    //if first child can be on top of the second child
                    if (!comparator(obj, firstChildOf(obj))) {
                        //if obj can't be on top of its first child we should swap them and continue the sifting
                        assert(comparator(firstChildOf(obj), obj));
                        swap(obj, firstChildOf(obj));
                        siftDown(firstChildOf(obj));
                    }
                    //else obj can't be sifted down any further
 
                } else {
 
                    //if first child can't be on top of the second child
                    assert(comparator(secondChildOf(obj), firstChildOf(obj)));
                    if (!comparator(obj, secondChildOf(obj))) {
                        //if obj can't be on top of its second child we should swap them and continue the sifting
                        assert(comparator(secondChildOf(obj), obj));
                        swap(obj, secondChildOf(obj));
                        siftDown(secondChildOf(obj));
                    }
                    //else obj can't be sifted down any further
 
                }
                break;
        }
    }
 
    void siftUp(T* obj) {
        if (!isRoot(obj)) {
            // if obj is not the root and ...
            if (!comparator(parentOf(obj), obj)) {
                //if obj can't be under its current parent swap them and continue sifting
                assert(comparator(obj, parentOf(obj)));
                swap(obj, parentOf(obj));
                siftUp(parentOf(obj));
            }
            //else obj can be left where it currently is
        }
        //else reached top
    }
 
public:
 
    T extract() {
        assert(!containedObjects.empty());
        T ans = *getFirst(); //remember the extracted element
        if (size() == 1) {
            //if it was the getLast() element remove the only element and reset both first and getLast() pointers
            containedObjects.pop_back();
            keys[containedKeys[getLast() - getFirst()]] = 42;
            containedKeys.pop_back();
        } else {
            //else we should put the getLast() element in place of obj, sift it down and move getLast() pointer backward
            swap(getFirst(), getLast()); //replace the getFirst() element with the getLast()
            containedObjects.pop_back(); //remove getLast() element
            keys[containedKeys[size()]] = 42; // error here
            containedKeys.pop_back();
            siftDown(getFirst()); //restore properties of the heap
        }
        keys.push_back(42);
        ++queries;
        return ans; //return the extracted element
    }; //used only from outside
 
    void insert(T obj) {
        containedObjects.push_back(obj);
        containedKeys.push_back(queries);
        keys.push_back(size() - 1);
        siftUp(getLast());
        ++queries;
    }; //used only from outside
 
    T getRoot() {
        assert(!containedObjects.empty());
        keys.push_back(42);
        ++queries;
        return containedObjects[0];
    } //used only from outside
 
    void changeKey(unsigned long long key, T newVal) {
        T val = getKey(key);
        containedObjects[keys[key]] = newVal;
        if (comparator(&newVal, &val)) {
            siftUp(&containedObjects[keys[key]]);
        } else {
            assert(comparator(&val, &newVal));
            siftDown(&containedObjects[keys[key]]);
        }
        keys.push_back(42);
        ++queries;
    } //used only from outside
 
    T getKey(unsigned long long key) {
        T ans = containedObjects[keys[key]];
        return ans;
    }
 
    unsigned long long size() {
        return containedObjects.size();
    }
 
};
 
class isLess {
public:
    bool operator() (const long long* obj1, const long long* obj2) {
        return *obj1 <= *obj2;
    }
};
 
int main() {
 
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
 
    unsigned long long queriesAmount;
    long long value;
    long long newValue;
    unsigned long long key;
    std::cin >> queriesAmount;
    Heap<long long, isLess> theHeap;
    std::string command;
 
    for (unsigned long long i = 0; i < queriesAmount; ++i) {
 
//        std::cout << i + 1 << ")\n";
 
        std::cin >> command;
 
        if ((command == "insert") || (command == "i")) {
            std::cin >> newValue;
            theHeap.insert(newValue);
            continue;
        }
 
        if ((command == "getMin") || (command == "g")) {
            std::cout << theHeap.getRoot() << '\n';
            continue;
        }
 
        if ((command == "extractMin") || (command == "e")) {
            theHeap.extract();
            continue;
        }
 
        if ((command == "decreaseKey")  || (command == "d")) {
            std::cin >> key;
            --key;
            std::cin >> newValue;
            value = theHeap.getKey(key);
            newValue = value - newValue;
            theHeap.changeKey(key, newValue);
            continue;
        }
 
        --i;
 
    }
 
}
