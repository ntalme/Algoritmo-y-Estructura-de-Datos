#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Entrada:
Salida:
Proceso:
*/
struct personas{
    char rut[11];
    char nombre[40];
    int entradas;
    struct personas *sig;
};

typedef struct personas tPersonas;
typedef tPersonas *Lista;

/*
Entrada: Variables de la estructura persona

Salida: Lista Dinamica

Proceso: Funcion que crea un nodo para poder crear una lista dinamica
*/
//CREAR NODO DE LA LISTA
Lista creaNodo(char rut[11], char nombre[40], int entradas)
{
    Lista p;

     p = malloc(sizeof(tPersonas));

    if (p != NULL)
    {
        strcpy(p->rut, rut);
        strcpy(p->nombre, nombre);
        p->entradas = entradas;
        p->sig = NULL;
    }

    else
    {
        printf("no hay memoria, adios");
        exit(-1);
    }

    return p;
}

/*
Entrada: Resive un puntero de la estructura de tipo Lista llamada L.

Salida: Imprime en pantalla los datos almacenados en cada nodo de la lista.

Proceso: Funcion que revise el tipo de Lista L y con un auxiliar recorre toda la lista hasta el ultimo nodo,
         y va imprimiendo cada dato de cada nodo hasta que el auxiliar sea NULO.
*/
//IMPRIMIR LA LISTA
void imprimeLista(Lista L)
{
    Lista aux;

    aux = L;
    //RECORRO TODA LA LISTA
    while (aux != NULL)
    {
        printf("%s %s %i \n", aux->rut, aux->nombre, aux->entradas);
        aux = aux->sig;
    }
}

/*
Entrada: Resive un puntero de la estructura de tipo Lista llamada L y ademas resive todas las variables que posee la estructura Personas.

Salida: Retorna la Lista

Proceso: Funcion que revise el tipo de Lista L ademas de las variables y crea una nueva lista llamada pPersonas, esta revisa si la lista L esta vacia si es asi se iguala con
        pPersonas y se va agregando al final cada Nodo
*/
//INSERTAR EN LA LISTA
Lista insertaFinal(Lista L, char rut[11], char nombre[40], int entradas)
{
    Lista pPersonas;
    Lista aux;

    pPersonas = creaNodo(rut, nombre, entradas);

    if (L == NULL)
    {
        L = pPersonas;
    }
    else
    {
        aux = L;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = pPersonas;
        aux = NULL;
    }
    return L;
}

/*
Entrada: Resive el nommbre del archivo que queremos leer

Salida: Retorna una Lista L con los datos que leyo del archivo

Proceso: La funcion resive el nombre del archivo que se quiere leer, luego se habre este mismo archivo en modo escritura, si el archivo no se encuntra le avisa al usuario
         en cambio si se encuentra el archivo se va leyendo linea por linea del archivo con un while y la funcion fgets y se separan los datos con strtok cada vez que se
         encuentre una coma este los separa por variable, y como la variable entrada en el archivo es de tipo char, por lo que la cambiamos con atoi para que sea un entero
         luego guardamos todos esto datos en un tipo de lista L con la funcion insertar al final.
*/

//LEER ARCHIVO
Lista LeerArchivo(char NombreArchivo [20])
{
    char lineas[100];
    char *rut;
    char *nombre;
    char *cadena;
    int entradas;
    FILE * archivo;

    archivo = fopen(NombreArchivo, "r");

    Lista L;
    L = NULL;

// SI EL ARCHIVO NO SE ENCUENCUENTRA
    if (archivo == NULL)
    {
        printf("No se encontro el archivo, adios");
        exit(-1);
    }

// LEER TODO EL ARCHIVO
    else
    {
        while (fgets(lineas, 100, archivo) != 0)
        {
            strtok(lineas, "\n");

            // SEPARAR LOS DATOS
            rut = strtok(lineas, ","),
            nombre = strtok(NULL,",");
            cadena = strtok(NULL,",");
            entradas = atoi(cadena);

            L = insertaFinal(L, rut, nombre, entradas);
        }
        fclose(archivo);

        return L;
    }
}

