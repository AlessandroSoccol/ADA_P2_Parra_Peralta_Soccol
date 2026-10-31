#include "Auxiliar.hpp"
#include "clasico.hpp"
#include <iostream>
#include <string>

// Contadores globales para el resumen final.
static int pruebas = 0;
static int fallos = 0;

// Compara el resultado obtenido (como string) contra el esperado e imprime
static void revisar(const std::string& caso,
                    const std::string& obtenido,
                    const std::string& esperado) {
    pruebas++;
    if (obtenido == esperado) {
        std::cout << "OK    " << caso << " = " << obtenido << "\n";
    } else {
        fallos++;
        std::cout << "FALLO " << caso
                  << " -> esperado " << esperado
                  << ", obtenido " << obtenido << "\n";
    }
}

// Atajo: multiplica dos numeros dados como string usando el metodo clasico.
static std::string multClasica(const std::string& a, const std::string& b) {
    return aString(multiplicacionClasica(aVector(a), aVector(b)));
}

int main() {
    std::cout << "Auxiliares\n";

    // Conversion ida y vuelta.
    revisar("aString(aVector(1234))", aString(aVector("1234")), "1234");

    // sumar
    revisar("999 + 1",   aString(sumar(aVector("999"), aVector("1"))),   "1000");
    revisar("12 + 3456", aString(sumar(aVector("12"), aVector("3456"))), "3468");

    // restar (precondicion A >= B)
    revisar("1000 - 1",    aString(restar(aVector("1000"), aVector("1"))),    "999");
    revisar("3468 - 3456", aString(restar(aVector("3468"), aVector("3456"))), "12");
    revisar("500 - 500",   aString(restar(aVector("500"), aVector("500"))),   "0");

    // desplazar (x 10^k)
    revisar("12 << 3", aString(desplazar(aVector("12"), 3)), "12000");

    // partir (1234 con m=2 -> alto 12, bajo 34)
    {
        Numero alto, bajo;
        partir(aVector("1234"), 2, alto, bajo);
        revisar("partir(1234,2) alto", aString(alto), "12");
        revisar("partir(1234,2) bajo", aString(bajo), "34");
    }

    std::cout << "\n Multiplicacion clasica \n";

    // Casos basicos.
    revisar("7 * 8",       multClasica("7", "8"),       "56");
    revisar("12 * 12",     multClasica("12", "12"),     "144");
    revisar("123 * 456",   multClasica("123", "456"),   "56088");
    revisar("999 * 999",   multClasica("999", "999"),   "998001");

    // Casos de borde.
    revisar("0 * 12345",   multClasica("0", "12345"),   "0");
    revisar("1 * 1",       multClasica("1", "1"),       "1");

    // Longitudes distintas.
    revisar("25 * 100000", multClasica("25", "100000"), "2500000");

    // Un caso mas grande
    revisar("123456789 * 987654321",
            multClasica("123456789", "987654321"),
            "121932631112635269");

    std::cout << "\n=== Resumen ===\n";
    std::cout << "Pruebas: " << pruebas << ", Fallos: " << fallos << "\n";
    return (fallos == 0) ? 0 : 1;
}
