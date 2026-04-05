# PLANIFICADOR DINÁMICO TAREAS (Smart TODO)
> Iván García Briones - Ingeniería Civil Informática
---

## Objetivo del programa:
Esta aplicación es un sistema de gestión de tareas organizado por categorías personalizadas. El programa utiliza el sistema FIFO (First In, First Out) para asegurar que el despacho de pendientes respete estrictamente el orden de llegada de las tareas.

---
## STRUCTS:

### 1. Tarea:
Este struct permite guardar la descripción de la tarea en un maximo de 99 caracteres (+ el nulo), el nombre de la categoría a la que pertenece y la hora a la que se registró la tarea. 

### 2. Categoria:
Con este struct podemo crear categorías introduciendo su nombre y por estetica en mensajes (poder mencionar cuantas le quedan de cada categoría) ir actualizando las tareas pendientes que tiene el usuario. 

---

## FUNCIONES:
### 1. Registrar Categoría:
Esta función permite al usuario registrar una nueva categoría a su lista, donde deberá ingresar el nombre de la categoría que desea agregar y luego se validará si esa categoría ya existe recorriendo la lista; en dicho caso se reportará al usuario que ya existe la categoría y se realiza un return, de lo contrario se reserva memoria para la nueva categoría y se valida que no hubiera problema al reservar memoria, para luego inicializar los datos, pasar el nombre de la categoría a la nueva variable de "nuevaCategoria" y finalmente guardar en la lista está nueva categoría mostrando en pantalla un mensaje de que se logró crear la categoría.

### 2. Eliminar Categoría:
Esta función permite eliminar una categoría y a su vez las tareas correspondiente a esa categoría, funciona de la siguiente manera: 
1. Se le pide al usuario el nombre de la categoría y se coloca en mayusculas para poder compararla con las de la lista de categorías. 
1. Se recorre la lista de categorías validando en cada iteración si el nombre que ingresó el usuario es igual al de la categoría que se esté verificando en cada iteración, en caso de encontrarla se hace un popCurrent para eliminar de la lista esa categoría y luego se libera la memoria de esa categoría, tambien se coloca el flag = 1 (nos permitirá confirmar que se contró una categoría valida para la eliminación de tareas) y se corta el ciclo. 
1. Se revisa si se encontró una categoría valida mediante el flag, en caso de que no se haya encontrado se emite un mensaje correspondiente y se retorna. Si hubo una categoría valida se crea una colaAux para el traspaso de tareas y se crea una variable tipo Tarea para guardar la tarea de cada iteración (*tareaActual). 
1. Se empieza a iterar para ir recorriendo la cola original y se va sacando el primer dato validando si pertenece a la categoría eliminada, en caso de que no pertenezca se agrega a la colaAux y en caso de que si pertenezca, se libera la memoria eliminandola para siempre. 
1. Se traspasan los datos de la colaAux a la original, pero está vez ya modificados sin las tareas correspondientes a la categoría que se deseaba eliminar.
1. Se libera la memoria de colaAux y acaba la función.

### 3. Mostrar Categorías:
Esta función recorre la lista de categorías y muestra las categorías existentes junto a la cantidad de tareas que contiene cada una, se utilizó un diseño tipo tabla para mostrar los datos, además de hacer uso de especificadores de formato para manejar el espaciado de los datos en un estilo más organizado y legible.

### 4. Registrar Pendiente:
Esta función permite al usuario crear una tarea y agregarla a su cola de tareas pendientes, 
- Se inicia pidiendo la categoría a la que pertenecerá la tarea para verificar que exista. 
- En caso de que la categoría no existe, se creará e inicializaran los datos usando el mismo nombre que el usuario ingresó.
- Se pide la descripción y además se registra la hora y fecha en que se hizo el ingreso de datos.
- Se crea la nueva tarea y se inicializan las variables con los datos recopilados.
- Se agrega la tarea a la lista general de tareas y se suma una tarea pendiente a la categoría perteneciente.

### 5. Atender Pendiente:
Esta función nos permite mostrar la primera tarea de la cola para atenderla y a su vez la elimina de la cola.
Para que funcioné se quita el primer elemento de la cola y se valida que sea un elemento valido, en caso de ser una tarea se muestra cuál tarea está siendo atendida y se busca la categoría a la que pertenece mediante el recorrido de la lista de categorías, esto se hace para reducir en 1, las tareas pendientes de esa categoría y luego se libera la memoria mediante free(). Finalmente se muestra cual tarea será la siguiente que debe realizar y finaliza la función.

---

## FUNCIONES DE APOYO:
### 1. Convertir Mayusculas:
Está función nos permite convertir los nombres de las categorías a mayusculas para poder comparar strings uniformemente, y además nos permite tener más bonitas las tablas de tareas por categoría.


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