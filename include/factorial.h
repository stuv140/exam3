#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP
// Вспомогательная функция для факториала
int factorial(int n) {
    unsigned int res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}
#endif /* FACTORIAL_HPP */