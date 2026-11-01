Necesita g++, en minw32 o otro

Comando en windows: g++ -Wall -Wextra -std=c++17 -O3 src/benchmark.cpp src/Auxiliar.cpp src/clasico.cpp src/karatsuba.cpp -o benchmark_karatsuba.exe

 .\benchmark_karatsuba.exe     

Linux:

Para compilar las pruebas unitarias: make test

Para compilar el benchmark (con optimización máxima -O3):

make bench

2. Ejecutar los programas
En Linux, por razones de seguridad, debes indicarle a la terminal explícitamente que ejecute un archivo que está en la carpeta actual usando ./ (punto y barra). Y recuerda que en Linux los ejecutables no llevan la extensión .exe

Para correr las pruebas:

Bash
/test_karatsuba

Para correr el benchmark y generar el CSV:

./benchmark_karatsuba


Si no funciona o modificas algo, ejecutar desde el principio

make clean

Y luego vuelves a ejecutar make bench o make test.