#include <iostream>
#include <functional> // для std::hash, если понадобится

#include <map>

#include "MyAllocator.h"

#include "MyContainer.h"

// Вспомогательная функция для факториала
constexpr int factorial(int n) {
    unsigned int res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

int main() {
    // 1. Создаем std::map как есть
    std::map<int, int> default_map;
    for (int i = 0; i < 10; ++i) {
        default_map[i] = factorial(i); // заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    }
   /* for (auto& pr : default_map) {
        std::cout << pr.first <<" "<<pr.second<< std::endl;
    }*/
    
    // 2. Создаем std::map с нашим аллокатором ограниченным 10 элементами
    MyAllocator<std::pair<const int, int>> map_alloc(10); 
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> custom_map( std::less<int>(), map_alloc);
    
    for (int i = 0; i < 10; ++i) {
        custom_map.emplace(i, factorial(i)); //заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    }

    // Вывод содержимого custom_map
   
    for (const auto& k : custom_map) {
        std::cout << k.first << " " << k.second << std::endl;
    }
    
    // 3. Создаем свой контейнер для хранения int
    MyContainer<int> my_cont;
    for (int i = 0; i < 10; ++i) {
        my_cont.push_back(i); // заполнение 10 элементами от 0 до 9
    }
 //   for (int i = 0; i < 10; ++i) {
  //      std::cout << my_cont.at(i) << std::endl;
  //  }
   
    // 4. Создаем свой контейнер с новым аллокатором  
    
    MyAllocator<int> myAlloc;
    MyContainer<int, MyAllocator<int>> my_cont2(myAlloc);
   
    for (int i = 0; i < 10; ++i) {
        my_cont2.push_back(i);// заполнение 10 элементами от 0 до 9
    }
 
    // Вывод значений из my_cont2
    
    for (auto& val : my_cont2) {
        std::cout << val << " "; //вывод на экран всех значений, хранящихся в контейнере
    }
    std::cout << std::endl;

    return 0;
}
