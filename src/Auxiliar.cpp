#include "Auxiliar.hpp"
#include <algorithm> 

// Pasar entrada a vector
Numero aVector(const std::string& s) {
    Numero num;
    // inversion de orden (Para simplificar procedimientos).
    for (int i = s.size() - 1; i >= 0; i--) {
        num.push_back(s[i] - '0');
    }
    return num;
}

std::string aString(const Numero& num) {
    std::string s;
    // La posicion mas alta del vector es el digito mas significativo.
    for (int i = num.size() - 1; i >= 0; i--) {
        s.push_back(num[i] + '0');
    }
    return s;
}

// Normalizacion
void normalizar(Numero& num) {
    // Quitamos 0s (menos el ultimo)
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
}

// Comparar
int comparar(const Numero& A, const Numero& B) {
    Numero a = A, b = B;
    normalizar(a);
    normalizar(b);
    // Definir cual es mas alto, A o B.
    if (a.size() != b.size()) {
        return (a.size() < b.size()) ? -1 : 1;
    }
    // Siu son igual de largos comparamos desde el digito mas significativo.
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) {
            return (a[i] < b[i]) ? -1 : 1;
        }
    }
    return 0;
}

// OPERACIONES

//Sumar
Numero sumar(const Numero& A, const Numero& B) {
    Numero R;
    int acarreo = 0;
    int n = std::max(A.size(), B.size());
    for (int i = 0; i < n; i++) {
        int da = (i < (int)A.size()) ? A[i] : 0;
        int db = (i < (int)B.size()) ? B[i] : 0;
        int suma = da + db + acarreo;
        R.push_back(suma % BASE);  // lo que se queda
        acarreo = suma / BASE;     // lo que se lleva
    }
    if (acarreo > 0) {
        R.push_back(acarreo);    //Acareo restante
    }
    return R;
}

//Restar
Numero restar(const Numero& A, const Numero& B) {
    Numero R;
    int prestamo = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        int da = A[i];
        int db = (i < (int)B.size()) ? B[i] : 0;
        int resta = da - db - prestamo;
        if (resta < 0) {
            resta += BASE; // pedimos prestado a la siguiente posicion
            prestamo = 1;
        } else {
            prestamo = 0;
        }
        R.push_back(resta);
    }
    normalizar(R);
    return R;
}

//Desplazar
Numero desplazar(const Numero& A, int k) {
    Numero R(k, 0);     // Base 10, empezamos con k cantidad de 0s
    R.insert(R.end(), A.begin(), A.end());  //Desplazamos el numero hacia la izquierda
    return R;
}

//Partir
void partir(const Numero& A, int m, Numero& alto, Numero& bajo) {
    // bajo = los m digitos menos significativos; alto = el resto.
    bajo.clear();
    alto.clear();
    for (int i = 0; i < (int)A.size(); i++) {
        if (i < m) bajo.push_back(A[i]);
        else       alto.push_back(A[i]);
    }
    if (bajo.empty()) bajo.push_back(0);
    if (alto.empty()) alto.push_back(0);
    normalizar(alto);
    normalizar(bajo);
}
