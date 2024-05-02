#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **Grafo; //Matriz del grafo
int numNodos;
int numArcos;
char **Nombres; //Matriz con los nombres de las personas de la red.

void creaMatrizGrafo()
{
   int i;

   Grafo = calloc(numNodos, sizeof(int *));

   for(i=0; i<numNodos; i++)
   {
      Grafo[i] = calloc(numNodos, sizeof(int));
   }
}
void creaMatrizNombres()
{
   int i;

   Nombres = calloc(numNodos, sizeof(char *));
   for(i=0; i<numNodos; i++)
   {
      Nombres[i] = calloc(30, sizeof(char));
   }
}
int posicionDeNombre(char nombre[30])
{
    int i;

    for (i=0; i<numNodos; i++)
    {
        if (strcmp(Nombres[i], nombre) == 0)
        {
            return i;
        }
    }
    return -1;
}
void imprimeGrafo()
{
    int i, j;

    printf("\nLa matriz del grafo es: \n\n");
    for (i=0; i<numNodos; i++)
    {
        for (j=0; j<numNodos; j++)
        {
            printf("%4i", Grafo[i][j]);
        }
        printf("\n");
    }
}
void imprimeNombres()
{
    int i, j;

    printf("\nLos nombres son: \n\n");
    for (i=0; i<numNodos; i++)
    {
        printf("%s (nodo %i)\n", Nombres[i], i);
    }
}
void leeGrafo(char nomArchivo[30])
{
    FILE *arch;
    int i, nodo1, nodo2;
    char linea[100];
    char *persona1, *persona2;

//SE ABRE EL ARCHIVO
    arch = fopen(nomArchivo, "r");
//SI EL ARCHIVO NO EXISTE
    if (arch == NULL)
    {
        printf("Archivo no encontrado");
        exit(-1);
    }
//EL PRIMER NUMERO CORRESPONDE A LA CANTIDAD DE NODOS
    fscanf(arch, "%i", &numNodos);

//SE CREA LA MATRIZ GRAFO Y LA MATRIZ NOMBRE DE TAMAÑO DE NUMNODOS
    creaMatrizGrafo();

    creaMatrizNombres();

//EL SEGUNDO NUMERO CORRESPONDE A LA CANTIDAD DE ARCOS
    fscanf(arch, "%i\n", &numArcos);

//LEE CADA NOMBRE Y LA ASIGNA UNA POSICION EN LA FILA I EN LA MATRIZ NOMBRES
    for (i=0; i<numNodos; i++)
    {
        //PRIMERO: COMPLETA AQUÍ LA LECTURA DE LOS NOMBRES DE CADA PERSONA
        //DESDE EL ARCHIVO, Y GUÁRDALOS EN "Nombres".
        //1. Leer la linea
        //2. Sacar el "\n"
        //3. Almacenar en la Matriz "Nombres" en la fila i

        fgets(linea, 100, arch);
        strtok(linea, "\n");
        strcpy(Nombres[i], linea);
    }
    for (i=0; i<numArcos; i++)
    {
        //SEGUNDO: HAZ LA LECTURA DE LAS RELACIONES ENTRE PERSONAS "AMIGAS",
        //Y ALMACENA EN EL GRAFO. USA LA FUNCIÓN "posicionDeNombre".
        //1. Leer la linea
        //2. Sacar el "\n"
        //3. Obtener el nombre de la primera persona
        //4. Obtener el nombre de la segunda persona
        //5. Obtener numero de nodo respectivo(usar "posicionDeNombre")
        //6. Colocar los dos 1 en la matriz "Grafo"

        fgets(linea, 100, arch);
        strtok(linea, "\n");
        //PERSONA 1
        persona1 = strtok(linea, ",");
        //PERSONA 2
        persona2 = strtok(NULL, ",");

        //CONOCEMOS A QUE NODO CORRESPONDE
        nodo1 = posicionDeNombre(persona1);
        nodo2 = posicionDeNombre(persona2);
        //DECIMOS QUE EXISTE UNA RELACION ENTRE AMBAS PERSONAS
        Grafo[nodo1][nodo2] = 1;
        Grafo[nodo2][nodo1] = 1;
    }
    fclose(arch);
}

int numAmigosEnComun(int nodo1, int nodo2)
{
    int cont;
    int i;

    cont = 0;
    for (i=0; i<numNodos; i++)
    {
        if (Grafo[nodo1][i] != 0 && Grafo[nodo2][i] != 0)
        {
            cont++;
        }
    }
    return cont;
}

void inicioProceso()
{
    char nomArchivo[30];
    int nodo1, nodo2, valor;

    printf("Ingresa nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");

    leeGrafo(nomArchivo);
    imprimeNombres();
    imprimeGrafo();

//    nodo1 = 0;
//    nodo2 = 2;
//    valor = numAmigosEnComun(nodo1, nodo2);
//
//    //TERCERO: Corrije el printf para mostrar el nombre del nodo1 y el nombre del nodo2.
//    printf("\nAmigos en comun entre %s y %s: %i", Nombres[nodo1], Nombres[nodo2], valor);

}
int main()
{
    inicioProceso();
    printf("\n\n");
    return 0;
}
