# Práctica 2 — Multiplicación rápida de enteros: Algoritmo de Karatsuba

Este proyecto compara la multiplicación clásica de enteros grandes, con complejidad cuadrática, y el algoritmo de Karatsuba, basado en **Divide y Vencerás** y con complejidad teórica aproximada de $O(n^{1.585})$. Los números se representan como vectores de dígitos decimales para evitar límites de los tipos enteros nativos. El repositorio incluye operaciones auxiliares, pruebas, un benchmark, datos y gráficas.

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
├── report/
│   ├── Informe_Practica2_Karatsuba.pdf        # Informe técnico
│   └── promt.md                               # Prompt y registro resumido del uso de IA
├── Makefile                # Automatización de compilación
└── README.md
```

## Cómo funciona el proyecto

### Representación y operaciones auxiliares

El tipo `Numero`, definido en `src/Auxiliar.hpp`, es un `std::vector<int>` en base decimal (`BASE = 10`). Sus dígitos están almacenados en orden *little-endian*: el índice `0` contiene las unidades y el último índice el dígito más significativo. Por ejemplo, `1234` se almacena como `{4, 3, 2, 1}`.

`src/Auxiliar.cpp` implementa la conversión entre cadenas y vectores, la normalización de ceros finales del vector, la comparación y las operaciones de suma, resta, desplazamiento decimal y partición. La resta `restar(A, B)` presupone que `A >= B`. El desplazamiento por `k` posiciones equivale a multiplicar por `10^k`.

### Algoritmos de multiplicación

- **Multiplicación clásica — `src/clasico.cpp`:** multiplica cada dígito de un operando por cada dígito del otro, acumula los productos parciales y propaga los acarreos. Su costo es $O(nm)$ para longitudes `n` y `m`, o $O(n^2)$ cuando ambas son similares.
- **Karatsuba — `src/karatsuba.cpp`:** normaliza los operandos y completa sus longitudes con ceros hasta una potencia de dos. En cada llamada divide los operandos en mitades (`A1`, `A0`, `B1`, `B0`) y calcula tres productos recursivos:

  ```text
  P1 = A1 * B1
  P2 = A0 * B0
  P3 = (A1 + A0) * (B1 + B0)
  central = (P3 - P1) - P2
  resultado = P1 * 10^(2m) + central * 10^m + P2
  ```

  La resta se realiza en ese orden para que los resultados intermedios sean no negativos. Si un operando alcanza el caso base, se usa la multiplicación clásica. La recurrencia ideal es `T(n) = 3T(n/2) + O(n)`, que conduce a $O(n^{\log_2 3})$.

### Pruebas y benchmark

- **`src/test.cpp`:** comprueba conversiones y operaciones auxiliares, y compara resultados conocidos de ambos algoritmos. Incluye casos como cero, ceros a la izquierda, ceros intercalados, longitudes diferentes y productos grandes.
- **`src/benchmark.cpp`:** genera pares de números aleatorios y mide cada algoritmo con `std::chrono::steady_clock`. La generación y conversión de los operandos se hacen antes de iniciar los cronómetros; cada resultado se compara fuera de los intervalos medidos. Se escriben los tiempos promedio en `results/tiempos.csv`.
- **`results/graficar.py`:** lee el CSV y genera una figura comparativa. El panel izquierdo grafica tiempo contra `log2(n)` y permite observar el rendimiento y el posible punto de cruce. El panel derecho grafica `log2(tiempo)` contra `log2(n)` para comparar tendencias de crecimiento.

### Parámetros y variables importantes

| Variable | Archivo | Función |
|---|---|---|
| `BASE` | `src/Auxiliar.hpp` | Base decimal usada para representar y operar sobre los dígitos. |
| `THRESHOLD` | `src/karatsuba.cpp` | Umbral de tamaño para cambiar de Karatsuba a multiplicación clásica; actualmente es `64`. |
| `MAX_DIGITOS` | `src/benchmark.cpp` | Máxima cantidad de dígitos evaluada; actualmente `32768`. |
| `REPETICIONES` | `src/benchmark.cpp` | Número de mediciones promediadas para cada tamaño; actualmente `15`. |
| `gen(42)` | `src/benchmark.cpp` | Semilla fija del generador pseudoaleatorio para que la secuencia de entradas sea reproducible. |
| `Tamano`, `TiempoClasico_ms`, `TiempoKaratsuba_ms` | `results/tiempos.csv` | Tamaño del problema y tiempos promedio, en milisegundos, de cada algoritmo. |

El benchmark recorre tamaños en potencias de dos, desde `2` hasta `MAX_DIGITOS`. Al ejecutarlo, `results/tiempos.csv` se vuelve a generar con los nuevos resultados.

## Cómo interpretar los resultados

En `tiempos.csv`, cada fila corresponde a una cantidad de dígitos. Compara `TiempoClasico_ms` con `TiempoKaratsuba_ms`: el algoritmo con el valor menor fue más rápido para ese tamaño en esa ejecución. El punto de cruce observado está entre tamaños consecutivos donde cambia cuál tiempo es menor; no debe asumirse de antemano ni extrapolarse más allá de los datos medidos.

Karatsuba puede ser más lento para entradas pequeñas a pesar de su mejor complejidad asintótica. Las llamadas recursivas, sumas, restas, particiones y asignaciones de vectores introducen costos constantes que pesan más para tamaños reducidos. Al crecer los operandos, el costo cuadrático de la multiplicación clásica aumenta más rápido y Karatsuba puede compensar esa sobrecarga. El umbral `THRESHOLD` controla dónde se hace el cambio entre ambos métodos.

Las mediciones dependen del procesador, compilador, opciones de optimización y carga del sistema. La semilla fija reproduce la secuencia pseudoaleatoria, pero no garantiza tiempos idénticos entre ejecuciones. Por ello, interpreta las gráficas como evidencia experimental y no como una prueba formal de complejidad. La curva en escala logarítmica facilita comparar tendencias, mientras que los tiempos directos muestran la diferencia práctica y el cruce.

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

## Directorio `report/`

Este directorio reúne documentación complementaria de la práctica. Se creó para mantener organizados tanto el informe académico como el registro del proceso de trabajo:

- `Informe_Practica2_Karatsuba.pdf`: informe técnico del proyecto, con la explicación y los resultados de la implementación.
- `promt.md`: prompt de contexto utilizado durante el desarrollo y un resumen temático de las conversaciones con la IA. Este registro permite revisar cómo se utilizó la herramienta a lo largo del proyecto; no es necesario para compilar ni ejecutar el programa.
