#include "tdas/list.h"
#include "tdas/queue.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* ================ REPO DE GIT ==============

Estudiante: Iván Octavio García Briones
Carrera: Ingeniería Civíl en Informática

Repositorio Tarea 1: https://github.com/garciaivan11/Tarea1
Uso de IA: 

=================== REPO DE GIT ============== */ 

// ================  STRUCTS  ================

typedef struct {
  char descripcion[100];
  char categoria[50];
  char hora[30];
} Tarea;

typedef struct {
  char nombre[50];
  size_t pendientes;
} Categoria;

// ================  STRUCTS  ================

// ================  FUNCIONES  ================


// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión de Tareas");
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

void convertirMayusculas(char *nombre) {
  for (int i = 0; nombre[i] != '\0'; i++) {
    nombre[i] = toupper((unsigned char)nombre[i]);
  }
}

void registrar_categorias(List *categorias) {
  printf("==== REGISTRAR NUEVA CATEGORÍA ====\n");

  // INGRESAR NOMBRE CATEGORÍA
  char nombre[50];
  printf("Ingresa el nombre de la nueva categoría: ");
  scanf(" %49[^\n]", nombre);
  convertirMayusculas(nombre); // Transformar a mayusculas por estetica y funcionalidad al comparar.
  printf("\n");

  // VALIDAR SI EXISTE CATEGORÍA
  Categoria *categoriaActual = list_first(categorias);
  while (categoriaActual != NULL) {
    if (strcmp(nombre, categoriaActual->nombre) == 0) {
      printf("¡Ya existe la categoría %s!\n", categoriaActual->nombre);
      return;
    }
    categoriaActual = list_next(categorias);
  }

// SI PASA VERIFICACIÓN: SE CREA NUEVA CATEGORÍA
  Categoria *nuevaCategoria = (Categoria *)malloc(sizeof(Categoria));
  if (nuevaCategoria == NULL) {
    printf("Error: No se pudo asignar memoria.\n");
    exit(EXIT_FAILURE);
  }
  strcpy(nuevaCategoria->nombre, nombre);
  nuevaCategoria->pendientes = 0;

// AGREGAR CATEGORÍA CREADA
  list_pushBack(categorias, nuevaCategoria);

  printf("¡Se ha creado la categoría %s con éxito!", nombre);
  return;
}

void eliminar_categorias(List *categorias, Queue *tareasGenerales) {
  printf("==== ELIMINAR CATEGORÍA ====\n");

  // INGRESAR NOMBRE CATEGORÍA
  char nombre[50];
  size_t tareasCategoria;
  printf("Ingresa el nombre de la categoría que quieres eliminar: ");
  scanf(" %49[^\n]", nombre);
  convertirMayusculas(nombre);
  printf("\n");

// VALIDAR QUE EXISTA Y ELIMINARLO
  unsigned short existe = 0; // Para marcar si se encontró alguna categoría

// ELIMINAR CATEGORÍA
  Categoria *categoriaActual = list_first(categorias);
  while (categoriaActual != NULL) {
    if (strcmp(nombre, categoriaActual->nombre) == 0) {
      tareasCategoria = categoriaActual->pendientes;
      list_popCurrent(categorias);
      free(categoriaActual);
      existe = 1;
      break;
    }
    categoriaActual = list_next(categorias);
  }

// ELIMINAR TAREAS CON LA CATEGORÍA
  if (existe == 0) printf("¡La categoría que deseas eliminar no se encuentra registrada!"); // Si existe == 0, es por que no se encontró una categoría con el nombre proporcionado por el usuario.
  else { // Si existe == 1, se encontró la categoría y se eliminó, ahora hay que eliminar las tareas que pertenezcan a esa categoría.
    Tarea *tareaActual;
    Queue *colaAux = queue_create(NULL); // Para traspasar las tareas que no sean de la categoría a eliminar.

    while (queue_front(tareasGenerales) != NULL) { // Eliminar tareas de la categoría escogida y traspasarla al aux.
      tareaActual = (Tarea *) queue_remove(tareasGenerales); // Se saca de la cola original el primer dato.
      if (strcmp(tareaActual->categoria, nombre) != 0) queue_insert(colaAux, tareaActual); // Se verifica si pertenece a la categoría escogida, si no pertenece se guarda en la cola aux.
      else free(tareaActual); // Y si pertenece a la categoría se libera la memoria de esa tarea, eliminadola para siempre.
    }

    while (queue_front(colaAux) != NULL) {  // Se traspasan los datos de la colaAux a la original, para guardar la lista nuevamente pero sin las tareas pertenecientes a la categoría seleccionada.
      queue_insert(tareasGenerales, queue_remove(colaAux));
    }

    free(colaAux); // Se liberá la memoria de colaAux.
    printf("¡La categoría %s se ha eliminado, contaba con %zu tareas!", nombre, tareasCategoria);
  }
  return;
}

