#pragma once

#include "matrice.hpp"
#include <string>
#include <fstream>


template <typename T>
void InscriptionDansFichier (std::vector<matrice<T>>& SOLUTION, std::string file){

   std::ofstream fichier(file);
    if (fichier)
    {
        for (auto it = std::begin(SOLUTION); it != std::end(SOLUTION); it++)
        {
            for (int i = 1; i <= (*it).Size()[0]; i++)
            {
                fichier << it->getValue(i,1) << ",";
            }
            fichier << std::endl;
        }
    }
}
