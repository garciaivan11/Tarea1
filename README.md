# PLANIFICADOR DINÁMICO TAREAS (Smart TODO)
> Iván García Briones - Ingeniería Civil Informática
---

## Objetivo del programa:
Esta aplicación es un sistema de gestión de tareas organizado por categorías personalizadas. El programa utiliza el sistema FIFO (First In, First Out) para asegurar que el despacho de pendientes respecte estrictamente el orden de llegada de las tareas, sin importar su categoría.

---

## Como compilar el programa:

Para compilar y ejecutar este proyecto, asegúrate de tener instalado un compilador de C (como **GCC**) y sigue estos pasos:

1. Descomprimir el archivo: Asegúrate de que el archivo tarea1.c y la carpeta tdas/ estén en el mismo directorio.

1. Compilación: Abre una terminal en la carpeta raíz del proyecto y ejecuta el siguiente comando:

```
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
```

Nota: El flag -Wno-unused-result se utiliza para omitir advertencias sobre resultados de funciones no utilizados (como en scanf), manteniendo la terminal limpia durante la compilación.

3. Ejecución: Una vez compilado, inicia el programa con:

```
./tarea1
```

---

## STRUCTS:

### 1. Tarea:
Este struct permite guardar la descripción de la tarea en un maximo de 99 caracteres (+ el nulo), el nombre de la categoría a la que pertenece y la hora a la que se registró la tarea. 

### 2. Categoria:
Permite crear grupos de tareas. Almacena el nombre de la categoría y un contador de tareas pendientes, lo que permite informar al usuario cuántos pendientes tiene en cada área específica.

---

## FUNCIONES:
### 1. Registrar Categoría:
Esta función permite al usuario registrar una nueva categoría en su lista. Se ingresa el nombre de la categoría y se valida que no exista previamente recorriendo la lista; en caso de duplicado, se informa al usuario y se realiza un return. De lo contrario, se reserva memoria dinámicamente para la nueva categoría, se inicializan sus datos y se guarda en la lista, mostrando un mensaje de éxito.

### 2. Eliminar Categoría:
Permite eliminar una categoría y todas sus tareas asociadas. Funciona de la siguiente manera:

1. Se solicita el nombre de la categoría y se convierte a mayúsculas para compararlo uniformemente.

1. Se recorre la lista de categorías. Al encontrarla, se usa popCurrent para sacarla de la lista, se libera su memoria con free() y se activa un flag = 1 para confirmar el hallazgo.

1. Si no se encuentra (flag en 0), se emite un mensaje y se retorna. Si se encontró, se crea una colaAux para el traspaso de tareas.

1. Se itera sobre la cola original extrayendo cada tarea: si no pertenece a la categoría eliminada, se inserta en colaAux; si pertenece, se libera su memoria permanentemente.

1. Se traspasan los datos de colaAux de vuelta a la cola original para restaurar los pendientes modificados.

1. Se libera la memoria de colaAux y finaliza la función.

### 3. Mostrar Categorías:
Esta función recorre la lista de categorías y muestra los nombres junto a la cantidad de tareas pendientes de cada una. Se utiliza un diseño de tabla mediante especificadores de formato para que los datos se vean organizados y legibles en la terminal.

### 4. Registrar Pendiente:
Permite al usuario añadir una tarea nueva a la cola global:

- Se solicita la categoría: si no existe en la lista, el sistema la crea automáticamente.
- Se pide la descripción y se captura la fecha/hora exacta del registro mediante <time.h>.
- Se reserva memoria para la nueva tarea, se inicializan sus campos y se inserta al final de la cola general.
- Se incrementa el contador de pendientes de la categoría correspondiente.

### 5. Atender Pendiente:
Esta función extrae y muestra la tarea más antigua de la cola (sistema FIFO). Se desencola el primer elemento y se valida que exista; luego, se muestran sus datos en pantalla. El sistema busca la categoría de la tarea en la lista para reducir su contador de pendientes en 1 y libera la memoria de la tarea atendida con free(). Finalmente, se previsualiza cuál es la siguiente tarea en la fila.

### 6. Visualización del Tablero General:
Muestra todas las tareas anotadas, desde la más antigua a la más reciente. Para visualizar la lista sin alterar el orden ni borrar nada (evitando el comportamiento destructivo de las colas), se utiliza queue_next. Esto permite "caminar" por los nodos de la cola uno a uno para armar la tabla, manteniendo la integridad de los datos para su posterior uso.

---

## FUNCIONES DE APOYO:
### 1. Convertir Mayusculas:
Esta función transforma los nombres de las categorías a mayúsculas. Esto permite comparar cadenas de texto de forma uniforme (evitando errores por diferencias de escritura) y mejora la estética de las tablas de datos.

---

## Ejemplo de uso:
Para probar el programa rápidamente:

1. Inicia el sistema y usa la opción 1 para crear la categoría PROGRA.

1. Usa la opción 4 para anotar una tarea en la categoría PROGRA con la descripción Terminar tarea 1.

1. Usa la opción 6 (Tablero) para ver que se guardó bien con la hora de tu PC.

1. Usa la opción 5 (Atender) para simular que ya la hiciste y ver cómo se borra del sistema.

