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
Entrada: Resive los parametros de la estructura personas.

Salida: Retorna un nodo de la Lista Dinamica.

Proceso: La funcion inicia creando una variable de tipo Lista llamada p, la cual corresponde a un puntero, luego de esto con la funcion malloc se busca un espacio
         en la RAM para tPersonas, y mientras el puntero p sea distinto de NULL se igualara p->rut con la variable rut, p->nombre con la variable nombre pero como estas
         son de tipo char se debe usar strcpy para que esto ocurra, luego se igualara p->entradas con la variable entradas y por ultimo se le asiganara p->sig el valor NULL,
         para luego retornar el puntero al nuevo nodo creado.
         En el caso de que p = NULL es decir no se pudo asignar memoria la funcion imprimira el mensaje "no hay memoria, adios! y terminara el programa sin retornar el puntero p.

*/
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
Entrada: Resive un puntero de la estructura de tipo Lista y ademas resive todos los parametros que posee la estructura personas.

Salida: Retorna una la Lista que va insertando los datos desde el final.

Proceso: La funcion revise una variable de tipo de Lista de nombre L ademas de los parametros de tPersonas, leugo la funcion va creando nodos llamando
         a la funcion creaNodo. Luego revisa si es que la lista L esta vacia, si es así esta se iguala a el nodo tPersonas. Luego si la lista ya tiene
         datos con un while se revisara que la variable auxliar sea disntito a nulo, cabe aclarar que la varible auxiliares igual a la lista L, por lo
         que auxiliar pasara a ser igual a aux->sig si esta es nula se igualara con el nodo pPersonas por lo que se ira creando una lista dinamica la
         cual sera retornada al final.

