# Actividad Ordenamiento
Emiliano Acuña - A01254706

Implementación individual en C++ de tres algoritmos de búsqueda sobre `vector<int>`,
con experimentación de desempeño para tamaños de entrada de 10⁵ a 10⁸ elementos.

## Archivos

- `busqueda.hpp` 
- `busqueda.cpp` 
- `main.cpp` 

## Compilación y ejecución


> A través del compilador CMAKE.



## Complejidad computacional

| Función           | Precondición                  | Complejidad temporal | Complejidad espacial |
|--------------------|-------------------------------|-----------------------|------------------------|
| `busquedaLineal`   | Ninguna (no requiere orden)   | O(n)                  | O(1)                   |
| `busquedaBinaria`  | Vector ordenado ascendente    | O(log₂ n)             | O(1)                   |
| `busquedaTrinaria` | Vector ordenado ascendente    | O(log₃ n) ≈ O(log n)  | O(1)                   |

Las tres implementaciones son **iterativas** (no recursivas), por lo que no consumen
memoria adicional de pila.

## Metodología de medición

1. Para cada tamaño de entrada n se genera un vector<int> de n elementos aleatorios y se ordena de forma ascendente. La generación y el ordenamiento NO se incluyen en el tiempo reportado.
2. Se seleccionan 30 índices aleatorios del vector y se busca el valor
    almacenado en cada uno de ellos.
3. Para cada una de las 30 búsquedas se mide el tiempo empleado
    por la función de búsqueda, usando
    chrono::high_resolution_clock.
4. Se calcula el promedio de las 30 mediciones para cada combinación
    (algoritmo, tamaño de entrada) y se reporta en microsegundos (us).
5. Los mismos 30 índices se reutilizan para los tres algoritmos en un
    mismo tamaño de entrada.

## Tabla de resultados (tiempo promedio, en microsegundos µs)

| Tamaño de entrada | Búsqueda Lineal | Búsqueda Binaria | Búsqueda Trinaria       |
|-------------------|--|------------------|-------------------------|
| 10⁵ (100,000)     | 55.8033 | 0.1767           | 0.15                    |
| 10⁶ (1,000,000)   | 517.8333 | 0.3767           | 0.26                    |
| 10⁷ (10,000,000)  | 5419.62 | 1.0467           | 0.68                    |
| 10⁸ (100,000,000) | 51815.8733 | 1.6633                | 1.0933                       |

## Análisis de resultados

### 1. Comportamiento al incrementar el tamaño de entrada

Al multiplicar `n` por 10 en cada paso:

- **Búsqueda lineal**: el tiempo se multiplica aproximadamente por **10** en cada salto, consistente con su complejidad **O(n)**: si el
  trabajo es directamente proporcional a `n`, multiplicar `n` por 10 debe multiplicar el
  tiempo por ~10. 

- **Búsqueda binaria y trinaria**: el tiempo crece de forma mucho más lenta. Al pasar de
  10⁵ a 10⁸, el tiempo de la binaria solo se multiplica por
  ~18x. Esto es
  justamente lo esperado de una complejidad **logarítmica**: log(1000·n) − log(n) es una
  constante (no depende de n), por lo que el número de pasos crece de forma aditiva, no
  multiplicativa, al aumentar `n` en un factor fijo.

### 2. Complejidad computacional de cada algoritmo

- `busquedaLineal`: en el peor caso recorre los `n` elementos → **O(n)**.
- `busquedaBinaria`:  **O(log₂ n)**.
- `busquedaTrinaria`: **O(log₃ n)**,
  esto es **asintóticamente equivalente** a O(log n): ambas pertenecen a la misma clase de
  complejidad, y solo difieren por una constante multiplicativa.

### 3. Diferencias entre binaria y trinaria pese a tener ambas complejidad logarítmica 

Aquí es donde el análisis puramente asintótico (O(log n) para ambas) **no basta** para
predecir cuál es más rápida en la práctica; hay que analizar la constante oculta detrás
de la notación O:

- **Número de iteraciones**: la trinaria necesita menos iteraciones que la binaria para el
  mismo `n`, porque `log₃ n < log₂ n` (concretamente, `log₃ n ≈ 0.631 · log₂ n`).
- **Trabajo por iteración**: sin embargo, cada iteración de la trinaria hace **más
  comparaciones** que cada iteración de la binaria. La binaria evalúa un solo punto medio. La trinaria evalúa **dos** puntos de
  corte.
- Multiplicando pasos por trabajo-por-paso: la binaria realiza en total del orden de
  `2 log₂ n` comparaciones, mientras que la trinaria realiza del orden de
  `4 log₃ n = (4 / log₂ 3) · log₂ n ≈ 2.52 · log₂ n` comparaciones. **En número total de
  comparaciones, la trinaria (~2.52·log₂n) requiere más operaciones que la binaria
  (~2·log₂n)**, a pesar de tener menos iteraciones.
- Esto explica por qué, en teoría, no existe una razón matemática sólida para esperar que
  la trinaria sea más rápida que la binaria: dividir en más partes reduce la profundidad
  del proceso, pero incrementa el costo de cada paso, y en este caso el segundo efecto
  domina en número de comparaciones.


### 4. Conclusión



- Si se compara **búsqueda lineal contra las otras dos**, la respuesta es inequívoca:
  la lineal es dramáticamente más lenta a partir de vectores medianamente grandes, y esto es exactamente lo que predice la teoría: O(n) crece sin límite
  mientras que O(log n) crece extremadamente despacio. **Para datasets grandes ordenados,
  la búsqueda lineal nunca es una opción competitiva.**
- Si se compara **binaria contra trinaria**, ambas pertenecen a la misma clase de
  complejidad asintótica, O(log n); **matemáticamente ninguna es "mejor" que la otra en el
  límite**, solo difieren en la constante multiplicativa dentro de esa clase. El análisis
  teórico de comparaciones incluso sugiere que la trinaria debería requerir
  *más* trabajo total que la binaria, no menos. Que la trinaria haya salido ligeramente
  adelante en esta implementación y en este hardware específico es un efecto de bajo nivel
  (localidad de memoria/caché) y no una propiedad general del algoritmo — en otro compilador,
  arquitectura o patrón de acceso a memoria, el resultado podría invertirse fácilmente.

**Conclusión final:** el algoritmo con mejor desempeño garantizado y consistente, tanto en
teoría como en la práctica, es cualquiera de los dos algoritmos logarítmicos
(**búsqueda binaria** o **búsqueda trinaria**) sobre la búsqueda lineal, dada la brecha de
varios órdenes de magnitud confirmada experimentalmente. Entre binaria y trinaria no hay un
ganador universal: ambas son asintóticamente equivalentes (O(log n)), la trinaria hace más
comparaciones por búsqueda en teoría, y la pequeña ventaja de la trinaria observada aquí es
atribuible a efectos de memoria/caché específicos de esta ejecución, no a una superioridad
algorítmica demostrable. En la práctica, dado que la búsqueda binaria es más simple de
implementar, más fácil de verificar y no depende de efectos de caché para ser competitiva.