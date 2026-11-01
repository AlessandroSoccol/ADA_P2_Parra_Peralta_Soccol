#include "karatsuba.hpp"
#include <algorithm>

// Umbral para usar el método clásico. 
// Para vectores muy pequeños, la recursión añade sobrecarga innecesaria.
const int THRESHOLD = 1; 

// Función recursiva interna sin la sobrecarga del padding en cada llamada
Numero karatsubaRecursivo(const Numero& A, const Numero& B) {
    // 1. Caso Base: Delegamos a la clásica si el tamaño es muy pequeño
    if (A.size() <= THRESHOLD || B.size() <= THRESHOLD) {
        return multiplicacionClasica(A, B);
    }

    // 2. Determinar el punto de corte (m)
    int n = std::max(A.size(), B.size());
    int m = n / 2;

    // 3. Partición de operandos en mitades
    Numero A1, A0, B1, B0;
    partir(A, m, A1, A0);
    partir(B, m, B1, B0);

    // 4. Tres productos recursivos (P1, P2, P3)
    Numero P1 = karatsubaRecursivo(A1, B1);
    Numero P2 = karatsubaRecursivo(A0, B0);
    
    Numero sumaA = sumar(A1, A0);
    Numero sumaB = sumar(B1, B0);
    Numero P3 = karatsubaRecursivo(sumaA, sumaB);

    // 5. Resta segura para obtener el término central: P3 - P1 - P2
    // Se procesa como (P3 - P1) - P2 para garantizar que no existan resultados negativos
    Numero temp = restar(P3, P1);
    Numero central = restar(temp, P2);

    // 6. Recomposición: P1 * 10^(2m) + central * 10^m + P2
    Numero T1 = desplazar(P1, 2 * m);
    Numero T2 = desplazar(central, m);

    Numero sumaFinal = sumar(T1, T2);
    sumaFinal = sumar(sumaFinal, P2);

    return sumaFinal;
}

// Wrapper público que prepara los datos iniciales
Numero karatsuba(const Numero& A, const Numero& B) {
    Numero a = A;
    Numero b = B;
    
    normalizar(a);
    normalizar(b);

    // Manejo de multiplicación por cero
    if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)) {
        return Numero{0};
    }

    // Calcular la potencia de 2 más cercana para el relleno inicial
    int max_len = std::max(a.size(), b.size());
    int n = 1;
    while (n < max_len) {
        n *= 2;
    }

    // Relleno con ceros a la "izquierda" (Matemáticamente).
    // Como el Integrante 1 usó Little-Endian, agregar ceros a la izquierda 
    // significa agregarlos al FINAL del vector.
    while ((int)a.size() < n) a.push_back(0);
    while ((int)b.size() < n) b.push_back(0);

    // Llamada a la recursión y limpieza final del resultado
    Numero resultado = karatsubaRecursivo(a, b);
    normalizar(resultado);
    
    return resultado;
}