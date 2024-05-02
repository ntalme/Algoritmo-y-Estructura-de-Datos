
//void numAmigos()
//{
//    int cont;
//    int i, j, k;
//    int visitados[numNodos][numNodos];
//
//    for (i=0; i<numNodos; i++)
//    {
//        for(j=0; j<numNodos; j++)
//        {
//            if(i != j && visitados[i][j] == 0 )
//            {
//                cont = 0;
//                for (k=0; k<numNodos; k++)
//                {
//                    if (Grafo[i][k] != 0 && Grafo[j][k] != 0)
//                    {
//                        cont++;
//                    }
//                }
//                printf("%s, %s: %i\n", Nombres[i], Nombres[j], cont);
//                visitados[i][j] = 1;
//                visitados[j][i] = 1;
//            }
//        }
//    }
//}
