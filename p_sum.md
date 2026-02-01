# Suma de Arreglos en Paralelo con OpenMP

**Autor:** Artemio Padilla
**Fecha:** Febrero 2026

---

## Introducción

Este programa demuestra el uso de OpenMP para realizar operaciones en paralelo sobre arreglos. Se inicializan dos arreglos `a` y `b` con valores calculados, y se computa un tercer arreglo `c` donde cada elemento es la suma de los elementos correspondientes: `c[i] = a[i] + b[i]`. La operación de suma se distribuye entre múltiples hilos usando la directiva `#pragma omp parallel for`.

---

## Repositorio

[https://github.com/tu-usuario/openmp-demo](https://github.com/tu-usuario/openmp-demo)

---

## Capturas de Pantalla

### Ejecución 1: N = 1000, chunk = 100

```
Sumando Arreglos en Paralelo!
Imprimiendo los primeros 10 valores del arreglo a:
0 - 10 - 20 - 30 - 40 - 50 - 60 - 70 - 80 - 90 -
Imprimiendo los primeros 10 valores del arreglo b:
11.1 - 14.8 - 18.5 - 22.2 - 25.9 - 29.6 - 33.3 - 37 - 40.7 - 44.4 -
Imprimiendo los primeros 10 valores del arreglo c:
11.1 - 24.8 - 38.5 - 52.2 - 65.9 - 79.6 - 93.3 - 107 - 120.7 - 134.4 -
```

### Ejecución 2: N = 100000, chunk = 100

```
Sumando Arreglos en Paralelo!
Imprimiendo los primeros 10 valores del arreglo a:
0 - 10 - 20 - 30 - 40 - 50 - 60 - 70 - 80 - 90 -
Imprimiendo los primeros 10 valores del arreglo b:
11.1 - 14.8 - 18.5 - 22.2 - 25.9 - 29.6 - 33.3 - 37 - 40.7 - 44.4 -
Imprimiendo los primeros 10 valores del arreglo c:
11.1 - 24.8 - 38.5 - 52.2 - 65.9 - 79.6 - 93.3 - 107 - 120.7 - 134.4 -
```

---

## Explicación del Código

### Parámetros Principales

| Parámetro | Valor | Descripción |
|-----------|-------|-------------|
| `N` | 100000 | Tamaño de los arreglos |
| `chunk` | 100 | Iteraciones por bloque asignado a cada hilo |
| `mostrar` | 10 | Elementos a imprimir |

### Región Paralela

```cpp
#pragma omp parallel for \
shared(a, b, c, pedazos) private(i) \
schedule(static, pedazos)
for (i = 0; i < N; i++)
    c[i] = a[i] + b[i];
```

**Directivas OpenMP:**

- `parallel for`: Crea hilos y distribuye las iteraciones del ciclo entre ellos
- `shared(a, b, c, pedazos)`: Variables compartidas entre todos los hilos
- `private(i)`: Cada hilo tiene su propia copia del índice `i`
- `schedule(static, pedazos)`: Asigna bloques de 100 iteraciones consecutivas a cada hilo

### Distribución del Trabajo

Con `schedule(static, 100)` y 12 hilos:

| Hilo | Iteraciones |
|------|-------------|
| 0 | 0-99, 1200-1299, ... |
| 1 | 100-199, 1300-1399, ... |
| 2 | 200-299, 1400-1499, ... |
| ... | ... |

Esta distribución en bloques contiguos mejora la localidad de caché.

### Resultados

Los valores de `c[i]` confirman la suma correcta:
- `c[0] = a[0] + b[0] = 0 + 11.1 = 11.1`
- `c[1] = a[1] + b[1] = 10 + 14.8 = 24.8`

---

## Reflexión sobre Programación Paralela

### Utilidad

La programación paralela permite aprovechar múltiples núcleos del procesador para reducir el tiempo de ejecución. Como señala Pancake (1996), "si ejecutar un programa en un CPU toma 10 horas, ¿por qué no usar 10 CPUs y obtener resultados en solo una hora?" (p. 18).

Este programa es un ejemplo de **paralelismo perfecto** (o "embarrassingly parallel"): las operaciones sobre cada elemento son completamente independientes, sin necesidad de comunicación entre hilos.

### Implicaciones

Sin embargo, el paralelismo tiene costos. Según Pancake (1996):

1. **Ley de Amdahl**: El contenido serial limita la aceleración máxima. Si el 5% del programa es serial, el speedup máximo es 20x, sin importar cuántos CPUs se usen.

2. **Overhead**: Crear hilos, sincronizar y distribuir trabajo consume tiempo. Para arreglos pequeños, este overhead puede superar el beneficio.

3. **Memoria**: Los arreglos en el stack tienen límite (~8 MB). Para N muy grande, se produce error de segmentación y se requiere memoria dinámica (heap).

### Dificultades

- Elegir el tamaño de `chunk` adecuado: muy pequeño causa overhead, muy grande causa desbalance
- Evitar condiciones de carrera en variables compartidas
- Depuración más compleja que código serial

---

## Referencias

Pancake, C. M. (1996). Is parallelism for you? *IEEE Computational Science and Engineering*, *3*(2), 18-37. https://doi.org/10.1109/99.503307
