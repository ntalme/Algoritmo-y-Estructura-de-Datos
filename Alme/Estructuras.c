
#include <stdio.h>
#include <math.h>

//Las estructuras funcionan como las clases en Python

struct punto
{
    float x;
    float y;
};
typedef struct punto TipoPunto;

int main()
{
    TipoPunto p1, p2, p3={4,5};
    //variables de "TipoPunto"

    p1.x = 12;
    p1.y = p1.x + p3.y;

    p2.x = 2;
    p2.y = pow(p2.x, 3);

    printf("p1 = (%2.f, %2.f)\n", p1.x, p1.y);
    printf("p2 = (%2.f, %2.f)\n", p2.x, p2.y);
    printf("p3 = (%2.f, %2.f)\n", p3.x, p3.y);
    return 0;
}
