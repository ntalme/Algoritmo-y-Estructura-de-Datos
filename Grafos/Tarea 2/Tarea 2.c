#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define infinito 10000000

int **Grafo; //Matriz del grafo
int numNodos;
int numArcos;
char **Nombres; //Matriz con los nombres de las personas de la red.

bool *Visitados;
int *Costo;
int *Predecesor;
int *Camino;

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
//Busca un espacio en la ram donde quepa un arrelgo de tamñano numNodos y da la direccion
void creaArreglosParaDijkstra()
{
    Visitados = calloc(numNodos, sizeof(bool));
    Costo = calloc(numNodos, sizeof(int));
    Predecesor = calloc(numNodos, sizeof(int));
    Camino = calloc(numNodos, sizeof(int));
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

void ImprimeCaminos(int v0, int vf)
{
    int i, j, nodo;

    i = vf;
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
        for (; j>=0; j--)
            printf("\n%s", Nombres[Camino[j]]);
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
        //Primer paso
        if (Grafo[v0][i] == 0)  //No existe arco desde v0 al nodo "i" por lo que se guarda "infinito"
        {
            Costo[i] = infinito;
        }
        else
        {
            Costo[i] = Grafo[v0][i]; //Grafo[v0][i] equivale al costo
        }
        Predecesor[i] = v0;
    }
    while (NumeroNodosSinVisitar()>1)
    {
        w = NodoMinimoCostoSinVisitar(); //revisa los adyasentes sin visitar y de costo minimo
        Visitados[w] = true;
        for (i=0;i<numNodos;i++)
        {
            if (Grafo[w][i] != 0 && Visitados[i] == false)
            {
                if (Costo[w] + Grafo[w][i] < Costo[i]) //si el costo + el numero del arco es menor que al costo anterior lo cambia
                {
                    Predecesor[i] = w;
                    Costo[i] = Costo[w] + Grafo[w][i];
                }
            }
        }
    }
}

void Profundidad(int **Grafo, int numNodos, int nodo)
{
    int i;

    Visitados[nodo] = true;
    printf("%i ", nodo);
    for (i=0; i<numNodos; i++)
    {
        if (Grafo[nodo][i] != 0 && Visitados[i] == false)
        {
            Profundidad(Grafo, numNodos, i);
        }
    }
}

bool Conexo(int **Grafo, int numNodos)
{
    int i;
    Profundidad(Grafo, numNodos, 0);
    for (i=0; i<numNodos; i++)
    {
        if (Visitados[i] == false)
        {
            return true;
        }
    }
    return false;
}

bool ExisteCamino(int **Grafo, int numNodos, int nodoOrigen, int nodoDestino)
{
    bool visitados[numNodos];
    memset(visitados, false, sizeof(visitados));

    // Realizar una búsqueda en profundidad (DFS) desde el nodo origen
    Profundidad(Grafo, numNodos, nodoOrigen, visitados);

    // Verificar si el nodo destino fue visitado
    return visitados[nodoDestino];
}

void SecuenciaAmigos(char nomArchivo[30])
{
    char nombre1[30], nombre2[30];
    int n1, n2, i, j, k;

    if (numArcos != 0)
    {
        creaArreglosParaDijkstra();
        printf("\nIngresa tu nombre: ");
        fgets(nombre1, 30, stdin);
        strtok(nombre1, "\n");
        n1 = posicionDeNombre(nombre1);
        if (n1 == -1)
        {
            printf("El nombre ingresado no existe, el programa se cerrara.");
            exit(0);
        }

        printf("\nA quien quieres conocer?: ");
        fgets(nombre2, 30, stdin);
        strtok(nombre2, "\n");
        n2 = posicionDeNombre(nombre2);
        if (n2 == -1)
        {
            printf("El nombre ingresado no existe, el programa se cerrara.");
            exit(0);
        }

        DIJKSTRA(Grafo, numNodos, n1);
        if(Grafo[n1][n2] == 0 && Grafo[n2][n1] == 0)
        {
            if (Conexo(Grafo, numNodos) == true)
            {
                printf("\nLa secuencia de nombres es: ");
                ImprimeCaminos(n1,n2);
            }
            else
            {
                printf("Lo lamento, no hay red que conecte a esta persona para que la puedas conocer");
            }
        }
        else
        {
            printf("Ya son amigos :D");
        }
    }
    else
    {
        printf("No hay amistades");
    }
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
    char nombre1[30], nombre2[30];
    int v0, vf;

    //INGRESO EL NOMBRE DEL ARCHIVO A ABRIR
    printf("Ingresa nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");

    //USAMOS LA FUNCION LEEGRAFO PARA QUE LEA EL ARCHIVO
    leeGrafo(nomArchivo);

    SecuenciaAmigos(nomArchivo);

    if (numArcos != 0)
    {
        ArchivoAmigosComunes(nomArchivo);
    }
}

int main()
{
    inicioProceso();
    printf("\n\n");
    return 0;
}

