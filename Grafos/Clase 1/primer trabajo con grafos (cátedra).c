#include <stdio.h>
#include <stdlib.h>

//VARIABLES GLOBALES
int **Grafo; //Matriz del grafo
int numNodos, numArcos;

int **creaMatriz(int filas, int columnas)
{
   int **Matriz;
   int i;

   Matriz = calloc(filas, sizeof(int *)); //Calloc nos pone 0 donde no hay informacion

   for(i=0; i<filas; i++)
   {
      Matriz[i] = calloc(columnas, sizeof(int));
   }
   return Matriz;
}
void imprimeMatriz(int **Matriz, int n)
{
    int i, j;

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%i ", Matriz[i][j]);
        }
        printf("\n");
    }
}
/*CUARTO: Crea la fución "imprimeAdyacentes".
Esta función debe recibir como parámetro 1 nodo y debe imprimir los adyacentes que posea en el grafo.
Esta función NO tiene retorno.
*/
int imprimeAdyacentes(int nodo)
{
    int i;
    printf("\nLos antecesores de %i son: ", nodo);
    for(i=0; i<numNodos; i++)
    {
        if (Grafo[nodo][i]!=0)
        {
            printf("%i ", i);
        }
    }
}

/*PRIMERO:
Genera la función "leeGrafo" revisada en clases.
Esta funcion debe "retornar" la matriz del grafo, el número de nodos y el número de arcos.
*/
void leeGrafo()
{
    FILE *arch;
    int i, nodo1, nodo2, costo;
    char nomArchivo[30];

    printf("Ingresa el nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");

    arch = fopen(nomArchivo, "r");
    fscanf(arch, "%i", &numNodos);
    Grafo = creaMatriz(numNodos, numNodos);
    fscanf(arch, "%i", &numArcos);
    for(i=1; i<=numArcos; i++)
    {
       fscanf(arch, "%i", &nodo1);
       fscanf(arch, "%i", &nodo2);
       fscanf(arch, "%i", &costo);
       Grafo[nodo1][nodo2] = costo;
       Grafo[nodo2][nodo1] = costo;
    }
    fclose(arch);
}


int main()
{
    int nodo;

    //SEGUNDO: Llama a la función "leeGrafo"
    leeGrafo();

    //TERCERO: imprime la matriz del grafo usando la función "imprimeMatriz"
    imprimeMatriz(Grafo, numNodos);

    //QUINTO: Pídele aquí al usuario (en main) un nodo.
    //Verifica que el nodo que solicita el usuario sea un valor entre 0 y numNodos-1
    //Si el nodo es válido, llama a la función "imprimeAdyacentes"

    printf("Ingresa el nodo a buscar: ");
    scanf("%i", &nodo);

    if (nodo > 0 && nodo < numNodos)
    {
       imprimeAdyacentes(nodo);
    }
    else
    {
        printf("El nodo ingresado no es valido");
    }

    printf("\n\n");
    return 0;
}
