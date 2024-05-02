#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define infinito 10000000

int **Grafo;
int numNodos;
int numArcos;

bool *Visitados;
int *Costo;
int *Predecesor;

int *Camino;
int Pos;

void creaMatrizGrafo()
{
    int i, j;

    Grafo = calloc(numNodos, sizeof(int *));
    for (i=0; i<numNodos; i++)
    {
        Grafo[i] = calloc(numNodos, sizeof(int));
    }
}
void creaArreglosParaDijkstra()
{
    Visitados = calloc(numNodos, sizeof(bool));
    Costo = calloc(numNodos, sizeof(int));
    Predecesor = calloc(numNodos, sizeof(int));
    Camino = calloc(numNodos, sizeof(int));
}
void LeeGrafo(char nomArchivo[20])
{
    FILE *pArchivo;
    int i, j, tipo, nodo1, nodo2, costo;

    pArchivo = fopen(nomArchivo, "r");
    if (pArchivo == NULL)
    {
        printf("\nERROR: Archivo no encontrado.\nEste programa se cerrar%c.\n\n", 160);
        exit(-1);
    }
    fscanf(pArchivo, "%i", &numNodos);
    fscanf(pArchivo, "%i", &numArcos);
    fscanf(pArchivo, "%i", &tipo);//si tipo = 1 "DIRIGIDO", si tipo = 2 "NO DIRIGIDO"
    creaMatrizGrafo();
    for (i=0; i<numArcos; i++)
    {
        fscanf(pArchivo, "%i", &nodo1);
        fscanf(pArchivo, "%i", &nodo2);
        fscanf(pArchivo, "%i", &costo);
        Grafo[nodo1][nodo2] = costo;
        if (tipo == 2)
        {
            Grafo[nodo2][nodo1] = costo;
        }
    }
}
void ImprimeCaminos(int v0)
{
    int i, j, nodo;

    for(i=0; i<numNodos; i++)    //En este ciclose construye el camino a cada nodo i desde v0.
    {
        if (i != v0)
        {
            Camino[0] = i;
            nodo = Predecesor[i];

            for (j=1; nodo!=v0; j++)
            {
                Camino[j] = nodo;
                nodo = Predecesor[nodo];
            }
            Camino[j] = nodo;

            printf("\n %2i -> %2i (costo %2i):", v0, i, Costo[i]);
            for (; j>=0; j--) //No va el j=0 en este for, porque se necesita iniciar j en el valor que viene del for de arriba (línea 74)
            {
                printf("%3i", Camino[j]);
            }

        }
    }
}
int NumeroNodosSinVisitar()
{
    int i, cont;

    cont = 0;
    for (i=0; i<numNodos; i++)
    {
        if (Visitados[i] == false){
            cont++;
        }
    }
   return cont;
}
int NodoMinimoCostoSinVisitar()
{
    int i, nodo, minimo;
    bool esElPrimero;

    esElPrimero = true;
    for (i=0; i<numNodos; i++)
    {
        if (Visitados[i] == false)
        {
            if (esElPrimero)
            {
                minimo = Costo[i];
                nodo = i;
                esElPrimero = false;
            }
            else
            {
                if (Costo[i] < minimo)
                {
                    minimo = Costo[i];
                    nodo = i;
                }
            }
        }
    }
    return nodo;
}
void DIJKSTRA(int **Grafo, int numNodos, int v0)
{
    int i, j, w=v0;

    Visitados[v0] = true;
    for (i=0; i<numNodos; i++)
    {
        if (Grafo[v0][i] == 0)  //No existe arco desde v0 al nodo "i" por lo que se guarda "infinito"
        {
            Costo[i] = infinito;
        }
        else
        {
            Costo[i] = Grafo[v0][i];
        }
        Predecesor[i] = v0;
    }
    while (NumeroNodosSinVisitar()>1)
    {
        w = NodoMinimoCostoSinVisitar();
        Visitados[w] = true;
        for (j=0;j<numNodos;j++)
        {
            if (Grafo[w][j] != 0 && Visitados[j] == false)
            {
                if (Costo[w] + Grafo[w][j] < Costo[j])
                {
                    Predecesor[j] = w;
                    Costo[j] = Costo[w] + Grafo[w][j];
                }
            }
        }
    }
}
void iniciaProceso()
{
    char nomArchivo[30];
    int v0;

    printf("\nIngrese nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");
    LeeGrafo(nomArchivo);
    creaArreglosParaDijkstra();
    printf("\nIngrese nodo inicial para buscar los caminos en el grafo (entre 0 y %i): ", numNodos-1);
    scanf("%i", &v0);
    DIJKSTRA(Grafo, numNodos, v0);
    printf("\nLos caminos son: ");
    ImprimeCaminos(v0);
}
int main()
{
    iniciaProceso();
    printf("\n\n");
    return 0;
}
