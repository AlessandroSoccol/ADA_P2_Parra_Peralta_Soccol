import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

def main():
    # 1. Rutas flexibles
    archivo_csv = 'tiempos.csv' if os.path.exists('tiempos.csv') else 'results/tiempos.csv'
    
    if not os.path.exists(archivo_csv):
        print(f"[ERROR] No se encontró '{archivo_csv}'. Ejecuta el benchmark primero.")
        return

    # 2. Leer los datos
    df = pd.read_csv(archivo_csv)

    # 3. Transformaciones matemáticas
    df['Log2_Tamano'] = np.log2(df['Tamano'])
    
    # Aplicamos log2 a los tiempos para la segunda gráfica. 
    # (Tus datos mínimos son ~0.0002, por lo que np.log2 funcionará sin problemas de log(0))
    df['Log2_TiempoClasico'] = np.log2(df['TiempoClasico_ms'])
    df['Log2_TiempoKaratsuba'] = np.log2(df['TiempoKaratsuba_ms'])

    # 4. Configurar el lienzo panorámico con 2 subgráficas (1 fila, 2 columnas)
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))
    fig.suptitle('Análisis de Rendimiento: Multiplicación Clásica vs Karatsuba', fontsize=18, fontweight='bold', y=1.05)

    # ==========================================
    # GRÁFICA 1: t vs log_2(n) (El Punto de Cruce)
    # ==========================================
    ax1.plot(df['Log2_Tamano'], df['TiempoClasico_ms'], label='Clásico $\Theta(n^2)$', color='#e74c3c', linewidth=2.5, marker='o')
    ax1.plot(df['Log2_Tamano'], df['TiempoKaratsuba_ms'], label='Karatsuba $\Theta(n^{\log_2 3})$', color='#2980b9', linewidth=2.5, marker='s')
    ax1.set_title('Rendimiento Real ($t$ vs $\log_2 n$)', fontsize=14, pad=10)
    ax1.set_xlabel('Magnitud del problema ($\log_2 n$)', fontsize=12)
    ax1.set_ylabel('Tiempo de ejecución $t$ (ms)', fontsize=12)
    ax1.set_xticks(np.arange(1, 16, step=1))
    ax1.grid(True, linestyle="--", alpha=0.7)
    ax1.legend(loc='upper left')

    # ==========================================
    # GRÁFICA 2: log_2(t) vs log_2(n) (Asintótica)
    # ==========================================
    ax2.plot(df['Log2_Tamano'], df['Log2_TiempoClasico'], label='Clásico (Pendiente ≈ 2)', color='#e74c3c', linewidth=2.5, marker='o')
    ax2.plot(df['Log2_Tamano'], df['Log2_TiempoKaratsuba'], label='Karatsuba (Pendiente ≈ 1.585)', color='#2980b9', linewidth=2.5, marker='s')
    ax2.set_title('Complejidad Asintótica ($\log_2 t$ vs $\log_2 n$)', fontsize=14, pad=10)
    ax2.set_xlabel('Magnitud del problema ($\log_2 n$)', fontsize=12)
    ax2.set_ylabel('$\log_2(t)$ (Logaritmo del tiempo)', fontsize=12)
    ax2.set_xticks(np.arange(1, 16, step=1))
    ax2.grid(True, linestyle="--", alpha=0.7)
    ax2.legend(loc='upper left')

    # 5. Ajustar márgenes, guardar y mostrar
    plt.tight_layout()
    nombre_salida = 'graficas_completas.png' if os.path.exists('tiempos.csv') else 'results/graficas_completas.png'
    plt.savefig(nombre_salida, dpi=300, bbox_inches='tight')
    print(f"[ÉXITO] Gráficas guardadas en: {nombre_salida}")
    plt.show()

if __name__ == "__main__":
    main()