void mostrar_categorias(List *categorias) {
  // Mostrar categorías
  printf("==== LISTADO DE CATEGORÍAS ===\n\n");
  
  Categoria *categoriaActual = list_first(categorias);
  size_t i = 0;

  printf("+---------------------------+-----------------------+\n");
  printf("| CATEGORÍA                 | TAREAS PENDIENTES     |\n");
  printf("+---------------------------+-----------------------+\n");
  // Se recorre la lista de categorías printeando cada una de las categorías con un formato visual especial, mediante un formateo de texto.
  while (categoriaActual != NULL) {
    i ++;
    printf("| %-25s |          %4zu         |\n", categoriaActual->nombre, categoriaActual->pendientes);
    categoriaActual = list_next(categorias);
  }
  printf("+---------------------------+-----------------------+\n");

  if (i == 0) printf("No se han registrado categorías aún.\n");
  else printf("\nTotal: %zu categorías encontradas.\n", i);
  return;
}

void registrar_pendiente(Queue *tareasGenerales, List *categorias) {
  printf("==== REGISTRAR NUEVA TAREA ====\n");

  // Solicitar nombre de categoría
  printf("Ingresa la categoría a la que pertenecerá está tarea (Si no existe se creará): ");
  char categoria[50];
  scanf(" %49[^\n]", categoria);
  printf("\n");
  convertirMayusculas(categoria);

  // Verificar si existe la categoría mencionada
  unsigned short existe  = 0;

  Categoria *categoriaActual = list_first(categorias);
  while (categoriaActual != NULL) {
    if (strcmp(categoria, categoriaActual->nombre) == 0) {
      existe = 1;
      break;
    }
    categoriaActual = list_next(categorias);
  }

  // Si no existe se crea la categoría
  if (existe == 0) {
    Categoria *nuevaCategoria = (Categoria *)malloc(sizeof(Categoria));
    if (nuevaCategoria == NULL) exit(EXIT_FAILURE);
    strcpy(nuevaCategoria->nombre, categoria);
    nuevaCategoria->pendientes = 0;
    list_pushBack(categorias, nuevaCategoria);
    categoriaActual = nuevaCategoria;
    printf("Se ha creado la nueva categoría: %s. \n", categoria);
  }

  // Se Solicitan los datos para colocar en la nueva tarea
  char descripcion[100];
  char hora[30];
  printf("Ingresa la descripción de tu tarea (máx 99 car.): ");
  scanf(" %99[^\n]", descripcion);
  printf("\n");

  // Registro del día y hora en el que se creó la tarea
  time_t t = time(NULL);                                   // Se recopila cuantos segundos han pasado desde el 1 de enero de 1970 (Número gigante que entiende <time.h>)
  struct tm *tm_info = localtime(&t);                      // Transforma esa cantidad de segundos en varios campos (Año, mes, dia, hora)
  char bufferTiempo[30];                                   // Creamos la variable donde se guardaran los datos horarios
  strftime(bufferTiempo, 30, "%d/%m/%Y %H:%M", tm_info);   // Formateo de texto que extrae los datos y los guarda en la variable que utilizamos

  // Se crea la tarea y se le adjuntan los datos recopilados
  Tarea *nuevaTarea = (Tarea *)malloc(sizeof(Tarea));
  if (nuevaTarea == NULL) exit(EXIT_FAILURE);

  strcpy(nuevaTarea->descripcion, descripcion);
  strcpy(nuevaTarea->categoria, categoria);
  strcpy(nuevaTarea->hora, bufferTiempo);

  // Se inserta la nueva tarea a la cola y se aumentan los pendientes de la categoría correspondiente
  queue_insert(tareasGenerales, nuevaTarea);
  categoriaActual->pendientes ++;

  printf("\n¡Tarea registrada con éxito en la categoría %s, a las %s!\n", categoria, bufferTiempo);
}

void atender_pendiente(Queue *tareasGenerales, List *categorias) {
  Tarea *tareaActual = queue_remove(tareasGenerales); // Sacamos el primer elemento de la cola y guardamos sus datos
  if (tareaActual == NULL) {  // Verificamos que el elemento que sacamos exista, si no quedaban tareas en la cola se muestra un mensaje
    printf("¡Libre de pendientes!\n");
    return; 
  }
  // Con el return salimos de la función y evitamos poner un else para el caso 2: Si existe tarea.
  printf("Atendiendo: %s | Categoría: %s | Momento del registro: %s\n", tareaActual->descripcion, tareaActual->categoria, tareaActual->hora); // Mostramos la tarea

  // Recorremos la lista de categorías para buscar la categoría a la que pertenecía la tarea y disminuimos en 1 los pendientes que le quedan a esa categoría
  Categoria *categoriaActual = list_first(categorias);
  while (categoriaActual != NULL) {
    if (strcmp(categoriaActual->nombre, tareaActual->categoria) == 0) {
      categoriaActual->pendientes -= 1;
      break;
    }
    categoriaActual = list_next(categorias);
  }

  free(tareaActual); // Se vacía la memoria utilizada para la tarea

  // Por estitica mostraremos la siguiente tarea para que el usuario sea conciente de cual tendrá despues de completar la actual
  tareaActual = queue_front(tareasGenerales);
  if (tareaActual != NULL) {
    printf("Próxima Tarea: Descripción: %s | Categoría: %s | Momento del registro: %s\n", tareaActual->descripcion, tareaActual->categoria, tareaActual->hora);
  }
  else {
    printf("¡No te quedan tareas pendientes por completar!\n");
  }
  return;
}

