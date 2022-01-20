#pragma once

#include "matrice.hpp"
#include <vector>

template<typename T>
void Euler_Explicite (std::vector<matrice<T>>& VectT, const matrice<T>& K, const T& deltaTemp)
{

    matrice<T> dtK (deltaTemp*K);

    for (auto it = std::begin(VectT)+1; it != std::end(VectT); it++)
    {
        *it = *(it-1) + dtK*(*(it-1));
    }
}
