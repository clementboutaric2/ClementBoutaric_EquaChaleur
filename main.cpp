#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "matrice.hpp"
#include "corps_test.hpp"
#include "resolution.hpp"
#include "Euler_explicite.hpp"
#include "Euler_implicite.hpp"
#include "graphisme.hpp"



int main()
{
    const double duree = 1; //s
    const double delta_temp = 0.0001; //s
    const double longueur = 1; //m
    const double delta_spat = 0.01;
    const std::vector<double> D (static_cast<int>(longueur/delta_spat),1);

    matrice<double> CI (static_cast<int>(longueur/delta_spat), 1);

    for (int i = 1; i <= CI.Size()[0]; i++)
    {
        CI.setValue(i,1, 0.5 + std::sin(2*3.14*(i-1)*delta_spat) - 0.5*std::cos(2*3.14*(i-1)*delta_spat));
    }

    matrice<double> K  = MatriceConductivite(duree, delta_temp, longueur, delta_spat, D);

    std::vector<matrice<double>> VT = VecteurTemporel(duree, delta_temp, CI, longueur, delta_spat);

    Euler_Explicite<double>(&VT, K, delta_temp);
    
    InscriptionDansFichier(&VT, std::string("resultat_explicite.txt"));

    Euler_implicite<double>(&VT, delta_temp, K);

    InscriptionDansFichier(&VT, std::string("resultat_implicite.txt"));
}

