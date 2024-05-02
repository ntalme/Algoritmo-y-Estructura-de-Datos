#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFINIMOS LA ESTRUCTURA
struct perro
{
    char nombre [30];
    int edad;
    struct perro *sig;

};
//CAMBIAR NOMBRE DE LA ESTRUCTURA
typedef struct perro tPerro;

//CAMBIAR NOMBRE DEL PUNTERO tPERRO
typedef tPerro * Lista;

void ImprimeLista(Lista p)
{
    Lista aux;

    aux = p; //con esto hacemos que aux apunte a la primera lista/caja

    //PARA RECORRER TODAS LAS CAJA/LISTA
    while (aux != NULL)
    {
        printf("%s (%i)\n", aux->nombre, aux->edad);

        aux = aux->sig;

    }
}

int main()
{
    //PUNTERO QUE APUNTE A TODA LA LISTA
  //tPerro *p; -En la linea 17 cambiamos tPerro por Lista
    Lista p;

    //SIEMPRE DEFINIR AL PRINCIPIO EL PUNTERO COMO NULL
    p = NULL;

    //BUSCAR UN ESPACIO DONDE QUEPA TPERRO
    p = malloc(sizeof(tPerro));

    //POR SI P NO ENCUENTRA MEMORIA EN LA RAM
    if (p == NULL)
    {
        printf("No hay memoria. Chaito");
        exit(-1); //Esto sirve para poder salir
    }
//----------------------------------------------------------------------------------------------------

    //AÑADIMOS LOS VALORES 2
    strcpy(p->nombre, "Irene Zuccar"); //Para poder poner un string en la estructura
    p->edad = 17;
    p->sig = NULL; //El campo sig siempre debe tener el valor NULL

    //PONDREMOS NUEVOS VALORES
    //Para unirlos con la primera lista debemos poner que p va hacia la casilla sig (p->sig)
    p->sig = malloc(sizeof(tPerro));

    if (p->sig == NULL)
    {
        printf("No hay memoria. Chaito");
        exit(-1); //Esto sirve para poder salir
    }

    //LE DAMOS VALORES
    strcpy(p->sig->nombre, "Ricky Martin"); //Para poder poner un string en la estructura
    p->sig->edad = 19;
    p->sig->sig = NULL;
    //NOTA: si se pone p->edad se cambiara la edad de la primera lista por lo que debemos poner p->sig->edad

//----------------------------------------------------------------------------------------------------

    //AÑADIMOS VALORES 3
    p->sig->sig = malloc(sizeof(tPerro));

    if (p->sig->sig == NULL)
    {
        printf("No hay memoria. Chaito");
        exit(-1); //Esto sirve para poder salir
    }

    //LE DAMOS VALORES
    strcpy(p->sig->sig->nombre, "Pedro Pascal"); //Para poder poner un string en la estructura
    p->sig->sig->edad = 18;
    p->sig->sig->sig = NULL;

    ImprimeLista(p);

    return 0;
}
