#include "MinimumSpanningTree.h"

int main(void)
{
    int adjmatrix[vertex_size][vertex_size];//图的邻接矩阵存储 
    AdjMatrix(adjmatrix);                   //对adjmatrix赋值
    Kruskal(adjmatrix);                     //Kruskal算法
    Prim(adjmatrix,0);                      //Prim算法，从顶点0开始
    return 0;
}
