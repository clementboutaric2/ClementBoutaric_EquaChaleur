#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

template <typename T>
class matrice
{
   /*Cette classe matrice n'a pas d'élément d'indice (0,0).
     On fait des maths ici, que diable ! */
    protected:
       std::vector<T> tableau;
       int NbCol;
       int NbLig;

    public:
       matrice();
       matrice(const int&, const int&);
       matrice(const int&, const int&, const std::vector<T>&);
       matrice(const matrice<T>& M);

       T getValue(const int&, const int&) const;
       void setValue(const int&, const int&, const T&);
       std::vector<int> Size() const;
       matrice<T>& operator=(const matrice<T>& other);
       matrice<T> t ();

       void affichage() const;
};

template<typename T>
matrice<T>::matrice(): NbCol(1), NbLig(1), tableau(1) {}

template<typename T>
matrice<T>::matrice(const int& a, const int& b): NbLig(a), NbCol(b), tableau(a*b) {}

template<typename T>
matrice<T>::matrice(const int& a, const int& b, const std::vector<T>& initialisation): NbLig(a), NbCol(b), tableau(initialisation)
{}

template<typename T>
matrice<T>::matrice(const matrice<T>& M): NbLig(M.Size()[0]), NbCol(M.Size()[1]), tableau(M.Size()[0]*M.Size()[1])
{
   for (int i = 1; i <= this->NbLig; i++)
   {
      for (int j = 1; j <= this->NbCol; j++)
      {
         this->setValue(i,j,M.getValue(i,j));
      }
   }
}

template<typename T>
T matrice<T>::getValue(const int& ligne, const int& colonne) const
{
    return tableau[(ligne-1)*(this->NbCol)+ colonne-1];
}

template<typename T>
void matrice<T>::setValue(const int& ligne, const int& colonne, const T& valeur)
{
    tableau[(ligne-1)*(this->NbCol) + colonne-1] = valeur;
}

template<typename T>
std::vector<int> matrice<T>::Size() const
{
   std::vector<int> Size {this->NbLig, this->NbCol};
   return Size;
}

template<typename T>
matrice<T>& matrice<T>::operator= (const matrice<T>& other)
{
   int NbLig {this->Size()[0]};
   int NbCol {this->Size()[1]};

   for (int i = 1; i <= NbLig; i++)
   {
      for (int j = 1; j <= NbCol; j++)
      {
         this->setValue(i,j, other.getValue(i,j));
      }
   }
   return *this;
}

template<typename T>
matrice<T> operator* (const matrice<T>& A, const matrice<T>& B)
{

   int n {(A.Size())[0]}; //nombre de lignes de la nouvelle matrice.
   int m {(B.Size())[1]}; //nombre de colonnes.
   int commune {(A.Size())[1]};

   //On vérifie que le produit matriciel est possible.
   try 
   {
      if ((A.Size())[1] != (B.Size())[0])
      {
         //sinon on fait tout planter, avec un petit message quand même.
         throw (std::string("column size of left matrice must be equal to row size of right matrice"));
      }
   }

   catch (std::string error)
   {
      std::exit(-1);
   }


   matrice<T> M (n, m);

   for (int i = 1; i <= n; i++ )
   {
      for (int j = 1; j <= m; j++)
      {
         int a {0}; //élément d'indice (i,j) de la nouvelle matrice
         for (int l = 1; l <= commune; l++)
         {
            a += A.getValue(i, l)*B.getValue(l, j);
         }
         M.setValue(i,j,a);
      }
   }
   return M;
}

template<typename T>
matrice<T> operator* (const T& scalaire, const matrice<T>& B)
{
   int n {(B.Size())[0]}; //nombre de lignes de la nouvelle matrice.
   int m {(B.Size())[1]}; //nombre de colonnes.

   matrice<T> M (n, m);

   for (int i = 1; i <= n; i++ )
   {
      for (int j = 1; j <= m; j++)
      {
         T a {scalaire*B.getValue(i,j)}; //élément d'indice (i,j) de la nouvelle matrice
         M.setValue(i,j,a);
      }
   }
   return M;
}

template<typename T>
matrice<T> operator+ (const matrice<T>& A, const matrice<T>& B)
{
   int NbL {(A.Size())[0]};
   int NbC {(A.Size())[1]};
   matrice<T> M (NbL,NbC);

   for (int i = 1; i <= NbL; i++)
   {
      for (int j = 1; j <= NbC; j++)
      {
         M.setValue(i,j, A.getValue(i,j) + B.getValue(i,j));
      }
   }

   return M;
}

template<typename T>
matrice<T> operator- (const matrice<T>& A, const matrice<T>& B)
{
   return A + static_cast<T>(-1.)*B;
}

template<typename T>
matrice<T> matrice<T>::t()
{
   matrice<T> transpose (this->NbCol, this->NbLig);
   for (int i = 1; i <= this->NbCol; i++)
   {
      for (int j = 1; j <= this->NbLig; j++)
      {
         transpose.setValue(i,j,this->getValue(j,i));
      }
   }
   return transpose;
}

template<typename T>
void matrice<T>::affichage() const
{
   std::cout << "[";
   for (int i = 1; i <= this->NbLig; i++)
   {
      for (int j = 1; j <= this->NbCol; j++)
      {
         std::cout << this->getValue(i,j) << ",";
      }
      std::cout << "\n";
   }
   std::cout << "]" << std::endl;
}
