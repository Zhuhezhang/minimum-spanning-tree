#include "MinimumSpanningTree.h"

int main(void)
{
    int adjmatrix[vertex_size][vertex_size];//ͼ���ڽӾ���洢 
    AdjMatrix(adjmatrix);                   //��adjmatrix��ֵ
    Kruskal(adjmatrix);                     //Kruskal�㷨
    Prim(adjmatrix,0);                      //Prim�㷨���Ӷ���0��ʼ
    return 0;
}
