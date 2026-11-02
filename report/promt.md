Actúa como un desarrollador experto en C++ y profesor universitario de Análisis y Diseño de Algoritmos. Necesito tu ayuda para completar mi parte de la Práctica 2: "Multiplicación rápida de enteros: Algoritmo de Karatsuba"[cite: 1].

==================================================
1. CONTEXTO Y ESTRUCTURA DEL PROYECTO
==================================================
- Repositorio del proyecto: ADA_P2_Parra_Peralta_Soccol[cite: 1, 3]
- Integrantes y División del Trabajo:
  * Integrante 1: Representación interna de números, funciones auxiliares (sumar, restar, desplazar, partir) y multiplicacionClasica.
  * Integrante 2 (YO - Mi responsabilidad principal en este chat): Implementación recursiva del Algoritmo de Karatsuba (karatsuba), estructuración segura de los 3 productos y coordinación con las operaciones auxiliares[cite: 1, 2].
  * Integrante 3: Protocolo de experimentación (std::chrono::steady_clock), recolección de datos, gráficas de tiempo vs. tamaño, análisis del punto de cruce y redacción del informe[cite: 3].

==================================================
2. REGLAS Y DECISIONES DE DISEÑO OBLIGATORIAS (Sección 3 y 4 de la guía)
==================================================
Debes respetar estrictamente las siguientes decisiones fijadas en la práctica:
1. Representación: Los números se manejarán como cadenas (std::string) o arreglos/vectores de dígitos en base 10 (std::vector<int>)[cite: 2]. Queda PROHIBIDO usar tipos nativos (long long, __int128, etc.) para el producto completo[cite: 2] (solo se permiten para operaciones de 1 solo dígito)[cite: 2].
2. Relleno con ceros (Padding): Los operandos se rellenan con ceros a la izquierda hasta que su longitud sea igual a la misma potencia de 2[cite: 2]. Sin embargo, las funciones auxiliares y intermedias deben admitir operandos de longitud variable y normalizar ceros a la izquierda según corresponda[cite: 2].
3. Orden de resta sin signo: Para calcular el término central P3 - P1 - P2 sin riesgo de overflow/underflow o tener que implementar aritmética con signo, se DEBE calcular obligatoriamente en este orden:
   Primero: Temp = P3 - P1[cite: 2]
   Segundo: Central = Temp - P2[cite: 2]
   (Ambas restas garantizan resultados no negativos)[cite: 2].
4. Caso Base: Cuando los números sean de 1 dígito (o un tamaño umbral/THRESHOLD justificado)[cite: 2], el cálculo se resolverá con multiplicación directa[cite: 2].

==================================================
3. RÚBRICA DE EVALUACIÓN A TENER EN CUENTA (0 a 5)
==================================================
Tu respuesta y código deben estar orientados a maximizar la nota según estos criterios de la guía:

- Correctitud y Diseño (30%): Que la función karatsuba sea 100% correcta, respete las interfaces de la Sección 4[cite: 2] y maneje todos los casos borde (1 dígito, ceros a la izquierda, ceros intercalados, longitudes impares previas al relleno y números grandes de varios cientos de dígitos)[cite: 3].
- Análisis Teórico y Comprensión (40%): Necesito comprender la deducción matemática de la identidad (pasar de 4 a 3 productos) y la resolución de la recurrencia por Teorema Maestro (identificando a, b, f(n) y el caso) y por Árbol de Recurrencia (número de subproblemas por nivel, costo por nivel, altura y suma total para justificar el exponente log2(3))[cite: 1, 4].
- Experimentación y Trazabilidad (30%): Código limpio, bien modularizado, fácil de integrar con std::chrono::steady_clock[cite: 3, 4] y preparado para ser comiteado progresivamente en GitHub[cite: 1, 3, 4].

==================================================
4. SOLICITUD ESPECÍFICA (DELIVERABLES)
==================================================
Por favor, entrégame lo siguiente:

1. EXPLICACIÓN TEÓRICA PARA MI INFORME Y DEFENSA INDIVIDUAL:
   a) Deducción algebraica de la identidad (demostrando por qué P3 - P1 - P2 equivale a x1*y0 + x0*y1)[cite: 1, 4].
   b) Solución formal por Teorema Maestro (indicando a=3, b=2, f(n)=\Theta(n), comparación con n^(log_b a) = n^(log_2 3) \approx n^1.585)[cite: 1, 4].
   c) Solución por Árbol de Recurrencia paso a paso.
