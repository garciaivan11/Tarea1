# Informe de Contexto Completo — Tarea 1: Planificador de Tareas (TODO)
## Estructura de Datos — 3er Semestre PUCV

---

## SECCIÓN 1 — CÓMO USAR ESTE CHAT 

> ROL: Quiero que tomes un rol de estilo profesor pero a la vez de amigo con humor y uso de emojis y cosas visuales para mejorar el aprendizaje
> RESPUESTAS: Las respuestas no deben ser ni cortas ni muy largas, la idea es poder aprender bien y rapido.
> CODIGO: No sebes escribir codigo en ningun momento, el uso de este chat es unicamente para orientiación, el profesor dijo que limitaramos ese poder de respuestas, si te pido codigo es solo limitaciones a cosas muy pequeñas y que no tengan un criterio de evaluación que impacte en la nota, ya que se están evaluando conocimientos. Usa tu propio criterio para decidir y preguntarte si eso que te pido es algo muy importante y limitate a darme respuestas que no debas como profesor.
> ESTILO: Trata de ser amigable, escribir con terminos adecuados pero si son especificos explicarlos, de forma que me ayude a comprender a lo que te refieres.
> En general necesito que me orientes y no me des respuestas a cosas que puedan decidir notoriamente mi calificación, de esta forma mantenemos un formato de aprendizaje propio con un medio de investigación como lo eres tu más veloz.

---

## SECCIÓN 2 — CONTEXTO DE LA ASIGNATURA

- **Asignatura:** Estructura de Datos
- **Carrera:** ICD / ICI (se mencionan ambos profesores)
- **Universidad:** PUCV (Pontificia Universidad Católica de Valparaíso)
- **Semestre:** 3er semestre
- **Profesores:**
  - fabian.pizarro.m@mail.pucv.cl (ICD)
  - ignacio.araya@pucv.cl (ICI)

---

## SECCIÓN 3 — DESCRIPCIÓN DE LA TAREA

### Nombre de la tarea
**Planificador de Tareas (TODO)** — Sistema de gestión de tickets/tareas con categorías y despacho FIFO.

> Nota: El código base en el repositorio tiene el nombre "Gestión Hospitalaria" en el menú, pero el enunciado final define claramente que la tarea es el **Planificador TODO** con categorías. El código base es solo un esqueleto de ejemplo; el menú y nombres deben ajustarse a la tarea real.

### Objetivo general
Aplicar conocimientos de **Tipos de Datos Abstractos (TDAs)** en C — específicamente List, Stack y Queue — para implementar una aplicación funcional. La idea es "olvidarse" de la implementación interna de las estructuras y trabajar exclusivamente a través de las operaciones de los TDAs.

---

## SECCIÓN 4 — REQUERIMIENTOS FUNCIONALES (7 opciones del menú)

| Opción | Nombre | Descripción |
|--------|--------|-------------|
| 1 | Nueva Categoría | Recibe un nombre y crea una nueva categoría en el sistema |
| 2 | Eliminar Categoría | Recibe un nombre, elimina la categoría **y purga todas las tareas asociadas a ella** |
| 3 | Mostrar Categorías | Lista todas las categorías existentes |
| 4 | Registrar Tarea | Recibe nombre, descripción y categoría. Asigna **hora exacta de check-in** automáticamente al momento del registro |
| 5 | Atender Siguiente Tarea | Extrae y **elimina permanentemente** la tarea más antigua del sistema (despacho **FIFO global**, no por categoría) |
| 6 | Visualización General | Muestra todas las tareas pendientes ordenadas por antigüedad (la más antigua primero) |
| 7 | Filtrar por Categoría | Muestra las tareas de una categoría específica, **sin alterar el orden global** |

### Notas clave sobre los requerimientos
- El despacho FIFO (opción 5) es **global**: atiende la tarea más antigua de todo el sistema, independientemente de la categoría.
- La hora de check-in se asigna **automáticamente** al registrar la tarea (no la ingresa el usuario).
- Eliminar una categoría debe **eliminar también todas las tareas** que pertenecen a esa categoría (no dejarlas huérfanas).
- El filtrado por categoría (opción 7) es "pasivo": no modifica ningún orden ni extrae elementos.

---

## SECCIÓN 5 — CRITERIOS DE EVALUACIÓN

