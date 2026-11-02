# Práctica 2 — Multiplicación rápida de enteros: Algoritmo de Karatsuba

Este repositorio contiene la implementación en C++ del algoritmo clásico ($O(n^2)$) y el algoritmo de Karatsuba ($O(n^{\log_2 3})$) para la multiplicación de enteros grandes, utilizando la estrategia de **Divide y Vencerás**. Se incluye también un marco de pruebas unitarias y un benchmark de rendimiento para el análisis empírico del punto de cruce.

## Integrantes del equipo
- **Parra El Masri, Juan Pablo**
- **Peralta Bedoya, Joan Stiven**
- **Soccol Mejia, Alessandro**

## Estructura del Repositorio
```text
ADA_P2_Parra_Peralta_Soccol/
├── src/
│   ├── Auxiliar.cpp        # Operaciones de suma, resta, padding y partición
│   ├── Auxiliar.hpp
│   ├── benchmark.cpp       # Protocolo de experimentación (std::chrono)
│   ├── clasico.cpp         # Algoritmo tradicional O(n^2)
│   ├── clasico.hpp
│   ├── karatsuba.cpp       # Algoritmo de Karatsuba recursivo optimizado
│   ├── karatsuba.hpp
│   └── test.cpp            # Batería de pruebas unitarias y casos borde
├── results/
│   ├── graficar.py         # Script de Python para visualización de datos
│   ├── grafica_t_vs_log2n.png
│   ├── graficas_completas.png
│   └── tiempos.csv         # Resultados generados por el benchmark
├── Makefile                # Automatización de compilación
└── README.md
```

## Requisitos Previos
*   Compilador **g++** con soporte para estándar C++17 (MinGW-w64 en Windows, o GCC en Linux/macOS).
*   **Make** (Recomendado para entornos Linux/WSL).
*   **Python 3** (Solo si se desean regenerar las gráficas).

---

## 🛠️ Compilación y Ejecución en Linux / macOS / WSL

El proyecto cuenta con un `Makefile` para facilitar la compilación. Ubíquese en la raíz del proyecto y ejecute:

**1. Para Pruebas Unitarias:**
```bash
make test
./test_karatsuba
```

**2. Para Medición de Rendimiento (Benchmark):**
*Nota: Se compila con optimización máxima `-O3` para medir tiempos reales.*
```bash
make bench
./benchmark_karatsuba
```

**3. Para limpiar los ejecutables:**
```bash
make clean
```

---

## 🪟 Compilación y Ejecución en Windows (PowerShell / CMD)

Dado que Windows no incluye `make` de forma nativa, puede compilar directamente usando `g++`. Ubíquese en la raíz del proyecto:

**1. Para Pruebas Unitarias:**
```powershell
g++ -Wall -Wextra -std=c++17 src/test.cpp src/Auxiliar.cpp src/clasico.cpp src/karatsuba.cpp -o test_karatsuba.exe
.\test_karatsuba.exe
```

**2. Para Medición de Rendimiento (Benchmark):**
```powershell
g++ -Wall -Wextra -std=c++17 -O3 src/benchmark.cpp src/Auxiliar.cpp src/clasico.cpp src/karatsuba.cpp -o benchmark_karatsuba.exe
.\benchmark_karatsuba.exe
```

---

## 📊 Generación de Gráficas

El archivo `results/tiempos.csv` contiene la salida del benchmark. Para visualizar el punto de cruce, instale las dependencias de Python y ejecute el script:

```bash
pip install pandas matplotlib numpy
python results/graficar.py
```
Las imágenes se guardarán automáticamente en la carpeta `results/`.