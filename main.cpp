//
//  main.cpp
//  linked_list
//
//  Created by Filip Peterek on 22/02/2019.
//  Copyright © 2019 Filip Peterek. All rights reserved.
//

#include <iostream>
#include <vector>

#include "list.hpp"

void print() { }

template<typename T, typename... Args>
void print(const T & t, const Args&... args) {
    
    std::cout << t;
    print(args...);
    
}

List<int> getList() {
    
    List<int> l;
    
    for (int i = 0; i < 10; ++i) {
        l.push_back(i*i*i);
    }
    
    return l;
    
}

struct Test {
    
    const int x;
    const int y;
    const int z;
    
    Test(int x, int y, int z) : x(x), y(y), z(z) {  }
    
};

std::ostream & operator<<(std::ostream & os, const Test & t) {
    return os << "[" << t.x << ", " << t.y << ", " << t.z << "]";
}

void basicTest(List<int> & list) {
    
    std::cout << "Basic test" << "\n"
              << "-------------------------" << std::endl;
    
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << std::endl;
    }
    
    try {
        list[20];
    } catch (const std::out_of_range & e) {
        std::cout << "Out of range test: " << e.what() << std::endl;
    }
    
    std::cout << "First: " << list.first() << std::endl;
    std::cout << "Last: " << list.last() << std::endl;
    
    std::cout << "-------------------------" << std::endl;
    
}

void mapFoldTest(List<int> & list) {
    
    std::cout << "Map/Fold test" << "\n"
              << "-------------------------" << std::endl;
    
    /* Map */
    
    auto square = [](int i) -> int {
        return i*i;
    };
    
    List<int> squares = list.map(square);
    for (size_t i = 0; i < squares.size(); ++i) {
        std::cout << squares[i] << std::endl;
    }
    
    /* Fold */
    
    auto add = [](int & acc, const int val) -> void {
        acc += val;
    };
    
    const int sum = squares.fold<int>(add, 0);
    std::cout << "Sum of squares: " << sum << std::endl;
    std::cout << "Sum: " << list.fold<int>(add, 0) << std::endl;
    
    /* Filter */
    
    auto isEven = [](const int val) -> bool {
        return not (val % 2);
    };
    List<int> even = list.filter(isEven);
    std::cout << "Even numbers: " << std::endl;
    for (size_t i = 0; i < even.size(); ++i) {
        std::cout << even[i] << std::endl;
    }
    
    std::cout << "-------------------------" << std::endl;
    
}

void insertionTest(List<int> & list) {
    
    std::cout << "Insertion test" << "\n"
              << "-------------------------" << std::endl;
    
    list.insert(1, 5);
    list.insert(0, 5);
    list.insert(11, 5);
    try {
        list.insert(13, 5);
    } catch (const std::out_of_range & e) {
        std::cout << "Out of range test: " << e.what() << std::endl;
    }
    
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << std::endl;
    }
    
    std::cout << "-------------------------" << std::endl;
    
}

void removalTest(List<int> & list) {
    
    std::cout << "Removal test" << "\n"
              << "-------------------------" << std::endl;
    
    list.remove(12);
    list.remove(0);
    list.remove(1);
    try {
        list.insert(13, 5);
    } catch (const std::out_of_range & e) {
        std::cout << "Out of range test: " << e.what() << std::endl;
    }
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << std::endl;
    }
    
    std::cout << "-------------------------" << std::endl;
    
}

void concatenationTest(const List<int> & list) {
    
    std::cout << "Concatenation test" << "\n"
              << "-------------------------" << std::endl;
    
    List<int> concatenated = list + list;
    concatenated += getList();
    for (size_t i = 0; i < concatenated.size(); ++i) {
        std::cout << concatenated[i] << std::endl;
    }
    
    std::cout << "-------------------------" << std::endl;
    
}

void copyConstructorTest(const List<int> & list) {
    
    std::cout << "Copy constructor test" << "\n"
              << "-------------------------" << std::endl;
    
    List<int> copy(list);
    for (size_t i = 0; i < copy.size(); ++i) {
        copy[i] += 1;
        std::cout << list[i] << " - " << copy[i] << std::endl;
    }
    
    std::cout << "-------------------------" << std::endl;
    
}

void moveConstructorTest() {
    
    std::cout << "Move constructor test" << "\n"
              << "-------------------------" << std::endl;
    
    List<int> moved(getList());
    for (size_t i = 0; i < moved.size(); ++i) {
        std::cout << moved[i] << std::endl;
    }
    
    std::cout << "-------------------------" << std::endl;
    
}

void varargTest() {
    
    std::cout << "Vararg test" << "\n"
              << "-------------------------" << std::endl;
    
    List<Test> t;
    for (int i = 0; i < 10; ++i) {
        t.push_back(i, i*i, i*i*i);
    }
    for (size_t i = 0; i < t.size(); ++i) {
        std::cout << t[i] << std::endl;
    }
    
    std::cout << "-------------------------" << std::endl;
    
}

void listTest() {
    
    List<int> list;
    basicTest(list);
    mapFoldTest(list);
    insertionTest(list);
    removalTest(list);
    concatenationTest(list);
    copyConstructorTest(list);
    moveConstructorTest();
    varargTest();
    
}

int main(int argc, const char * argv[]) {
    const int i = 0;
    print("Hello", ' ', "World", ' ', i, '\n');
    listTest();
}