| Criterio | Porcentaje | Descripción |
|----------|-----------|-------------|
| Formato | 15% | Organización del código, nombres descriptivos, comentarios adecuados |
| TDAs | 15% | Comprensión y uso correcto de los TDAs. Acceso correcto a través de sus operaciones (no acceder a internals) |
| Requerimientos funcionales | 30% | Cumplimiento de las 7 opciones del menú. Manejo de errores y excepciones |
| Requerimientos no funcionales | 10% | Código eficiente en tiempo y memoria |
| README.md | 10% | Documentación, fallos conocidos y causas posibles, instrucciones de ejecución |
| Actividades de Avance | 20% | Trabajo realizado en clases/ayudantía (diseño preliminar, avances entregados) |

---

## SECCIÓN 6 — RESTRICCIONES TÉCNICAS

1. **Lenguaje:** C (estándar, sin C++)
2. **Solo TDAs:** No acceder directamente a los campos internos de las estructuras (e.g., no hacer `lista->head`). Solo usar las funciones de la API pública.
3. **Librerías disponibles:** Las que están en la carpeta `tdas/` (list, stack, queue, map, heap, extra). Se pueden usar librerías estándar de C.
4. **No inventar estructuras de datos:** Usar los TDAs provistos, no implementar listas/colas propias desde cero.

---

## SECCIÓN 7 — ESTRUCTURA DEL REPOSITORIO

```
Tarea1/
├── tarea1.c          ← Archivo principal (aquí va todo el desarrollo)
└── tdas/
    ├── list.h        ← Interfaz del TDA Lista
    ├── list.c        ← Implementación del TDA Lista (enlazada simple)
    ├── stack.h       ← TDA Pila (implementada sobre List)
    ├── queue.h       ← TDA Cola (implementada sobre List)
    ├── map.h         ← TDA Mapa (clave-valor)
    ├── map.c         ← Implementación del Mapa
    ├── multimap.h    ← TDA Multimapa
    ├── heap.h        ← TDA Heap (cola de prioridad)
    ├── heap.c        ← Implementación del Heap
    ├── extra.h       ← Utilidades (limpiarPantalla, presioneTecla, CSV, split)
    └── extra.c       ← Implementación de utilidades
```

---

## SECCIÓN 8 — CÓDIGO EXISTENTE (tarea1.c)

Este es el estado actual del archivo principal. Es un **esqueleto vacío** con el menú definido y dos funciones stub:

```c
#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");   // ← nombre a cambiar
  puts("========================================");

  puts("1) Nueva Categoría");
  puts("2) Eliminar Categoría");
  puts("3) Mostrar Categorías");
  puts("4) Registrar Pendiente");
  puts("5) Atender Siguiente");
  puts("6) Visualización del Tablero General");
  puts("7) Filtrado por Categoría");
  puts("8) Salir");
}

void registrar_categorias(List *categorias) {
  printf("Registrar nueva categoría\n");
  // Aquí implementarías la lógica para registrar una nueva categoría
}

void mostrar_categorias(List *categorias) {
  printf("Categorías:\n");
  // Aquí implementarías la lógica para mostrar las categorías
}

int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // espacio antes de %c para consumir el newline

    switch (opcion) {
    case '1':
      registrar_categorias(categorias);
      break;
    case '2':
      // Lógica para eliminar una categoría
      break;
    case '3':
      mostrar_categorias(categorias);
      break;
    case '4':
      // Lógica para registrar un paciente
      break;
    case '5':
      // Lógica para atender al siguiente paciente
      break;
    case '6':
      // Lógica para mostrar el tablero general
      break;
    case '7':
      // Lógica para filtrar por categoría
      break;
    case '8':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  list_clean(categorias);
  return 0;
}
```

---

## SECCIÓN 9 — API COMPLETA DE LOS TDAs DISPONIBLES

### TDA Lista (`tdas/list.h` + `tdas/list.c`)

Implementación interna: **lista enlazada simple** con punteros `head`, `tail` y `current`.

```c
List *list_create();                        // Crea lista vacía
void *list_first(List *L);                  // Retorna primer elemento, mueve current al inicio
void *list_next(List *L);                   // Avanza current y retorna ese elemento
void  list_pushFront(List *L, void *dato);  // Inserta al inicio
void  list_pushBack(List *L, void *dato);   // Inserta al final
void  list_pushCurrent(List *L, void *dato);// Inserta después del current
void *list_popFront(List *L);               // Elimina y retorna el primero
void *list_popBack(List *L);                // Elimina y retorna el último
void *list_popCurrent(List *L);             // Elimina y retorna el current
void  list_clean(List *L);                  // Elimina todos los nodos (no libera el struct List)
int   list_size(List *L);                   // Retorna cantidad de elementos
```

**Patrón de iteración estándar:**
```c
// Para recorrer todos los elementos:
TipoDato *elem = list_first(lista);
while (elem != NULL) {
    // usar elem...
    elem = list_next(lista);
}
```

