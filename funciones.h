#ifndef LOGICA_H
#define LOGICA_H

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE    30

void ingresarDatos(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                   float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                   int *nProductos);

void listarProductos(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                     float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                     int nProductos);

void editarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                    float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                    int nProductos);

void eliminarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                      float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                      int *nProductos);

void calcularTotales(float demanda[MAX_PRODUCTOS], float tiempoUnidad[MAX_PRODUCTOS],
                     float recursosUnidad[MAX_PRODUCTOS], float *tTotal, float *rTotal,
                     int nProductos);

int  buscarProducto(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], char objetivo[MAX_NOMBRE],
                    int nProductos);

void verificarViabilidad(float tTotal, float rTotal, float tLimite, float rLimite);

void analizarCaso(char nombres[MAX_PRODUCTOS][MAX_NOMBRE], float demanda[MAX_PRODUCTOS],
                  float tiempoUnidad[MAX_PRODUCTOS], float recursosUnidad[MAX_PRODUCTOS],
                  int nProductos, float tLimite, float rLimite);

#endif