void mostrar_pendientes(Queue *tareasGenerales) {
  printf("=== LISTADO DE TAREAS ===\n\n");

  // Usamos queue_front para posicionar el puntero al inicio de la cola sin extraer elementos.
  Tarea *tareaActual = queue_front(tareasGenerales);

  // Se válida que existan tareas minimamente.
  if (tareaActual == NULL) {
    printf("No se han registrado tareas aún.\n");
    return;
  }

  size_t i = 0;

  // Encabezado con formato de tabla para mejorar la estetica del programa.
  printf("+------+------------------------+--------------------+------------------+\n");
  printf("|  ID  | DESCRIPCIÓN            | CATEGORÍA          | FECHA/HORA       |\n");
  printf("+------+------------------------+--------------------+------------------+\n");

  // Recorremos la cola desde principio a fin mostrando en cada iteración las tareas que se han registrado, usando queue_next
  while (tareaActual != NULL) {
    i ++;
    // Se utiliza un formato especial para mostrar las tareas, usando el espacio exacto del encabezado para mantener la estetica.
    printf("|  %zu  | %-22s | %-18s | %-16s |\n", i, tareaActual->descripcion, tareaActual->categoria, tareaActual->hora);
    // Avanzamos al siguiente nodo.
    tareaActual = queue_next(tareasGenerales);
  }
  printf("+------+------------------------+--------------------+------------------+\n");
  printf("\nTe falta un total de %zu tarea(s).\n", i);
  return;
}

void filtrar_por_categoria(Queue *tareasGenerales, List *categorias) {
  printf("==== FILTRADO POR CATEGORÍA ====\n\n");

  // Validar si hay tareas antes de pedir la categoría
  Tarea *tareaActual = queue_front(tareasGenerales);
  if (tareaActual == NULL) {
    printf("No hay tareas registradas en el sistema.\n");
    return;
  }

  // Solicitamos la categoría para filtrar
  char filtro[50];
  printf("Ingresa el nombre de la categoría que deseas filtrar: ");
  scanf(" %49[^\n]", filtro);
  convertirMayusculas(filtro); // Se convierte a mayusculas para comparar con las existentes de forma eficiente

  // Buscamos la categoría en la lista de categorías para ver si existe y si tiene tareas adjuntas
  Categoria *categoriaActual = list_first(categorias);
  while (categoriaActual != NULL) {
    if (strcmp(categoriaActual->nombre, filtro) == 0) break; // Paramos en la categoría cuando la encuentre
    categoriaActual = list_next(categorias);
  }

  // Si no existe o no tiene tareas se retorna para evitar más procesamiento
  if (categoriaActual == NULL) {
    printf("La categoría '%s' no existe.\n", filtro);
    return;
  }

  if (categoriaActual->pendientes == 0) {
    printf("La categoría '%s' no tiene tareas pendientes.\n", filtro);
    return;
  }


  // Si llegamos acá es por que si se encontró la categoría y contiene tareas válidas.
  printf("\nTienes %zu encontradas de la categoría: %s\n", categoriaActual->pendientes, filtro);
  printf("+------+--------------------------------+------------------+\n");
  printf("|  ID  | DESCRIPCIÓN                    | FECHA/HORA       |\n");
  printf("+------+--------------------------------+------------------+\n");

  // Recorremos la lista de tareas general para filtrar
  size_t i = 0;

  while (tareaActual != NULL) {
    if (strcmp(tareaActual->categoria, filtro) == 0) {
      i++;
      printf("|  %2zu  | %-30s | %-16s |\n", i, tareaActual->descripcion, tareaActual->hora);
    }
    tareaActual = queue_next(tareasGenerales);
  }
  printf("+------+--------------------------------+------------------+\n");
  return;
}

// ================  FUNCIONES  ================

// ================  MAIN  ================

int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías
  Queue *tareasGenerales = queue_create(NULL); // Cola para ir almacenando las tareas del usuario

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_categorias(categorias);
      break;
    case '2':
      eliminar_categorias(categorias, tareasGenerales);
      break;
    case '3':
      mostrar_categorias(categorias);
      break;
    case '4':
      registrar_pendiente(tareasGenerales, categorias);
      break;
    case '5':
      atender_pendiente(tareasGenerales, categorias);
      break;
    case '6':
      mostrar_pendientes(tareasGenerales);
      break;
    case '7':
      filtrar_por_categoria(tareasGenerales, categorias);
      break;
    case '8':
      puts("Saliendo del sistema Smart TODO");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  // Liberar recursos, si es necesario
  list_clean(categorias);
  queue_clean(tareasGenerales);
  free(categorias);
  free(tareasGenerales);
  return 0;
}

// ================  MAIN  ================