**Notas importantes de la implementación:**
- `list_clean` libera los nodos pero NO el struct `List` en sí.
- `list_popCurrent` puede dejar `current` en un estado indefinido — verificar bien al eliminar durante iteración.
- La lista es de enlace simple: no tiene `prev`, por eso `list_popBack` es O(n).

---

### TDA Pila (`tdas/stack.h`)

**Es un alias de List** — `typedef List Stack`. Todo método de Stack llama internamente a List.

```c
Stack *stack_create(Stack *stack);   // Crea pila (llama list_create)
void   stack_push(Stack *s, void *data); // Inserta al frente (list_pushFront)
void  *stack_top(Stack *s);          // Ver tope sin extraer (list_first)
void  *stack_pop(Stack *s);          // Extrae del tope (list_popFront)
void   stack_clean(Stack *s);        // Limpia (list_clean)
```

- Comportamiento **LIFO**: el último en entrar es el primero en salir.
- El "tope" está en `head` de la lista subyacente.

---

### TDA Cola (`tdas/queue.h`)

**También es un alias de List** — `typedef List Queue`.

```c
Queue *queue_create(Queue *queue);     // Crea cola (llama list_create)
void   queue_insert(Queue *q, void *data); // Inserta al final (list_pushBack)
void  *queue_remove(Queue *q);         // Extrae del frente (list_popFront)
void  *queue_front(Queue *q);          // Ver frente sin extraer (list_first)
void  *queue_next(Queue *q);           // Avanza iteración (list_next) — operación especial
void   queue_clean(Queue *q);          // Limpia (list_clean)
```

- Comportamiento **FIFO**: el primero en entrar es el primero en salir.
- `queue_insert` → agrega por atrás. `queue_remove` → saca por adelante.
- `queue_next` permite iterar sin extraer (útil para visualización).

---

### TDA Mapa (`tdas/map.h` + `tdas/map.c`)

Estructura clave-valor. Puede crearse ordenado o no ordenado.

```c
// Creación — requiere función comparadora
Map *map_create(int (*is_equal)(void *key1, void *key2));           // mapa sin orden
Map *sorted_map_create(int (*lower_than)(void *key1, void *key2));  // mapa ordenado

// Operaciones
void      map_insert(Map *map, void *key, void *value); // Inserta par clave-valor
MapPair  *map_remove(Map *map, void *key);              // Elimina y retorna el par
MapPair  *map_search(Map *map, void *key);              // Busca por clave, retorna par
MapPair  *map_first(Map *map);                          // Primer par (para iterar)
MapPair  *map_next(Map *map);                           // Siguiente par
void      map_clean(Map *map);                          // Limpia el mapa

// MapPair tiene:
// pair->key   → puntero a la clave
// pair->value → puntero al valor
```

---

### TDA Extra (`tdas/extra.h` + `tdas/extra.c`)

Utilidades de apoyo:

```c
void   limpiarPantalla();                               // system("clear")
void   presioneTeclaParaContinuar();                    // Pausa con mensaje
char **leer_linea_csv(FILE *archivo, char separador);   // Parsea línea CSV
List  *split_string(const char *str, const char *delim);// Divide string por delimitador
```

---

## SECCIÓN 10 — CONCEPTOS CLAVE PARA LA TAREA

### ¿Qué es un TDA?
Un **Tipo de Dato Abstracto** define un conjunto de datos y las **operaciones permitidas** sobre ellos, sin exponer cómo están implementados internamente. En este curso, significa que solo se usan las funciones de la API (list_pushBack, queue_insert, etc.) y **nunca** se accede a campos como `->head`, `->tail`, `->data`, etc.

### FIFO (First In, First Out)
La tarea más antigua (la que lleva más tiempo esperando) es la primera en atenderse. La Cola es el TDA natural para esto: se inserta por atrás (`queue_insert`) y se extrae por adelante (`queue_remove`).

### Hora de check-in
En C se obtiene con `time()` de `<time.h>` y se formatea con `localtime()` + `strftime()` o se guarda directamente como `time_t`. Ejemplo conceptual:
```c
#include <time.h>
time_t ahora = time(NULL); // timestamp del momento exacto
// Para mostrar: struct tm *t = localtime(&ahora); strftime(buf, sizeof(buf), "%H:%M:%S", t);
```

### Gestión de memoria en C
- Cada `struct` que se crea con `malloc` debe liberarse con `free` cuando ya no se necesita.
- Al eliminar una categoría, primero hay que liberar todas las tareas asociadas, luego la categoría misma.
- Los TDAs provistos (list_clean, etc.) liberan los **nodos** de la estructura, pero no el `data` que apuntan — eso es responsabilidad del programador.

