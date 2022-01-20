#pragma once
#include "matrice.hpp"
#include <vector>

template<typename T>
matrice<T> Gradient_conjugue(const matrice<T>* A, const matrice<T>* b, const matrice<T>* x0)
{
    matrice<T> rk (*b);
    matrice<T> rk1 (*b); //afin qu'il ait la bonne taille
    matrice<T> P (rk);
    matrice<T> x (b->Size()[0], b->Size()[1]);
    T beta {0.};
    int k{0};
    T alpha {0.};

    while (k < 1000)
    {
        alpha = (rk.t()*rk).getValue(1,1)/(P.t()*(*A)*P).getValue(1,1);
        x = x + alpha*P;
        rk1 = rk - alpha*(*A)*P;
        beta = (rk1.t()*rk1).getValue(1,1)/(rk.t()*rk).getValue(1,1);
        P = rk1 + beta*P;
        k++;
        rk = rk1;
    }
    return x;
}

template<typename T>
void Euler_implicite(std::vector<matrice<T>>* VectT, const T& deltaTemp,
                                         const matrice<T>& K )
{

    matrice<T> Id (K.Size()[0],K.Size()[1]);

    for (int i = 1; i <= Id.Size()[0]; i++) {Id.setValue(i,i,1);}

    for (auto it = std::begin(*VectT)+1; it != std::end(*VectT); it++)
    {
        *it = Gradient_conjugue(Id-deltaTemp*K*(*(it-1)), *(it-1), *(it-1));
    }
}
