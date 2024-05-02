#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define infinito 10000000

/*VARIABLES GLOBALES PARA MATRICES
 int **Grafo es un puntero en el que se guardará la dirección de la matriz Grafo, int numNodos es la cantidad de nodos que hay en el grafo
 int numArcos es la cantidad de arcos que existen en el grafo, char **Nombres es el puntero en el que se guardará la dirección de la matriz Nombres.
*/
int **Grafo;
int numNodos;
int numArcos;
char **Nombres;
/*VARIABLES GLOBALES PARA DIJKSTRA
bool *Visitados es un puntero a un arreglo en el cual dentro se almacena si un nodo ha sido visitado, asignadole a la posición un true y en caso contrario un false
int *Costo es un puntero a un arreglo en el cual dentro se almacena en cada posición el costo asociado al nodo correspondiente.
int *Predecesor es un puntero a un arreglo en el cual dentro se almacena en cada posición el predecesor segun el nodo correspondiente.
int *Camino es un puntero donde adentro se guardará la secuencia del camino para llegar de un nodo a otro.
*/
bool *Visitados;
int *Costo;
int *Predecesor;
int *Camino;
/*
Entrada: No recibe nada como entrada
Salida: La función no retorna nada.
Proceso: La función inicia creando una variable de tipo entero llamado i. Luego,con la función calloc se busca un espacio en la RAM para el puntero Grafo de tamaño
         numNodos de tipo puntero. Luego se inicia un bucle for donde se inicia la variable i en 0, y este incrementa hasta que i sea igual al numero de nodos -1,
         esto creara una nueva fila en la matriz del grafo y le buscará un espacio en la RAM para de tamaño numnodos pero de tipo entero.
         Para que así cuando se termine de ejecutar esta función se cree una matriz cuadrada de tamaño numNodos.
*/
void creaMatrizGrafo()
{
   int i;

   Grafo = calloc(numNodos, sizeof(int *));

   for(i=0; i<numNodos; i++)
   {
      Grafo[i] = calloc(numNodos, sizeof(int));
   }
}
/*
Entrada: No recibe nada como entrada.
Salida: La función no retorna nada.
Proceso: La función inicia creando una variable de tipo entero llamado i. Luego, con la función calloc se busca un espacio en la RAM de tamaño de numNodos de tipo puntero char.
         Luego, se inicia un bucle for donde se inicia la variable i en 0, y este incrementa hasta que i sea igual al numero de nodos -1, esto creara una nueva fila en la matriz nombre donde se le asignará un espacio en la RAM de
         tamaño de 30 caracteres pero de tipo char.
         Para que así cuando se termine de ejecutar esta función se almacen todos los nombres de los nodos.
 */