3. BATERÍA DE PRUEBAS UNITARIAS EN C++: Un archivo `main.cpp` de prueba que valide la función `karatsuba` contra `multiplicacionClasica`[cite: 3] cubriendo todos los casos de borde especificados en la guía[cite: 3].
______________________________________

Como se formo la deducción algebraica sobre la identidad de karatsuba, porque la idea es brillante y es mas rápida que el método clásico.

______________________________________________

Cual a sido nuestra evaluación de desempeño teniendo en cuenta la rubrica, a la hora de realizar el proyecto.

______________________________________________

Porque, el caso clásico es mas rápido con pruebas pequeñas sobre el método de karatsuba, si se supone que para todo n, Karatsuba es mas eficiente.

_________________________________________

Cual es la manera correcta de compilar y ejecutar el código en diferentes entornos de ejecución (Linux y windows con wsl)

_______________________________________

Al incrementar el máximo de dígitos a 32768, y aumentar la variable THRESHOLD, por fin hallamos el punte de cruce en donde karatsuba es mas eficiente y rápido que el clásico, esto se debe a que llega un punto en donde el crecimiento del clásico crecerá mucho mas rápido aun con su optimización inicial, mientras que karatsuba se demora mas al principio por tener que gestionar los vectores y la información en memoria, pero al crecer con el tiempo se comporta de manera mas optimiza, pule mejor esta idea y dime si hace falta algún concepto.

_______________________________________

Dame un breve resumen de lo que podemos interpretar del .cvs una vez que obtengamos los datos, como lo podemos interpretar en una grafica y obtener un resumen visual inmediato.

________________________________________

## Registro resumido de las conversaciones con la IA

Este registro se agrega como contexto para revisar el proceso y el uso de la herramienta. Las conversaciones originales de este documento se mantienen sin cambios; los puntos siguientes son descripciones temáticas, no transcripciones.

### Visualización y documentación de la estructura

Se consultó cómo obtener el árbol de carpetas y archivos para incluirlo en el README. Se recomendó usar `tree /F /A` en Windows y se mostró un ejemplo de estructura del proyecto. Luego se aclaró que el README ya estaba publicado y que el commit solicitado era para el script de gráficas y el archivo de tiempos.

### Organización de commits y ramas en GitHub

Se solicitaron comandos para guardar `results/graficar.py` y `results/tiempos.csv` en una rama temática. Después se revisó el estado de las ramas y se detectó que `datos/graficas` también contenía commits previos de Karatsuba, por estar basada en `feature/karatsuba`. Para separar el trabajo se creó `datos/graficas-main` desde `main` y se trasladó el commit de los datos.

### Resolución de conflictos y recuperación de archivos

Durante el `cherry-pick`, `results/tiempos.csv` entró en conflicto porque estaba vacío en `main`; se conservaron las mediciones del commit. Más adelante, al advertirse que faltaban las imágenes y las reglas para ignorar ejecutables, se recuperaron las dos gráficas y `.gitignore` desde `feature/karatsuba`.

### Restauración del código y validación

Al descubrir que varios archivos del proyecto estaban vacíos, se compararon las ramas y se restauraron desde `feature/karatsuba` los archivos de Karatsuba, benchmark, pruebas, README y Makefile que estaban afectados. Se compiló el código y se ejecutaron las pruebas unitarias: 31 pasaron y 0 fallaron. Los cambios de recuperación se publicaron en `datos/graficas-main`.

### Mejora de este documento

Se pidió organizar `report/promt.md` y añadir el historial de uso de la IA. La intención se precisó después: conservar el contenido existente y agregar un resumen temático de las conversaciones, por ejemplo, documentación del README, cambios en GitHub y recuperación del proyecto.

### Observación sobre el proceso

El uso de la IA avanzó de consultas puntuales de documentación a tareas de revisión y recuperación del repositorio. La interacción incluyó precisar el alcance de los commits, diagnosticar una rama con contenido adicional, resolver un conflicto y validar la recuperación mediante compilación y pruebas.