*/
Lista insertaFinal(Lista L, char rut[11], char nombre[40], int entradas)
{
    Lista pPersonas;
    Lista aux;

    aux = L;
    pPersonas = creaNodo(rut, nombre, entradas);

    if (L == NULL)
    {
        L = pPersonas;
    }

    else
    {
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
Entrada: Resive el nombre del archivo que queremos leer con un maximo de 20 caracteres.

Salida: Retorna una Lista L con los datos que leyo del archivo.

Proceso: La funcion resive el nombre del archivo que se quiere leer, luego se habre este mismo archivo en modo escritura, si el archivo no se encuntra le avisa al usuario
         en cambio si se encuentra el archivo se va leyendo linea por linea del archivo con un while y la funcion fgets, luego se separan los datos con strtok cada vez que se
         encuentre una coma este los separa por variable, pero como la variable entrada en el archivo es de tipo char la debemos cambiar con atoi para que sea un entero,
         luego guardamos todos esto datos en una variable tipo de lista L con la funcion insertar al final.
*/
Lista LeerArchivo(char NombreArchivo [20])
{
    char lineas[100];
    char *rut;
    char *nombre;
    char *cadena;
    int entradas;
    Lista L;
    FILE * archivo;

    archivo = fopen(NombreArchivo, "r");

    L = NULL;

    if (archivo == NULL)
    {
        printf("No se encontro el archivo, adios");
        exit(-1);
    }

    else
    {
        while (fgets(lineas, 100, archivo) != 0)
        {
            strtok(lineas, "\n");
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
/*
Entrada: Resive un puntero de la estructura de tipo Lista
Salida:
Proceso:
*/
Lista EntradasPorRut(Lista L)
{
    Lista nuevaLista;
    Lista aux;
    Lista aux1;
    Lista aux2;
    int contador;
    int entradas;

    nuevaLista = NULL;
    aux = L;

    while (aux != NULL)
    {
        contador = 0;
        aux1 = nuevaLista;

        while (aux1 != NULL)
        {
            if (strcmp(aux1->rut, aux->rut) == 0)
            {
                contador = 1;
            }
            aux1 = aux1->sig;
        }
        if (contador == 0)
        {
            entradas = 0;
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
    return nuevaLista;
}
/*
Entrada: Resive un puntero de la estructura de tipo Lista
Salida:  Retorna una variable de tipo Lista con solo las personas que compraron igual o menos de 5 entradas.
Proceso: La funcion crea dos variables de tipo Lista y se definen dos enteros para saber las cantidas de entradas totales que se asignaron, luego con un while
         vamos verificando si se cumple que la cantidad de entradas es menor a 50 y recorremos toda la lista mientras la variable auxiliar sea distinto de nulo
         luego con un if revisamos si la cantidad de entradas por rut es igual o menor a 50 si es asi, se cumplira que:
         Si la cantidad de entradas solicitadas es mayor o igual a 2 y la cantidad de entradas asignadas es igual a 49 solo se entregara una entrada ya que lo maximo
         de entradas es 50, luego si esto no se cumple se revisara si la cantidad de entradas es mayor a 5 si es asi al usuario solo se le entregaran 2 entradas y luego
         si tampoco se cumple esa condicion se le entragarn las entradas solcitadas por el usuario, luego la variable auxiliar pasara al siguiente nodo hasta que auxiliar
         sea igual a nulo y cuando esto ocurra la funcion terminara retornando una variable tipo lista con todo el filtro anteriormente puesto.
*/
Lista PersonasInscritas(Lista L)
{
    Lista aux;
    Lista personasinscritas;

    aux = L;
    personasinscritas = NULL;
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
    return personasinscritas;
}
/*
Entrada: Resive dos variable de tipo Lista una con la lista original y otra con la lista creada en la funcion PersonasInscritas
Salida: Retorna una variable de tipo Lista con las personas que quedaron afuera de la promocion pero que no estan penalizadas.
Proceso: La funcion crea tres variables de tipo lista y una variable entera llamada contador, con una variable while mientras la variable auxiliar
         sea distinto de nulo, si es asi se revisara si la cantidad de entradas por personas es igual a 1 o 2, si esto se cumple la variable aux 2 sera igual
         a la lista PI e ira verificando si el rut que esta en la variable aux es igual al de la variable aux2 si es asi, contador se igualara a 1, y se pasara
         al siguiente nodo, pero si contador es igual a 0, es decir que el rut no se ha encontrado repetido el nodo se agregara a la listadeEspera con la funcion
         insertaFinal para poder crear una nueva lista dinamica. Si nada de lo anterior se cumple aux avanzara al siguiente nodo. Por ultimo se retornara la nueva lista
         con las personas que corresponden a la lista de espera.
*/
Lista ListaDeEspera(Lista L, Lista PI)
{
    Lista aux;
    Lista aux2;
    Lista listaDeEspera;
    int contador;

    aux = L;
    listaDeEspera = NULL;
    while (aux != NULL)
    {
        if (aux->entradas == 1 || aux->entradas == 2)
        {
            contador = 0;
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
/*
Entrada: Resive dos variables, una de tipo Lista llamada L y una variable de tipo char con el nombre del archivo que ponga el usuario.
Salida: No retorna nada, pero crea un archivo de tipo asg solo con las personas que alcanzaron la promocion.
Proceso: La funcion abre el archivo en modo lectura con el nombre que se ingresa en la funcion LeerArchivo, luego el puntero PersonasAsignadas copia
         el nombre del archivo hasta el primer punto que se encuntre para luego cambiar lo que haya despues del punto por .asg. Luego de esto se vuelve
         a abrir el archivo en modo escritura pero con el nombre asignado en PersonaAsignadas. Despues se verifica que la variable auxiliar (que es igual
         a la lista ingresada) sea distinta de nulo, si es asi, se copiaran los datos en el archivo y se sumaran todas las entradas asignadas para luego
         pasar al siguiente nodo hasta que aux sea igual a nulo. Por ultimo se le edita el valor a la variable pendiente para que se le reste la cantidad de entradas
         asignadas, y asi con la funcion printf imprimimos en el archivo la cantidad de entradas asignadas y pendientes, para que luego de esto se cierre el archivo.
*/
void ArchivoAsignadas (Lista L, char NombreArchivo[20])
{
    char * PersonasAsignadas;
    FILE * archivo;
    Lista aux;

    aux = L;
    int asignadas = 0;
    int pendientes = 50;

    archivo = fopen(NombreArchivo, "r");

    PersonasAsignadas = strtok(NombreArchivo, ".");
    strcat(PersonasAsignadas, ".asg");

    archivo = fopen(PersonasAsignadas, "w");

    while (aux != NULL)
    {
        fprintf(archivo, "%s,%s,%i \n", aux->rut, aux->nombre, aux->entradas);

        asignadas += aux->entradas;

        aux = aux->sig;
    }
    pendientes -= asignadas;
    fprintf(archivo, "\nAsignadas: %i\n", asignadas);
    fprintf(archivo, "Pendientes: %i\n", pendientes);
    fclose(archivo);
}
/*
Entrada: Resive dos variables, una de tipo Lista llamada L y una variable de tipo char con el nombre del archivo que ponga el usuario.
Salida: No retorna nada, pero crea un archivo de tipo esp solo con las personas que no alcanzaron la promocion pero que no estan penalizadas.
Proceso: La funcion revisa si la lista ingresada es nula, de ser asi no crea el archivo de la lista de espera, en cambio si la lista no esta vacia se abre el archivo
         con el nombre que se ingreso en la funcion LeerArchivo en modo lectura, luego al archivo de las personas de espera se le copia el nombre del archivo hasta el
         primer punto que se encuntre para luego cambiar lo que haya despues del punto por .esp. Por ultimo se edita la variable archivo para que se abra con el nombre
         de PersonasEspera pero esta vez en modo escritura y mientras el auxiliar (que es igual a la lista ingresada) sea distinto de nulo se imprimiran los datos en
         el archivo. Luego de recorrer toda la lista hasta que aux se vuelva nulo se cierra el archivo.

*/
void ArchivoEspera (Lista L, char NombreArchivo[20])
{
    if (L == NULL)
    {
        return;
    }
    else
    {
        char * PersonasEspera;
        FILE * archivo;
        Lista aux;

        aux = L;

        archivo = fopen(NombreArchivo, "r");

        PersonasEspera = strtok(NombreArchivo, ".");
        strcat(PersonasEspera, ".esp");

        archivo = fopen(PersonasEspera, "w");

        while (aux != NULL)
        {
            fprintf(archivo, "%s,%s \n", aux->rut, aux->nombre);
            aux = aux->sig;
        }
        fclose(archivo);
    }
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

    L2 = PersonasInscritas(L);

    L3 = ListaDeEspera(L, L2);

    ArchivoAsignadas(L2, NombreArchivo);

    ArchivoEspera(L3, NombreArchivo);

    printf("\nSe han generado los archivos corresponientes\n");

    return 0;
}