---

## Estado de las funciones:

1. **Nueva Categoría**: FUNCIONANDO. Que hace: Crea y valida duplicados.
1. **Eliminar Categoría**: FUNCIONANDO. Que Hace: Borra categoría y todas sus tareas.
1. **Mostrar Categorías**: FUNCIONANDO. Que hace: Muestra tabla con contadores.
1. **Registrar Pendiente**: FUNCIONANDO. Que hace: Registra tareas y guarda la hora usando <time.h>
1. **Atender Siguiente**: FUNCIONANDO. Que hace: Muestra la tarea que se debe realizar y la elimina de la lista de tareas usando el sistema FIFO.
1. **Tablero General**: FUNCIONANDO. Que hace: Muestra las tareas junto a sus categorías en lista mediante la hora de registro (igual que FIFO).
1. **Filtrado por Categoría**: EN DESARROLLO. Aparece en el menú pero falta la lógica.

---

## Dificultades y Soluciones: (Escrito en línea de tiempo)

### FUNCIÓN: Eliminar Categoría
**1. Problema:** Lista general y por categoría comparten punteros, dificultando las eliminaciones de tareas
> 03/04 - 04:20 > Me di cuenta de que al tener en categorias una lista de tareas con punteros a datos que están conectados a su vez con la lista global, puede generar un error, ya que al eliminar una categoría hay que vaciar primero la lista de tareas, lo que dejaría toda la lista global desenlazada en caso de tener tareas dispersas. Por ende habría que generar alguna solción como guardar dos veces cada dato en variables diferentes, aunque no sería lo más eficiente.

> 03/04 - 4:34 > **-- Posible Solución --** Se me ocurre que podría realizar una única lista, y luego a la hora de mostrar por filtro o tener que eliminar por categoría se tendrá que iterar buscando por nombre, aprovechando que el struct de tareas ya cuenta con nombre de categoría. El único problema es que consume bastante proceso tener que iterar en varias ocaciones, sin embargo al no estar esperando millones de tareas, no se convertiría realmente en un problema para el computador.

**2. Problema:** Eliminar una tarea deja el puntero al actual vacío, teniendo que iterar varias veces la lista completa por tener que reiniciar desde el first.
> 03/04 - 19:25 > Hice el cambio a una sola lista general, sin embargo primero me encargo de eliminar la categoría y después las tareas que sean de esa categoría que borré, pero me di cuenta que hay un problema respecto a hacer eso, por que si bien el popCurrent nos deja current en el siguiente valor, la tareaActual se quedá apuntando a la dirección de memoria que fue borrada y despues no tengo como avanzar. 
>> - Posible Solución -> Se me ocurre que podría eliminar la tarea y empezar desde 0 el tareaActual, reiniciando el bucle por así decirlo, para poder tener el puntero puesto en algo válido. **Continuación en: "03/04 - 19:35 DECISIÓN: Lista o Cola?"**

> **SOLUCIONADO:** 03/04 - 19:35 > Finalmente se optó por el uso de colas que permitirá recorrer en una sola pasada las tareas. (*Más detalles en "03/04 - 19:35 DECISIÓN: Lista o Cola?"*)

### DECISIÓN: Lista o Cola?

> 03/04 - 4:47 > Detectando el programa la primera idea que se me vino a la cabeza fue el uso de una cola, ya que cumple completamente con el sistema FIFO que se requiere, sin embargo pensando bien en todo, creo que la mejor opción es una Lista (como he estado trabajando hasta el momento), esto debido a que nos permite manejar mejor los datos y gracias a su pushBack y popFront, puede trabajar como una cola. Esto permite trabajar con elementos del centro.

> **SOLUCIONADO:** 03/04 - 19:35 >  Pensando en el problema de eliminar las tareas de la lista acabo de resolver mi duda y es que que la cola al final es la ganadora, por que con la lista tendría que recorrer muchas veces al ser una lista simple. Por ende con la cola hago una pasada y voy descartando lo que no me sirve. Entonces al final es el TDA más optimo para este problema.

### REGISTRAR HORA EXACTA:
> 04/04 - 00:39 > Hasta el momento no me han enseñado como usar bibliotecas externas como tal, pero toca investigar sobre como hacer que se registre la hora exacta de una tarea, probablemente mediante una biblioteca.

> 04/04 - 00:41 > Esto es lo que encontré en google sobre una biblioteca que me permita registrar la hora exacta: 
>"La biblioteca estándar de C diseñada para manejar fecha y hora es <time.h>. Esta biblioteca, combinada con funciones de manipulación de cadenas como sprintf o strftime (de <stdio.h> o <time.h>), permite capturar la hora exacta de un input y almacenarla en una variable char (cadena de caracteres). 
*Biblioteca y funciones principales*
<time.h>: Proporciona tipos como time_t (para obtener el tiempo actual) y estructuras como struct tm (para desglosar hora, minuto, segundo).
time(): Obtiene la hora actual del sistema.
localtime(): Convierte time_t a un tiempo local desglosado en struct tm.
strftime(): Formatea la estructura de tiempo (tm) en una cadena de caracteres (char[]) personalizada (ej. "HH:MM:SS"). "