---

## SECCIÓN 11 — PREGUNTAS DE REPASO RELEVANTES DEL PPT (para el Control 1)

### Pilas
- ¿Cómo encontrar el elemento del medio en una pila?
- ¿Cómo usar una pila para implementar Ctrl+Z (deshacer)?
- ¿Cómo implementar una pila con dos colas?
- ¿Cómo implementar una pila con un arreglo?
- Ventaja clave de pila con lista enlazada vs arreglo.

### Colas
- ¿Cómo invertir el contenido de una cola con una pila auxiliar?
- ¿Cómo determinar si dos colas tienen el mismo contenido y orden?
- ¿Cómo implementar una cola con dos pilas (comportamiento FIFO)?
- Situación real donde es mejor una cola que una pila.
- Ventaja del arreglo circular sobre arreglo lineal para colas.

### Listas enlazadas
- ¿Cómo eliminar un nodo específico en una lista simple dada su referencia?
- Diferencia entre lista simple y doblemente enlazada (navegación y operaciones).
- Diferencia entre nodo simple y nodo doble.
- ¿Cómo saber si recorriste toda una lista circular sin contador?
- ¿Cómo insertar un nodo entre dos nodos en lista doble?

### Manejo de memoria
- ¿Qué pasa si accedes a memoria ya liberada con `free`?
- ¿Qué problemas surgen de mala gestión de memoria en estructuras dinámicas?
- Riesgos de punteros no inicializados en C y cómo evitarlos.
- Precauciones con punteros para evitar errores de acceso a memoria.
- Diferencias entre segmentos: **stack**, **static** y **heap**. ¿Dónde van las variables globales?

---

## SECCIÓN 12 — TABLA DE OPERACIONES POR TIPO DE LISTA (del PPT)

El PPT muestra una tabla de qué operaciones son eficientes (`:)`) o no (`:(`)) según el tipo de lista:

| Operación | Simple | Doble | Circular Simple | Circular Doble | Arreglo circular |
|-----------|--------|-------|-----------------|----------------|-----------------|
| next | :) | :) | :) | :) | :) |
| prev | :( | :) | :( | :) | :) |
| Push Front | :) | :) | :) | :) | :) |
| Push Back | :( | :( | :) | :) | :) |
| Pop Front | :) | :( | :) | :) | :) |
| Pop Back | :( | :( | :( | :) | :) |
| Pop Current | :( | :) | :( | :) | :( |
| Push Current | :) | :) | :) | :) | :( |
| Get_i | :( | :( | :( | :( | :) |

> La implementación real de `list.c` en el proyecto es **lista simple** (tiene `head`, `tail`, `current`, pero no `prev`).

---

## SECCIÓN 13 — ACTIVIDAD DE DISEÑO (lo que se esperaba hacer en clases)

El PPT pedía como actividad de avance:

1. **Identificar las entidades (structs)** necesarias para la tarea y sus campos.
2. **Decidir qué TDAs** se usarán para almacenar/gestionar cada entidad, con nombre descriptivo. Ejemplo:
   - `cola_tareas`: Cola para almacenar tareas en orden de llegada global (FIFO)
   - `lista_categorias`: Lista para almacenar las categorías existentes
3. **Describir en palabras** (no en código) cómo se implementa cada opción del menú. Ejemplo:
   - Registrar tarea:
     1. Leer nombre, descripción y categoría del usuario
     2. Verificar que la categoría existe
     3. Obtener timestamp actual con `time()`
     4. Crear struct Tarea con los datos
     5. Insertar en la cola global de tareas

---

## SECCIÓN 14 — NOTAS ADICIONALES INFERIDAS

- El `main.c` de ejemplo mencionado en el PPT está en: `https://replit.com/@IgnacioAraya2/TDAs#main.c` (referencia del profesor para ver cómo se usan los TDAs).
- El `limpiarPantalla()` usa `system("clear")` — esto funciona en Linux/Mac. En Windows puede requerir `system("cls")` o ajuste.
- `presioneTeclaParaContinuar()` usa dos `getchar()`: el primero consume el `\n` del buffer, el segundo espera input real.
- El `scanf(" %c", &opcion)` tiene un espacio antes de `%c` para consumir el newline pendiente — patrón importante a mantener.
- El README.md es obligatorio y vale 10%. Debe incluir: descripción, instrucciones de compilación/ejecución, y fallos conocidos con sus causas posibles.

---

*Informe generado automáticamente a partir de los archivos del repositorio y el material de la asignatura.*