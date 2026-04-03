#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ================  STRUCTS  ================

typedef struct {
  char descripcion[100];
  char categoria[50];
  char hora[30];
} Tarea;

typedef struct {
  char nombre[50];
  size_t pendientes;
  List *listaTareas;
} Categoria;

// ================  STRUCTS  ================

// ================  FUNCIONES  ================


// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
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

  // INGRESAR NOMBRE CATEGORÍA
  char nombre[50];
  printf("Ingresa el nombre de la nueva categoría: ");
  scanf("%50s", nombre);
  toupper(nombre); // Transformar a mayusculas por estetica y funcionalidad al comparar.
  printf("\n");

  // VALIDAR SI EXISTE CATEGORÍA
  Categoria *categoriaActual = list_first(categorias);
  while (categoriaActual != NULL) {
    if (strcmp(nombre, categoriaActual->nombre) == 0) {
      printf("¡Ya existe la categoría %s!", categoriaActual->nombre);
      return;
    }
    categoriaActual = list_next(categorias);
  }

// SI PASA VERIFICACIÓN: SE CREA NUEVA CATEGORÍA
  Categoria *nuevaCategoria = (Categoria *)malloc(sizeof(Categoria));
  strcpy(nuevaCategoria->nombre, nombre);
  nuevaCategoria->pendientes = 0;
  nuevaCategoria->listaTareas = list_create();

// AGREGAR CATEGORÍA CREADA
  list_pushBack(categorias, nuevaCategoria);

  puts("¡Se ha creado la categoría con éxito!");
}

void mostrar_categorias(List *categorias) {
  // Mostrar categorías
  printf("Categorías:\n");
  // Aquí implementarías la lógica para mostrar las categorías
}

// ================  FUNCIONES  ================

// ================  MAIN  ================

int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías

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
      eliminar_categorias(categorias);
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

  // Liberar recursos, si es necesario
  list_clean(categorias);

  return 0;
}

// ================  MAIN  ================