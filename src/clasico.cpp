#include "clasico.hpp"

Numero multiplicacionClasica(const Numero& A, const Numero& B) {

    //La multiplicacion tiene un maximo de n+m digitos
    int n = A.size();
    int m = B.size();

    Numero R(n + m, 0);

    // Multiplicacion de cada numero de A por cada uno de B
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            R[i + j] += A[i] * B[j];
        }
    }

    // Utilizamos el acarreo en caso de que se exceda
    int acarreo = 0;
    for (int i = 0; i < n + m; i++) {
        int valor = R[i] + acarreo;
        R[i] = valor % BASE;   // lo que se queda
        acarreo = valor / BASE; // lo que se lleva
    }

    normalizar(R);
    return R;
}
