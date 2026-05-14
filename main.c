#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char  nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    float demanda[MAX_PRODUCTOS], tiempoUnidad[MAX_PRODUCTOS], recursosUnidad[MAX_PRODUCTOS];
    float tLimite, rLimite, tTotal = 0, rTotal = 0;
    int   opcion, nProductos = 0;

    printf("=== Sistema de Optimizacion de Fabrica ===\n");
    printf("Ingrese Limite de TIEMPO de la fabrica: ");
    scanf("%f", &tLimite);
    printf("Ingrese Limite de RECURSOS de la fabrica: ");
    scanf("%f", &rLimite);

    do {
        printf("\n1. Ingresar Producto\n");
        printf("2. Listar Productos\n");
        printf("3. Editar Producto\n");
        printf("4. Eliminar Producto\n");
        printf("5. Calcular Viabilidad\n");
        printf("6. Buscar Producto\n");
        printf("7. Analisis de Caso\n");
        printf("8. Salir\n");
        printf("Seleccione: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                ingresarDatos(nombres, demanda, tiempoUnidad, recursosUnidad, &nProductos);
                break;
            case 2:
                listarProductos(nombres, demanda, tiempoUnidad, recursosUnidad, nProductos);
                break;
            case 3:
                editarProducto(nombres, demanda, tiempoUnidad, recursosUnidad, nProductos);
                break;
            case 4:
                eliminarProducto(nombres, demanda, tiempoUnidad, recursosUnidad, &nProductos);
                break;
            case 5:
                calcularTotales(demanda, tiempoUnidad, recursosUnidad, &tTotal, &rTotal, nProductos);
                verificarViabilidad(tTotal, rTotal, tLimite, rLimite);
                break;
            case 6: {
                char busca[MAX_NOMBRE];
                printf("Nombre a buscar: ");
                scanf("%s", busca);
                int idx = buscarProducto(nombres, busca, nProductos);
                if(idx != -1) printf("Encontrado! Demanda: %.2f unidades\n", demanda[idx]);
                else printf("Producto no encontrado.\n");
                break;
            }
            case 7:
                analizarCaso(nombres, demanda, tiempoUnidad, recursosUnidad,
                             nProductos, tLimite, rLimite);
                break;
            case 8:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while(opcion != 8);

    return 0;
}