Lista EntradasPorRut(Lista L)
{
    Lista nuevaLista;
    nuevaLista = NULL;

    Lista aux;
    aux = L;

    while (aux != NULL)
    {
        int contador = 0;

        Lista aux1;
        aux1 = nuevaLista;

        while (aux1 != NULL)
        {
            if (strcmp(aux1->rut, aux->rut) == 0)
            {
                contador = 1;
            }
            aux1 = aux1->sig;
        }

        // Si el rut no ha sido leido antes
        if (contador == 0)
        {
            int entradas = 0;

            Lista aux2;
            aux2 = L;

            while (aux2 != NULL)
            {
                if (strcmp(aux2->rut, aux->rut) == 0)
                {
                    entradas += aux2->entradas;
                }
                aux2 = aux2->sig;
            }

            nuevaLista = insertaFinal(nuevaLista, aux->rut, aux->nombre, entradas);
        }

        aux = aux->sig;
    }
    imprimeLista(nuevaLista);
    return nuevaLista;
}

Lista PersonasInscritas(Lista L)
{
    Lista aux;
    Lista personasinscritas;

    personasinscritas = NULL;

    aux = L;

    int asignadas = 0;
    int pendientes = 50;

    while(aux != NULL && asignadas < 50)
    {
        if(aux->entradas <= 5)
        {
            if (aux->entradas >= 2 && asignadas == 49)
            {
                personasinscritas = insertaFinal(personasinscritas, aux->rut, aux->nombre, 1);
                asignadas += 1;
            }
            else if (aux->entradas > 2)
            {
                personasinscritas = insertaFinal(personasinscritas, aux->rut, aux->nombre, 2);
                asignadas += 2;
            }

            else
            {
                personasinscritas = insertaFinal(personasinscritas, aux->rut, aux->nombre, aux->entradas);
                asignadas += aux->entradas;
            }
        }
        aux = aux->sig;
    }

    pendientes -= asignadas;

    return personasinscritas;
}

Lista ListaDeEspera(Lista L, Lista PI)
{
    Lista aux;
    aux = L;

    Lista listaDeEspera;
    listaDeEspera = NULL;


    while (aux != NULL)
    {
        if (aux->entradas == 1 || aux->entradas == 2)
        {
            int contador = 0;

            Lista aux2;
            aux2 = PI;

            while (aux2 != NULL)
            {
                if (strcmp(aux->rut, aux2->rut) == 0)
                    {
                        contador = 1;
                    }
                aux2 = aux2->sig;
            }

            if (contador == 0)
                {
                    listaDeEspera = insertaFinal(listaDeEspera, aux->rut, aux->nombre, aux->entradas);
                }
        }
        aux = aux->sig;
    }

    return listaDeEspera;
}

void ArchivoAsignadas (Lista L, char NombreArchivo[20])
{
    char * PersonasAsignadas;
    FILE * archivo;

    archivo = fopen(NombreArchivo, "r");

    PersonasAsignadas = strtok(NombreArchivo, ".");
    strcat(PersonasAsignadas, ".asg");

    archivo = fopen(PersonasAsignadas, "w");

    Lista aux;
    aux = L;

    while (aux != NULL)
    {
        fprintf(archivo, "%s,%s,%i \n", aux->rut, aux->nombre, aux->entradas);
        aux = aux->sig;
    }

    int asignadas = 0;
    int pendientes = 50;
    aux = L;

    while (aux != NULL)
    {
        asignadas += aux->entradas;
        aux = aux->sig;
    }

    pendientes -= asignadas;

    fprintf(archivo, "\nAsignadas: %i\n", asignadas);
    fprintf(archivo, "Pendientes: %i\n", pendientes);

    fclose(archivo);
}

void ArchivoEspera (Lista L, char NombreArchivo[20])
{
     if (L == NULL)
    {
        return;
    }

    char * PersonasEspera;
    FILE * archivo;

    archivo = fopen(NombreArchivo, "r");

    PersonasEspera = strtok(NombreArchivo, ".");
    strcat(PersonasEspera, ".esp");

    archivo = fopen(PersonasEspera, "w");

    Lista aux;
    aux = L;

    while (aux != NULL)
    {
        fprintf(archivo, "%s,%s \n", aux->rut, aux->nombre);
        aux = aux->sig;
    }

    fclose(archivo);
}

int main()
{
    Lista L;
    Lista L2;
    Lista L3;

    char NombreArchivo[20];

    printf("Ingrese nombre del archivo: ");
    fgets(NombreArchivo, 20, stdin);
    strtok(NombreArchivo, "\n");

    L = LeerArchivo(NombreArchivo);

    L = EntradasPorRut(L);

    L2 = PersonasInscritas(L);

    L3 = ListaDeEspera(L, L2);

    ArchivoAsignadas(L2, NombreArchivo);

    ArchivoEspera(L3, NombreArchivo);

    printf("\nSe han generado los archivos corresponientes\n");

    return 0;
}

