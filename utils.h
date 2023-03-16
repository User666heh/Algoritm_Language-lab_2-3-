#pragma once
#include <iostream>

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail() || x<min || x>max)
    {
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        std::cout << "Enter number(" << min << "-" << max << "):";
    }
    return x;
}
