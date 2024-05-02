
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERSONAS 100

typedef struct {
    char nombre[50];
    int entradas;
    int penalizado;
} Persona;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Debe proporcionar el nombre del archivo de entrada.\n");
        return 1;
    }

    FILE *archivo_entrada = fopen(argv[1], "r");
    if (archivo_entrada == NULL) {
        printf("No se pudo abrir el archivo de entrada.\n");
        return 1;
    }

    Persona personas[MAX_PERSONAS];
    int num_personas = 0;
    int entradas_disponibles = 50;

    // Leer los datos de todas las personas del archivo de entrada
    char linea[100];
    while (fgets(linea, 100, archivo_entrada)) {
        char *nombre = strtok(linea, ",");
        int num_entradas = atoi(strtok(NULL, ","));

        // Verificar si la persona ya existe en el arreglo de personas
        int indice_persona = -1;
        for (int i = 0; i < num_personas; i++) {
            if (strcmp(personas[i].nombre, nombre) == 0) {
                indice_persona = i;
                break;
            }
        }

        if (indice_persona == -1) {
            // La persona no existe en el arreglo de personas, crear una nueva
            strcpy(personas[num_personas].nombre, nombre);
            personas[num_personas].entradas = num_entradas;
            personas[num_personas].penalizado = 0;
            num_personas++;
        } else {
            // La persona ya existe en el arreglo de personas, actualizar su información
            personas[indice_persona].entradas += num_entradas;
        }
    }

    fclose(archivo_entrada);

    // Determinar quiénes recibirán las entradas
    FILE *archivo_ganadores = fopen("ganadores.txt", "w");
    FILE *archivo_lista_espera = fopen("lista_espera.txt", "w");

    for (int i = 0; i < num_personas; i++) {
        if (personas[i].entradas <= 2) {
            // La persona puede recibir todas las entradas que solicitó
            fprintf(archivo_ganadores, "%s,%d\n", personas[i].nombre, personas[i].entradas);
            entradas_disponibles -= personas[i].entradas;
        } else if (personas[i].entradas >= 3 && personas[i].entradas <= 5) {
            // La persona puede recibir solo 2 entradas y es penalizada
            fprintf(archivo_ganadores, "%s,2\n", personas[i].nombre);
            personas[i].penalizado = 1;
            entradas_disponibles -= 2;
        } else {
            // La persona no puede recibir entradas y no es considerada para la lista de espera
            personas[i].penalizado = 1;
        }
    }

    // Agregar a la lista de espera a las personas que no fueron penalizadas
    for (int i = 0; i < num_personas; i++) {
        if (personas[i].entradas > 2 && !personas[i].penalizado) {
            fprintf(archivo_lista_espera, "%s,%d\n", personas[i].nombre, personas[i].entr