void creaMatrizNombres()
{
   int i;

   Nombres = calloc(numNodos, sizeof(char *));

   for(i=0; i<numNodos; i++)
   {
      Nombres[i] = calloc(30, sizeof(char));
   }
}
/*
Entrada: No recibe nada como entrada.
Salida: La función no retorna nada.
Proceso: La función se encarga de asignarle a cada puntero un tamaño en la RAM de tamaño de numNodos pero cada uno con su respectivo valor (bool, int).
*/
void creaArreglosParaDijkstra()
{
    Visitados = calloc(numNodos, sizeof(bool));
    Costo = calloc(numNodos, sizeof(int));
    Predecesor = calloc(numNodos, sizeof(int));
    Camino = calloc(numNodos, sizeof(int));
}
/*
Entrada: Recibe una variable de tipo char de maximo 30 caracteres, el cual corresponde al nombre que se quiere buscar.
Salida: Retorna un entero.
Proceso: La función comienza definiendo una variable de tipo entero llamada i. Luego, se utiliza un bucle for para
         recorrer toda la matriz, donde se inicia la variable i en 0, y este incrementa hasta que i sea igual al numero de nodos -1.
         Dentro del bucle, con un if se revisa si en la posición i de la matriz Nombres se encuentra el nombre ingresado. Si esto se cumple,
         se retornará la posición del nombre buscado. En el caso que el nombre no se encuentre en la matriz Nombres, se retornará un -1.
*/
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
/*
Entrada: Recibe una variable de tipo char con el nombre del archivo que digite el usuario.
Salida: La función no retorna nada.
Proceso: La función recibe el nombre del archivo que se quiere leer. Luego se abre este mismo archivo en modo lectura. Si el archivo no se encuentra, se le avisa al usuario.
         Si el archivo es encontrado, se lee el primer entero que aparece y se define como la cantidad de nodos de la matriz.Esto se utiliza para llamar a las funciones que
         crean la matriz del grafo y la matriz de los nombres, asignándoles un tamaño según el valor de numNodos.
         Luego, se lee el segundo número entero que aparece y se asigna como la cantidad de arcos que existen. Luego, se utiliza un bucle for para leer cada nombre hasta que i
         sea igual a la cantidad de nodos, asignándole una posición en la fila i en la matriz Nombres.
         Finalmente, se utiliza otro bucle for para leer las relaciones hasta que i sea igual a la cantidad de arcos que existen. Utilizando strtok, se asigna a
         la variable persona1 todo lo que está antes de la primera coma encontrada y luego, con otro strtok se asigna a la variable persona2 todo lo que está después de la coma.
         Después de esto, se usa la función posicionDeNombre para verificar si el nombre está en la matriz, y se guarda en la variables nodo1 y nodo2 la posición corresponiente.
         Esto nos permite poner en el grafo las posiciones de ambos nombres, es decir el valor de la fila nodo1 y la columna nodo2 es igual a 1, esto nos indica que existe una
         relación entre los nodos, es decir que existe un arco y como es un grafo no dirigido, se debe poner tambien que existe una relación entre el la fila nodo2 y la columna
         nodo1, para así luego cerrar el archivo.
*/
void leeGrafo(char nomArchivo[30])
{
    FILE *arch;
    int i, nodo1, nodo2;
    char linea[100];
    char *persona1, *persona2;

    arch = fopen(nomArchivo, "r");

    if (arch == NULL)
    {
        printf("Archivo no encontrado");
        exit(-1);
    }

    fscanf(arch, "%i", &numNodos);

    creaMatrizGrafo();
    creaMatrizNombres();

    fscanf(arch, "%i\n", &numArcos);
    for (i=0; i<numNodos; i++)
    {
        fgets(linea, 100, arch);
        strtok(linea, "\n");
        strcpy(Nombres[i], linea);
    }

    for (i=0; i<numArcos; i++)
    {
        fgets(linea, 100, arch);
        strtok(linea, "\n");
        persona1 = strtok(linea, ",");
        persona2 = strtok(NULL, ",");

        nodo1 = posicionDeNombre(persona1);
        nodo2 = posicionDeNombre(persona2);

        Grafo[nodo1][nodo2] = 1;
        Grafo[nodo2][nodo1] = 1;
    }
    fclose(arch);
}
/*
Entrada: Recibe dos enteros que corresponden al nodo inicial y el nodo final que se quiere buscar.
Salida: La función no retorna nada.
Proceso: La función inicia igualando la variable i con la variable fin, esto para que el camino se escriba desde atras hacia adelante.
         Luego, se verifica si el nodo final es diferente al nodo inicial. Si es así, significa que hay un camino entre ambos nodos. Luego, se le asigna el valor de
         la variable fin a la primera posición del arreglo Camino. Después, con un bucle for iniciando j con valor 1 y este ira incremantando se realizará hasta que
         el nodo actual sea igual al nodo inicial. Dentro de este bucle se define el arreglo camino de la posicion j igual al nodo el cual tiene el predecesor de i, luego
         se cambia el valor de la variable nodo por el predecesor que le pertenezca a la variable nodo.
         Luego, cuando sale del bucle el arreglo camino se asigna el nodo inicial al último elemento del arreglo Camino, para que así tambien se incluya el primer nodo en el camino.
         Por ultimo, se utiliza un bucle for inverso desde j hasta 0. Para así imprimir el camino desde el primer nodo hasta el ultimo, debido a que la función escribe el camino
         desde el ultimo nodo hasta el primero.
*/
void ImprimeCaminos(int inicio, int fin)
{
    int i, j, nodo;

    i = fin;
    if (i != inicio)
    {
        Camino[0] = i;
        nodo = Predecesor[i];
        for (j=1; nodo!=inicio; j++)
        {
            Camino[j] = nodo;
            nodo = Predecesor[nodo];
        }
        Camino[j] = nodo;
        for (; j>=0; j--)
            printf("\n%s", Nombres[Camino[j]]);
    }
}
/*
Entrada: No recibe nada como entrada.
Salida: Retorna un entero, en este caso un contador.
Proceso: La función inicia estableciendo la variable contador en 0. Luego, con un bucle for donde se inicia la variable i en 0,
         y este incrementa hasta que i sea igual al numero de nodos -1.
         Dentro de este bucle se revisa si el nodo en la posición i del arreglo visitados no ha sido visitado, si esto se cumple
         la variable contador incrementara. Luego cuando el bucle for termine la función retornara el valor final que obtuvo la variable contador.
*/
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
/*
Entrada: No recibe nada como entrada.
Salida: Retorna un entero.
Proceso: La función comienza asigando a la variable esElPrimero el valor true. Luego, se inicia un bucle for
         donde se inicia la variable i en 0, la cual se ira incrementando hasta que i sea igual a la cantidad de nodos -1.
         Dentro de este bucle, se revisa con un if si el arreglo visitados en la posicion i no ha sido visitado. Si esto
         se cumple, se verifica con otro if si la variable esElPrimero es true. De cumplirse esta condición a la variable minimo
         se le asignará el costo de la posicion i, y a la variable nodo se le asigna el nodo actual i.
         Por ultimo se actualiza la varibable esElPrimero como false.
         En el caso de que esElPrimero sea false, es decir, que no sea el primer nodo encontrado y no visitado, con un if se comparará
         si el el costo en posición i es menor al valor de la variable minimo. Si esto se cumple, se actualiza el valor minimo por el
         costo del nodo actual y se le asigna el valor del nodo actual a la variable nodo.
         Cuando el bucle termine se retornara el valor del nodo, el cual sera el nodo que no ha sido visitado que tenga el minimo costo.
*/
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
/*
Entrada: Recibe tres variables de tipo entero
Salida: La función no retorna nada.
Proceso: La función inicia declarando la variable visitado del nodo inicial como true. Luego, con un bucle for
         donde se inicia la variable i en 0, y este incrementa hasta que i sea igual al numero de nodos -1.
         Dentro de este bucle, con un if se revisa si el valor de la posición de la fila inicio y columna i es igual a 0
         Esto nos indica que no existe una relación directa entre los nodos, es decir, no es adyacente del nodo inicio,
         por lo que se le asigna el valor infinito al costo de nodo i.
         Lo anterior, nos indica que no hay camino que lleve del nodo inicial hasta i. Si la condición anterior no se cumple, se le asigna el valor
         del costo del arco al nodo i.
         Luego, se le asigna al arreglo predecesor del nodo i el nodo inicial. Despues, con un bucle while que se ejecuta mientras en la funcion
         NumerosNodosSinvisirar sea mayor a 1. Esto nos indica que hay nodos que aun no se han podido visitar.
         Dentro del bucle, se declara que la variable w es igual a la función NodoMinimoCostoSinVisitar, la cual revisa los adyasentes sin visitar
         y de costo minimo. Luego, se marca el nodo w como visitado.
         Por ultimo, se utiliza otro bucle for donde se inicia la variable i en 0, y este se irá incrementando hasta que i sea igual al numero de nodos -1.
         Dentro de este bucle se verificará si el valor de la fila w y columna i es distinto de 0, es decir, que hay una relación entre ambos y a su vez
         no haya sido visitado. Si esta condición se cumple, con otro if se verifica si el costo actual más el costo del arco es menor al costo que habia anteriormente.
         De ser así, se cambia el valor del predecesor del nodo i por el nodo w, y luego se actualiza el costo de nodo i con la suma del costo del nodo actual más el
         valor del arco.
*/
void DIJKSTRA(int **Grafo, int numNodos, int inicio)
{
    int i, j, w=inicio;

    Visitados[inicio] = true;
    for (i=0; i<numNodos; i++)
    {
        if (Grafo[inicio][i] == 0)
        {
            Costo[i] = infinito;
        }
        else
        {
            Costo[i] = Grafo[inicio][i];
        }
        Predecesor[i] = inicio;
    }
    while (NumeroNodosSinVisitar()>1)
    {
        w = NodoMinimoCostoSinVisitar();
        Visitados[w] = true;
        for (i=0;i<numNodos;i++)
        {
            if (Grafo[w][i] != 0 && Visitados[i] == false)
            {
                if (Costo[w] + Grafo[w][i] < Costo[i])
                {
                    Predecesor[i] = w;
                    Costo[i] = Costo[w] + Grafo[w][i];
                }
            }
        }
    }
}
/*
Entrada: No recibe nada como entrada.
Salida: La función no retorna nada.
Proceso: La función comienza verificando si el número de arcos es diferente de 0. Si es así, se utiliza la función creaArreglosParaDijkstra para generar los espacios de
         la ram correspondientes para que la funcion DIJKSTRA se ejecute. Luego, se le pide al usuario que ingrese su nombre y con la funcion posicionDeNombre se verifica si el nombre
         ingresado existe en la matriz. El valor que se retorne se guardara en la variable n1. Si el valor de n1 es igual a -1, significa que el nombre ingresado no existe. Esto se
         determina al revisar la funcion posicionDeNombre. En caso de que el n1 sea igual a una posicion válida de la matriz, se le pregunta al usuario a quien quiere conocer y lo que ingrese
         se guardará en la variable nombre2. Nuevamente, se utiliza la fucnion posicionDeNombre para verificar si el nombre ingresado existe en la matriz y lo que se retorne se guardara en la
         variable n2.
         Luego, se revisa si el valor de n2 es igual a -1. Si esto ocurre, significa que el nombre no esta en la matriz, por lo que se le avisará al usuario y se finalizara el programa.
         Si el nombre existe, se llamara a la funcion DIJKSTRA con los parametros Grafo, número de nodos y n1, que corresponde a la posición del primer nombre ingresado por el usuario, para así
         comenzar desde ese nodo.
         Luego, se revisa con un if si el valor en la posicion de la fila n1 y columna n2 y a su vez el valor en la fila n2 y columna n1 sea igual a 0. Esto significa que no hay una relación directa
         entre esos dos nodos, ya que en caso de ser igual a 1, se le avisará al usuario que los dos nombres ingresados ya son amigos. En el caso de que sea igual a 0 con otro if para verificar
         si el costo de n2r es distinto de infinito. Esto se debe a que en la funcion DIJKSTRA se utiliza el valor infinito para representar la falta de conexión entre dos nodos en el grafo, debido a
         que DIJSTRA pasa por todos los nodos del grafo cambiandole su costo a uno menor a infinito, por lo tanto si este costo sigue siendo infinito significa que DIJKSTRA no pudo pasar por esos nodos
         lo que nos indicaría que se trata de un grafo desconexo.
         Si el costo es distinto de infinito, se utiliza la función ImprimeCaminos para mostrar al usuario la secuencia que debe realizar para conocer a una persona.
         Si el valor es igual a infinito significa que se trata de un grafo desconexo por lo que si ambos nombres estan en diferentes grafos, no podrán llegar a conocerse, por lo que no se imprimirá
         ningún camino.
*/
void SecuenciaAmigos()
{
    char nombre1[30], nombre2[30];
    int n1, n2;

    if (numArcos != 0)
    {
        creaArreglosParaDijkstra();
        printf("\nIngresa tu nombre: ");
        fgets(nombre1, 30, stdin);
        strtok(nombre1, "\n");
        n1 = posicionDeNombre(nombre1);
        if (n1 == -1)
        {
            printf("\nEl nombre ingresado no existe, el programa se cerrara.\n");
            exit(0);
        }

        printf("A quien quieres conocer?: ");
        fgets(nombre2, 30, stdin);
        strtok(nombre2, "\n");
        n2 = posicionDeNombre(nombre2);
        if (n2 == -1)
        {
            printf("\nEl nombre ingresado no existe, el programa se cerrara.\n");
            exit(0);
        }
        DIJKSTRA(Grafo, numNodos, n1);
        if (Grafo[n1][n2] == 0 && Grafo[n2][n1] == 0)
        {
            if (Costo[n2] != infinito)
            {
                printf("\nLa secuencia de nombres es: ");
                ImprimeCaminos(n1,n2);
            }
            else
            {
                printf("\nLo siento, no es posible conocer a esta persona.\n");
                exit(0);
            }
        }
        else
        {
            printf("\nUstedes ya son amigos!\n");
            exit(0);
        }
    }
    else
    {
        printf("\nNo existen amistades.\n");
        exit(0);
    }
}
/*
Entrada: Recibe una variable de tipo char con el nombre del archivo que digite el usuario.
Salida: La función no retorna nada.
Proceso: La función comienza abriendo el archivo que digito el usuario en modo lectura. Luego, se copia el nombre del archivo en la variable "AmigosenComun" hasta el
         primer punto que se encuentre, y se reemplaza todo lo que está después del punto por .aec. Después de eso, se modifica la variable archivo para que se abra
         con el nombre de AmigosenComun, pero esta vez en modo escritura.
         Luego, se usa un bucle for  donde se inicia la variable i en 0, y este incrementa hasta que i sea igual al numero de nodos -1. Dentro de este bucle, se inica otro bucle for pero en este caso la variable
         j que recorrera los nodos sera igual a i + 1 para evitar que se dupliquen datos de los amigos en comun. Dentro de este segundo bucle, se inicia la variable contador en 0
         para así contar la cantidad de amigos comunes entre los nodos i y j. Luego de esto, se inicia un ultimo bucle for con la variable w iniciando en 0. Dentro de este bucle
         se verifica si el valor en la posicion fila i y columna w es es igual a 1, lo cual indica que existe una relacion entre ellos. Además, se verifica si en la posicion fila j
         y columna w tambien existe una relacion. Si ambas condiciones se cumplen la variable contador incrementara su valor.
         Una vez finalizado el último bucle, se imprime en el archivo el nombre correspondiente con la posicion i en la matriz Nombres, junto con el nombre de la posicion j en la matriz Nombres
         y la cantidad de amigos en comun almacenda en la variable contador. Para por ultimo cerrar el archivo.
*/
void ArchivoAmigosComunes (char nomArchivo[30])
{
    char * AmigosenComun;
    FILE * archivo;
    int i, j, w, contador;

    archivo = fopen(nomArchivo, "r");
    AmigosenComun = strtok(nomArchivo, ".");
    strcat(AmigosenComun, ".aec");

    archivo = fopen(AmigosenComun, "w");

    for (i=0; i<numNodos; i++)
    {
        for(j=i+1; j<numNodos; j++)
        {
            contador = 0;
            for (w=0; w<numNodos; w++)
            {
                if (Grafo[i][w] == 1 && Grafo[j][w] == 1)
                {
                    contador++;
                }
            }
            fprintf(archivo, "%s, %s: %i\n", Nombres[i], Nombres[j], contador);
        }
    }
    fclose(archivo);
}
/*
Entrada: No recibe nada como entrada.
Salida: La función no retorna nada.
Proceso: En esta función se crean tres variables de tipo char, luego esta funcion le pedirá a el usuario que escriba el nombre del archivo que quiere abrir.
Luego se usara la función leeGrafo resiviendo como parametro el nombre del archivo ingresado, para asi leerlo y nos cree las matrices correspondientes.
Luego, mientras el numero de arcos sea distinto de 0, se creara el archivo de los amigos en comunes entre cada nombre con la funcion ArchivoAmigosComunes
recibiendou como paramatro el nombre del archivo, en caso de que el numero de arcos sea igual a 0, este archivo no se creara.
Por ultimo, se llamara a la funcion SecuenciaAmigos la cual, se encarga de mostrarnos la secuencia que se necesita para conocer a una persona en especifico.
*/
void procesoPrincipal()
{
    char nomArchivo[30];
    char nombre1[30], nombre2[30];

    printf("Ingresa nombre del archivo: ");
    fgets(nomArchivo, 30, stdin);
    strtok(nomArchivo, "\n");

    leeGrafo(nomArchivo);
    if (numArcos != 0)
    {
        ArchivoAmigosComunes(nomArchivo);
    }
    SecuenciaAmigos();
}
/*
Entrada: No recibe nada como entrada.
Salida: La función retorna un entero.
Proceso: Esta función es la función principal del codigo, con esta podemos correr el codigo haciendo que llame la función procesoPrincipal,
         luego que esta se ejecute se retornará un 0 para indicar que el programa se ejecuto de manera correcta.
*/
int main()
{
    procesoPrincipal();
    printf("\n\n");
    return 0;
}
