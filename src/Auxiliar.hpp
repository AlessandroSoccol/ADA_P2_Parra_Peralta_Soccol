#ifndef AUXILIAR_HPP
#define AUXILIAR_HPP

#include <vector>
#include <string>

const int BASE = 10;    //Trabajamos en base 10

// Representacion invertida del numero ingresado en forma de vector
using Numero = std::vector<int>;

// Conversion
Numero aVector(const std::string& s);   
std::string aString(const Numero& num); 

//Utilidades
void normalizar(Numero& num);
int comparar(const Numero& A, const Numero& B);

//Operaciones
Numero sumar(const Numero& A, const Numero& B);   // A + B
Numero restar(const Numero& A, const Numero& B);  // A - B   (precondicion: A >= B)
Numero desplazar(const Numero& A, int k);         // A * 10^k
void partir(const Numero& A, int m, Numero& alto, Numero& bajo); // separa en mitad alta y baja

#endif
