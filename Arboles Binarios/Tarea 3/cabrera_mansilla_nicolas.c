#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    char rut[12];
    char nombre[30];
    int entradas;
    struct nodo *izq;
    struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

void ImprimeElementosNivel(ABO A, int nivel)
{
    if (A == NULL)
        printf(" - ");
    else
    {
        if (nivel == 0)
            printf(" %s ", A->rut);
        else
        {
            ImprimeElementosNivel(A->izq, nivel-1);
            printf(" | ");
            ImprimeElementosNivel(A->der, nivel-1);
        }
    }
}

int Maximo(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}

int Altura(ABO A)
{
    if (A == NULL)
        return 0;
    else
        return Maximo(Altura(A->izq), Altura(A->der)) + 1;
}

void ImprimeArbol(ABO A)
{
    int h, i;

    h = Altura(A);

    printf("\n");
    for(i=0;i<h;i++)
    {
        ImprimeElementosNivel(A,i);
        printf("\n");
    }
}

ABO creaNodo(char rut[12], char nombre[30], int entradas)
{
   ABO aux;

   aux = malloc(sizeof(tNodo));
   if (aux != NULL)
   {
      strcpy(aux->rut, rut);
      strcpy(aux->nombre, nombre);
      aux->entradas = entradas;
      aux->izq = NULL;
      aux->der = NULL;
   }
   else
   {
       printf("\nNo hay memoria suficiente.");
       exit(1);
   }
   return aux;
}

ABO insertar(ABO T, char rut[12], char nombre[30], int entradas)
{

    if (T == NULL)
    {
        T = creaNodo(rut, nombre, entradas);
    }
    else
    {
        if (strcmp(rut, T->rut) == 0)
        {
            T->entradas = T->entradas + entradas;
        }
        else
       {
            if (strcmp(rut, T->rut) == -1) ///rut "es menor" que T->rut
            {
                T->izq = insertar(T->izq, rut, nombre, entradas);
            }
            else
            {
                T->der = insertar(T->der, rut, nombre, entradas);
            }
       }

    }
    return T;
}

void escribeEnArchivo(ABO arbol, char nArchivoEntrada[])
{
    FILE* archivoEntrada;
    FILE* archivoSalida;
    char linea[100];
    char nArchivoSal[30];
    char* rut;
    char* nombre;
    char* trozo;
    int entradas;
    int contadorPersonas = 0;

    archivoEntrada = fopen(nArchivoEntrada, "r");
    if (archivoEntrada == NULL)
    {
        printf("\nNo se ha encontrado el archivo. El programa se cerrará.");
        exit(-1);
    }

    strcpy(nArchivoSal, nArchivoEntrada);
    strtok(nArchivoSal, ".");
    strcat(nArchivoSal, ".sde");
    archivoSalida = fopen(nArchivoSal, "w");

    while (fgets(linea, 100, archivoEntrada) != 0)
    {
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        trozo = strtok(NULL, ",");
        entradas = atoi(trozo);

        arbol = insertar(arbol, rut, nombre, entradas);
    }

    fclose(archivoEntrada);

    if (arbol != NULL)
    {
        void escribeExcesoEntradas(ABO arbol, FILE* archivoSalida)
        {
            if (arbol != NULL)
            {
                escribeExcesoEntradas(arbol->izq, archivoSalida);

                if (arbol->entradas > 2)
                {
                    fprintf(archivoSalida, "%s, %s: %d\n", arbol->rut, arbol->nombre, arbol->entradas);
                    contadorPersonas++;
                }
                escribeExcesoEntradas(arbol->der, archivoSalida);
            }
        }

        escribeExcesoEntradas(arbol, archivoSalida);

        if (contadorPersonas > 0)
        {
            fprintf(archivoSalida, "\nTotal de personas: %d\n", contadorPersonas);
            printf("\nEl archivo %s fue generado.\n", nArchivoSal);
        }
        else
        {
            fclose(archivoSalida);
            remove(nArchivoSal);
            printf("\nTodos solicitaron la cantidad correcta de entradas.\n");
        }
    }
    else
    {
        fclose(archivoSalida);
        remove(nArchivoSal);
        printf("\nTodos solicitaron la cantidad correcta de entradas.\n");
    }
}

int main()
{
    ABO arbol = NULL;
    int numNodos = 3;
    char nArchivoEntrada[50];

    printf("Ingresa el nombre del archivo de entrada: ");
    fgets(nArchivoEntrada, 49, stdin);
    strtok(nArchivoEntrada, "\n");

    escribeEnArchivo(arbol, nArchivoEntrada);

    return 0;
}
