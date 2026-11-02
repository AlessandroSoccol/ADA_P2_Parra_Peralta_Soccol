#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <vector>
#include <cassert>
#include <iomanip>
#include "Auxiliar.hpp"
#include "clasico.hpp"
#include "karatsuba.hpp"

using namespace std;
using namespace std::chrono;

// Generador de números aleatorios en formato string
string generarNumeroAleatorio(int digitos) {
    static mt19937 gen(42); // Semilla fija para consistencia entre ejecuciones
    uniform_int_distribution<> dis(0, 9);
    uniform_int_distribution<> dis_first(1, 9); // El primer dígito no debe ser 0
    
    string num = "";
    num.reserve(digitos);
    num.push_back(dis_first(gen) + '0');
    for (int i = 1; i < digitos; ++i) {
        num.push_back(dis(gen) + '0');
    }
    return num;
}

int main() {
    // 1. Preparar el archivo CSV de salida en la carpeta 'results'
    ofstream archivoOut("results/tiempos.csv");
    if (!archivoOut.is_open()) {
        cerr << "[ERROR] No se pudo abrir results/tiempos.csv. Verifica que la carpeta exista.\n";
        return 1;
    }
    
    // Escribir las cabeceras del CSV
    archivoOut << "Tamano,TiempoClasico_ms,TiempoKaratsuba_ms\n";

    // 2. Parámetros de la experimentación
    const int MAX_DIGITOS = 32768; // Tamaño máximo de los números a multiplicar
    const int REPETICIONES = 15; // 15 repeticiones suavizan picos de CPU sin demorar demasiado

    cout << "========================================================\n";
    cout << " INICIANDO BENCHMARK: CLASICO VS KARATSUBA\n";
    cout << "========================================================\n";
    cout << fixed << setprecision(4); // Para imprimir con 4 decimales

    // 3. Bucle de tamaños: de 2 a 4096 (en potencias de 2)
    for (int n = 2; n <= MAX_DIGITOS; n *= 2) {
        double tiempo_total_clasico = 0.0;
        double tiempo_total_karatsuba = 0.0;

        for (int r = 0; r < REPETICIONES; ++r) {
            // Generar y convertir los operandos
            string strA = generarNumeroAleatorio(n);
            string strB = generarNumeroAleatorio(n);
            Numero A = aVector(strA);
            Numero B = aVector(strB);

            // --- MEDIR METODO CLASICO ---
            auto inicio_c = steady_clock::now();
            Numero res_c = multiplicacionClasica(A, B);
            auto fin_c = steady_clock::now();

            // --- MEDIR METODO KARATSUBA ---
            auto inicio_k = steady_clock::now();
            Numero res_k = karatsuba(A, B);
            auto fin_k = steady_clock::now();

            // VALIDACIÓN CRÍTICA:
            // 1. Garantiza correctitud en números masivos.
            // 2. Obliga al compilador a procesar res_c y res_k (evita que -O3 elimine la lógica).
            assert(comparar(res_c, res_k) == 0 && "Inconsistencia detectada en benchmark.");

            // Acumular los tiempos en milisegundos
            tiempo_total_clasico += duration<double, milli>(fin_c - inicio_c).count();
            tiempo_total_karatsuba += duration<double, milli>(fin_k - inicio_k).count();
        }

        // Promediar
        double prom_clasico = tiempo_total_clasico / REPETICIONES;
        double prom_karatsuba = tiempo_total_karatsuba / REPETICIONES;

        // Escribir en consola para ver progreso
        cout << "Tamano: " << setw(4) << n << " digitos | "
             << "Clasico: " << setw(8) << prom_clasico << " ms | "
             << "Karatsuba: " << setw(8) << prom_karatsuba << " ms\n";

        // Escribir datos reales en el CSV
        archivoOut << n << "," << prom_clasico << "," << prom_karatsuba << "\n";
    }

    archivoOut.close();
    cout << "========================================================\n";
    cout << "[EXITO] Datos guardados en results/tiempos.csv\n";
    cout << "========================================================\n";

    return 0;
}