# Compilador y banderas de compilación
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
OPTFLAGS = -O3

# Archivos fuente compartidos por ambos ejecutables (no incluyen ningún main)
SRC_COMMON = src/Auxiliar.cpp src/clasico.cpp src/karatsuba.cpp

# Nombres de los ejecutables de salida
TARGET_TEST = test_karatsuba
TARGET_BENCH = benchmark_karatsuba

# Regla por defecto: compilar todo
all: test bench

# 1. Compilar pruebas unitarias (ideal para depurar)
test:
	$(CXX) $(CXXFLAGS) src/test.cpp $(SRC_COMMON) -o $(TARGET_TEST)

# 2. Compilar el benchmark (con máxima optimización para medir tiempos reales)
bench:
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) src/benchmark.cpp $(SRC_COMMON) -o $(TARGET_BENCH)

# Regla para limpiar los ejecutables generados (útil tanto en Linux/WSL como en Windows)
clean:
	rm -f $(TARGET_TEST) $(TARGET_BENCH) *.exe