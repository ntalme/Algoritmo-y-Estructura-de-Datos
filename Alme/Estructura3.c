
#include <stdio.h>

struct esfera
{
    int Cx;
    int Cy;
    int Cz;
    float radio;
};
typedef struct esfera tEsfera;


int main()
{
    tEsfera esfera1;
    tEsfera *p;

    esfera1.Cx = 30;
    esfera1.Cy = 28;
    esfera1.Cz = 15;
    esfera1.radio = 9;

    printf("Radio Esfera 1 = %2.f\n", esfera1.radio);

    p = &esfera1;
    //Con esto puntero p se casa con estructura esfera

    p->Cx = 32;
    p->Cy = 30;
    p->Cz = 17;
    p->radio = 11;

    printf("Radio Esfera 1 = %2.f\n", esfera1.radio);

    return 0;
}
