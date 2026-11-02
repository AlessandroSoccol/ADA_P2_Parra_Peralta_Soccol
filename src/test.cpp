#include "Auxiliar.hpp"
#include "clasico.hpp"
#include "karatsuba.hpp"
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
        std::cout << "[OK]   " << caso << " = " << obtenido << "\n";
    } else {
        fallos++;
        std::cout << "[FAIL] " << caso
                  << " -> esperado " << esperado
                  << ", obtenido " << obtenido << "\n";
    }
}

// Atajo: multiplica dos numeros dados como string usando el metodo clasico.
static std::string multClasica(const std::string& a, const std::string& b) {
    return aString(multiplicacionClasica(aVector(a), aVector(b)));
}

// Atajo: multiplica dos numeros dados como string usando Karatsuba.
static std::string multKaratsuba(const std::string& a, const std::string& b) {
    return aString(karatsuba(aVector(a), aVector(b)));
}

// Atajo: valida ambos metodos simultaneamente para asegurar paridad
static void validarAmbos(const std::string& caso, 
                         const std::string& a, 
                         const std::string& b, 
                         const std::string& esperado) {
    revisar("Clasica: " + caso, multClasica(a, b), esperado);
    revisar("Karatsuba: " + caso, multKaratsuba(a, b), esperado);
}

int main() {
    std::cout << "========================================\n";
    std::cout << " PRUEBAS DE OPERACIONES AUXILIARES\n";
    std::cout << "========================================\n";

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

    std::cout << "\n========================================\n";
    std::cout << " PRUEBAS DE MULTIPLICACION Y CASOS BORDE\n";
    std::cout << "========================================\n";

    // 1. Caso Base: Números de 1 dígito
    validarAmbos("7 * 8", "7", "8", "56");
    validarAmbos("1 * 1", "1", "1", "1");
    validarAmbos("0 * 9", "0", "9", "0");

    // 2. Multiplicación estándar (diferentes tamaños)
    validarAmbos("12 * 12", "12", "12", "144");
    validarAmbos("123 * 456", "123", "456", "56088");
    validarAmbos("999 * 999", "999", "999", "998001");
    validarAmbos("25 * 100000", "25", "100000", "2500000");

    // 3. Operandos con ceros a la izquierda (Requiere normalización)
    validarAmbos("00045 * 0012", "00045", "0012", "540");

    // 4. Factores con ceros intercalados
    validarAmbos("10005 * 20004", "10005", "20004", "200140020");

    // 5. Longitudes impares antes del relleno (Ej. 3 digitos * 5 digitos)
    validarAmbos("123 * 45678", "123", "45678", "5618394");

    // 6. Producto grande 
    validarAmbos("123456789 * 987654321", 
                 "123456789", "987654321", 
                 "121932631112635269");

    std::cout << "\n========================================\n";
    std::cout << " RESUMEN FINAL\n";
    std::cout << "========================================\n";
    std::cout << "Pruebas ejecutadas: " << pruebas << "\n";
    std::cout << "Fallos detectados:  " << fallos << "\n";
    
    if (fallos == 0) {
        std::cout << "\n[EXITO] Tu modulo de Karatsuba funciona a la perfeccion.\n";
    }

    return (fallos == 0) ? 0 : 1;
}