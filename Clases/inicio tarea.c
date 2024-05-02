#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nodo{
    char rut[11];
    char nombre [25];
    int entradas;
    struct nodo *sig;
};

typedef struct nodo tNodoPerso;
typedef tNodoPerso *LISTA;

LISTA creaNodo(char rut[11], char nombre[25], int entradas)
{
    LISTA p;

    if (p == NULL)
    {
        printf("no hay memoria, adios");
        exit(-1);
    }

    p= malloc(sizeof(tNodoPerso));
    strcpy(p->rut, rut);
    strcpy(p->nombre, nombre);
    p->entradas = entradas;
    p->sig = NULL;

    return p;
}
void imprimeLista (LISTA L)
{
    LISTA aux;

    aux = L;
    while(aux != NULL)
    {
        printf("%s %s %i \n", aux->rut, aux->nombre, aux->entradas);
        aux = aux->sig;
    }
}

LISTA insertaFinal (LISTA L, char rut[11], char nombre[25], int entradas )
{
    LISTA aux;
    if(L == NULL)
    {
        L = creaNodo(rut, nombre, entradas);
    }
    else
    {
        aux = L;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = creaNodo(rut, nombre, entradas);
        aux = NULL;
    }
    return L;
}
LISTA actualiza(LISTA L, char rut[11], int nueva_edad)
{
    LISTA aux;

    aux = L;
    while (aux != NULL) {
        if (strcmp(aux->rut, rut) == 0) {
            aux->entradas = nueva_edad;
            printf("\nLa edad de la persona con RUT %s ha sido actualizada a %d.", rut, nueva_edad);
            return L;
        }
        aux = aux->sig;
    }
    printf("\nNo se encontró a ninguna persona con RUT %s en la lista.", rut);
    return L;
}

void procesoPrincipal()
{
     //1.pedir el nombre del archivo de entrada
     //2. abrir el archivo - validar
     //3. leer cada linea
     //4. dividir en el rut, nombre, entradas
     //5. insertar esa informacion en la lista

//void ListaDinamica()
//{
//    Lista L;
//    L = NULL;
//
//    imprimeLista(LeerArchivo());
//}

    LISTA L;

    L = NULL;
    L = creaNodo("21227314-7", "Almendra Manriquez", 2);
    L = insertaFinal(L, "21227314-7", "Almendra Manriquez", 2);
    L = insertaFinal(L, "20586214-5", "Bryan Salinas", 4);
    L = insertaFinal(L, "15724068-4", "Catherine Torres", 1);

    strcpy(rut, "21227314-7");
    L = actualiza(L, "21227314-7", 25);

   imprimeLista(L);
}


int main()
{
    procesoPrincipal();
    return 0;
}
