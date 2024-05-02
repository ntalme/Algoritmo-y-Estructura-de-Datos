#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **Grafo; //Matriz del grafo
int numNodos;
int numArcos;
char **Nombres; //Matriz con los nombres de las personas de la red.

//CREA LA MATRIZ
void creaMatrizGrafo()
{
   int i;

   Grafo = calloc(numNodos, sizeof(int *));

   for(i=0; i<numNodos; i++)
   {
      Grafo[i] = calloc(numNodos, sizeof(int));
   }
}
//CREA LA MATRIZ DE LOS NOMBRES
void creaMatrizNombres()
{
   int i;

   Nombres = calloc(numNodos, sizeof(char *));
   for(i=0; i<numNodos; i++)
   {
      Nombres[i] = calloc(30, sizeof(char));
   }
}
//BUSCA EN QUE NODO ESTA EL NOMBRE
int posicionDeNombre(char nombre[30])
{
    int i;

    for (i=0; i<numNodos; i++)
    {
        if (strcmp(Nombres[i], nombre) == 0) //Nombres[0]=Cesar es igual a Pablo?- NO, por lo que i=1- Nombres[1]=Pablo es igual a Pablo?- Si por lo que el nombre pablo corresponde a la posicion 1
        {
            return i;
        }
    }
    return -1;
}
//IMPRIME EL GRAFO DE LOS NOMBRES CONVERTIDOS A NUMEROSr
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
//IMPRIME EL NOMBRE Y QUE NODO LE CORRESPONDE
void imprimeNombres()
{
    int i, j;

    printf("\nLos nombres son: \n\n");
    for (i=0; i<numNodos; i++)
    {
        printf("%s (nodo %i)\n", Nombres[i], i); //Nombres[i] corresponde al nombre que seg guardo en esa posicion, e i significa el nodo q le corresponde
        //Ejmplo: Cuando i=2, Nombres[2]=Felipe por lo que se imprime que Felipe(Nodo 2)
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
        fgets(linea, 100, arch);
        strtok(linea, "\n");
        strcpy(Nombres[i], linea); //NOMBRE[0] = CESAR
    }
//LEE LAS RELACIONES
    for (i=0; i<numArcos; i++)
    {
        fgets(linea, 100, arch);
        strtok(linea, "\n");
        //PERSONA 1
        persona1 = strtok(linea, ",");
        //PERSONA 2
        persona2 = strtok(NULL, ",");

        //DECIMOS QUE LA POSICION DEL NOMBRE CORRESPONDE A UN NODO
        nodo1 = posicionDeNombre(persona1); //Cesar corresponde a la posicion 0
        nodo2 = posicionDeNombre(persona2); //Pablo corresponde a la posicion 1

        //DECIMOS QUE EXISTE UNA RELACION ENTRE AMBAS PERSONAS
        Grafo[nodo1][nodo2] = 1; //por lo que decimos que entre el nodo 0 y el nodo 1 existe un arco o relacion
        Grafo[nodo2][nodo1] = 1;
    }
    fclose(arch);
}

void ArchivoAmigosComunes (char nomArchivo[30])
{
    char * AmigosenComun;
    FILE * archivo;
    int i, j, k, contador;

    archivo = fopen(nomArchivo, "r");
    AmigosenComun = strtok(nomArchivo, ".");
    strcat(AmigosenComun, ".aec");

    archivo = fopen(AmigosenComun, "w");

    for (i=0; i<numNodos; i++)
    {
        for(j=i+1; j<numNodos; j++)
        {
            contador = 0;
            for (k=0; k<numNodos; k++)
            {
                if (Grafo[i][k] != 0 && Grafo[j][k] != 0)
                {
                    contador++;
                }
            }
            fprintf(archivo, "%s, %s: %i\n", Nombres[i], Nombres[j], contador);
        }
    }
    fclose(archivo);
}

void inicioProceso()
{
    char nomArchivo[30];
    int nodo1, nodo2, valor;

    //INGRESO EL NOMBRE DEL ARCHIVO A ABRIR
    printf("Ingresa nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");

    //USAMOS LA FUNCION LEEGRAFO PARA QUE LEA EL ARCHIVO
    leeGrafo(nomArchivo);
    imprimeNombres();
    imprimeGrafo();

    ArchivoAmigosComunes(nomArchivo);
}

int main()
{
    inicioProceso();
    printf("\n\n");
    return 0;
}

