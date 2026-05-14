#include <stdio.h>
#include <string.h>
#include "funciones.h"

void ingresarDatos(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                   float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                   int *nProductos) {
    if (*nProductos >= MAX_PRODUCTOS) {
        printf("Limite de productos alcanzado.\n");
        return;
    }
    int i = *nProductos;
    printf("\n--- Producto %d ---\n", i + 1);
    printf("Nombre: ");
    scanf("%s", nombres[i]);
    printf("Demanda (unidades): ");
    scanf("%f", &demanda[i]);
    printf("Tiempo por unidad (horas): ");
    scanf("%f", &tiempoUnidad[i]);
    printf("Recursos por unidad: ");
    scanf("%f", &recursosUnidad[i]);
    (*nProductos)++;
}

void listarProductos(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                     float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                     int nProductos) {
    if (nProductos == 0) {
        printf("No hay productos registrados.\n");
        return;
    }
    for (int i = 0; i < nProductos; i++) {
        printf("\nProducto %d: %s\n", i + 1, nombres[i]);
        printf("  Demanda: %.2f | Tiempo/u: %.2f | Recursos/u: %.2f\n",
               demanda[i], tiempoUnidad[i], recursosUnidad[i]);
    }
}

void editarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                    float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                    int nProductos) {
    if (nProductos == 0) {
        printf("No hay productos para editar.\n");
        return;
    }
    char buscar[MAX_NOMBRE];
    printf("Nombre a editar: ");
    scanf("%s", buscar);
    int idx = buscarProducto(nombres, buscar, nProductos);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    printf("Nuevo nombre: ");      scanf("%s",  nombres[idx]);
    printf("Nueva demanda: ");     scanf("%f", &demanda[idx]);
    printf("Nuevo tiempo/u: ");    scanf("%f", &tiempoUnidad[idx]);
    printf("Nuevos recursos/u: "); scanf("%f", &recursosUnidad[idx]);
    printf("Producto editado correctamente.\n");
}

void eliminarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                      float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                      int *nProductos) {
    if (*nProductos == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }
    char buscar[MAX_NOMBRE];
    printf("Nombre a eliminar: ");
    scanf("%s", buscar);
    int idx = buscarProducto(nombres, buscar, *nProductos);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }
    for (int j = idx; j < *nProductos - 1; j++) {
        strcpy(nombres[j], nombres[j + 1]);
        demanda[j]        = demanda[j + 1];
        tiempoUnidad[j]   = tiempoUnidad[j + 1];
        recursosUnidad[j] = recursosUnidad[j + 1];
    }
    (*nProductos)--;
    printf("Producto eliminado correctamente.\n");
}

void calcularTotales(float demanda[MAX_PRODUCTOS], float tiempoUnidad[MAX_PRODUCTOS],
                     float recursosUnidad[MAX_PRODUCTOS], float *tTotal, float *rTotal,
                     int nProductos) {
    *tTotal = 0;
    *rTotal = 0;
    for (int i = 0; i < nProductos; i++) {
        *tTotal += demanda[i] * tiempoUnidad[i];
        *rTotal += demanda[i] * recursosUnidad[i];
    }
}

int buscarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char objetivo[MAX_NOMBRE],
                   int nProductos) {
    for (int i = 0; i < nProductos; i++) {
        if (strcmp(nombres[i], objetivo) == 0)
            return i;
    }
    return -1;
}

void verificarViabilidad(float tTotal, float rTotal, float tLimite, float rLimite) {
    printf("\n--- RESULTADO DE VIABILIDAD ---\n");
    printf("Tiempo requerido : %.2f / Limite: %.2f\n", tTotal, tLimite);
    printf("Recursos requeridos: %.2f / Limite: %.2f\n", rTotal, rLimite);
    if (tTotal <= tLimite && rTotal <= rLimite) {
        printf("ESTADO: PRODUCCION VIABLE\n");
    } else {
        printf("ESTADO: PRODUCCION NO VIABLE\n");
        if (tTotal > tLimite)
            printf("  Faltan %.2f horas\n", tTotal - tLimite);
        if (rTotal > rLimite)
            printf("  Faltan %.2f recursos\n", rTotal - rLimite);
    }
}

void analizarCaso(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                  float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                  int nProductos, float tLimite, float rLimite) {
    if (nProductos == 0) {
        printf("No hay productos para analizar.\n");
        return;
    }
    float tTotal = 0, rTotal = 0;
    calcularTotales(demanda, tiempoUnidad, recursosUnidad, &tTotal, &rTotal, nProductos);

    printf("\n--- ANALISIS DE CASO ---\n");
    for (int i = 0; i < nProductos; i++) {
        float tProd = demanda[i] * tiempoUnidad[i];
        float rProd = demanda[i] * recursosUnidad[i];
        printf("\n%s:\n", nombres[i]);
        printf("  Tiempo requerido  : %.2f", tProd);
        printf("%s\n", (tProd > tLimite) ? " * EXCEDE limite de tiempo" : "");
        printf("  Recursos requeridos: %.2f", rProd);
        printf("%s\n", (rProd > rLimite) ? " * EXCEDE limite de recursos" : "");
    }
    printf("\nTotales -> Tiempo: %.2f / %.2f | Recursos: %.2f / %.2f\n",
           tTotal, tLimite, rTotal, rLimite);
    if (tTotal <= tLimite && rTotal <= rLimite)
        printf("La fabrica SI puede cumplir con la demanda.\n");
    else
        printf("La fabrica NO puede cumplir con la demanda.\n");
}