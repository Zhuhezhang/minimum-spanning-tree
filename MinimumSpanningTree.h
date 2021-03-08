#ifndef MINIMUMSPANNINGTREE_H_
#define MINIMUMSPANNINGTREE_H_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#define MAX 999                                     //��ʾ�ߵ�Ȩֵ���޴�
using namespace std;
char vertex[] = {'A','B','C','D','E','F','G'};      //���� 
#define vertex_size ((sizeof(vertex))/(sizeof(vertex[0])))
                                                    //��������

//ͼ�ı���Ϣ
typedef struct
{
    int from;                                       //�����
    int to;                                         //���յ�
    int cost;                                       //�ߵ�Ȩֵ
}Arc;


//ͼ���ڽӾ����ʾ��(�α�P371��ͼ�ṹ)
void AdjMatrix(int adjmatrix[][vertex_size])
{
    for(int i = 0;i < vertex_size;i++)              //��ʼ���ڽӾ���
    {
        for(int j = 0;j < vertex_size;j++)
        {
            adjmatrix[i][j] = MAX;
        }
    }
    adjmatrix[0][1] = 28; adjmatrix[0][5] = 10;
    adjmatrix[1][0] = 28; adjmatrix[1][2] = 16; adjmatrix[1][6] = 14;
    adjmatrix[2][1] = 16; adjmatrix[2][3] = 12;
    adjmatrix[3][2] = 12; adjmatrix[3][4] = 22; adjmatrix[3][6] = 18;
    adjmatrix[4][3] = 22; adjmatrix[4][5] = 25; adjmatrix[4][6] = 24;
    adjmatrix[5][0] = 10; adjmatrix[5][4] = 25;
    adjmatrix[6][1] = 14; adjmatrix[6][3] = 18; adjmatrix[6][4] = 24;
}


//����vector����ͼ�ı�Ȩֵ
void SaveArc(int adjmatrix[][vertex_size],vector<Arc> &vectorArc)
{
    Arc * temp = nullptr;
    for (int i = 0; i < vertex_size;i++)
    {
        for (int j = 0; j < i; j++)
        {
            if(adjmatrix[i][j]!=MAX)
            {
                temp = new Arc;
                temp->from = i;
                temp->to = j;
                temp->cost = adjmatrix[i][j];
                vectorArc.push_back(*temp);         //Ԫ�طŵ�β��
            }
        }
    }
}


//A.cost<B.cost����true
bool compare(Arc A,Arc B)
{
    return A.cost < B.cost ? true : false;
}


//from,to���㲻��һ������ϲ�������true 
bool Union(int from,int to,vector<vector<int> > &tree) 
{                                                   //����vector�������Ϊ��̬��ά����
    int index_from = MAX;
    int index_to = MAX;
    for(int i = 0;i < tree.size();i++)              //���from,to�ֱ������Ŀ���
    {                                               //find������ͷ�ļ�algorithm.h�� 
        if(find(tree[i].begin(),tree[i].end(),from) != tree[i].end())
            index_from = i;                         //��tree�е�i��Ѱ��from,�ҵ��򷵻����ַ
        if(find(tree[i].begin(),tree[i].end(),to) != tree[i].end())
            index_to = i;                           //��tree�е�i��Ѱ��to,�ҵ��򷵻����ַ
    }

    if(index_from != index_to)                      //from,to����һ�����ϣ��ϲ�to��from
    {
        for(int i = 0;i < tree[index_to].size();i++)
        {
            tree[index_from].push_back(tree[index_to][i]);
        }
        tree[index_to].clear();                     //�ϲ���ɾ��to
        return true;
    }
    return false;
}


//Kruskal�㷨
void Kruskal(int adjmatrix[][vertex_size])
{
	//ofstream out("MinimumSpanningTree.txt");       //����һ���ļ�MinimumSpanningTree.txt,Ĭ��ios::out,ɾ��ԭ���ļ����ݲ�д�� 
	cout<<"Kruskal�㷨:"<<endl;                      //������ļ�MinimumSpanningTree.txt
    vector<Arc> vertexArc;
    SaveArc(adjmatrix,vertexArc);                   //��ű���Ϣ
    sort(vertexArc.begin(),vertexArc.end(),compare);//�Ա�Ȩֵ��С��������
    vector<vector<int> > tree(vertex_size);         //vertex_size�ö�����

    for(int i = 0;i < vertex_size;i++)
    {
        tree[i].push_back(i);                       //��ʼ��vertex_size�ö���������Ϣ
    }
    for(int i = 0;i < vertexArc.size();i++)         //���δ�С����ȡ��С���۱�
    {
        int from = vertexArc[i].from;  
        int to = vertexArc[i].to;
        if(Union(from,to,tree))                     //���˱ߵ����������Ƿ���һ������
        {                                           //����ͬһ�����������ͬһ����������true
            cout<<"��: "<<vertex[to]<<"-->"<<vertex[from]<<"   ";
            cout<<"Ȩֵ: "<<vertexArc[i].cost<<endl; //������ļ�MinimumSpanningTree.txt 
        }                                           
    }
    //out.close();                                    //�ر��ļ� 
}


//����Prim�㷨�ĸ����ṹ�壬����data������Edge[i]Ȩֵ
struct node
{
    int data;                                       //0��ʾ����A��1��ʾ����B���������ƣ����� 
    int lowestcost;
}Edge[vertex_size];


//������С���۱�
int MinEdge(struct node *Edge)
{
    int min = MAX;
    int edge = -1;
    for(int i = 0;i < vertex_size;i++)
    {
        if(Edge[i].lowestcost < min && Edge[i].lowestcost !=0)
        {
            min = Edge[i].lowestcost;
            edge = i;
        }
    }
    return edge;
}


//Prim�㷨
void Prim(int adjmatrix[][vertex_size],int v)
{
	//ofstream out("MinimumSpanningTree.txt",ios::app);//д���ļ���׷�ӵ�ĩβ 
	cout<<"------------------------\n"<<"Prim�㷨:"<<endl;
    Edge[v].data = v;                               //�Ӷ���v��ʼ
    Edge[v].lowestcost = 0;
    for(int i = 0; i < vertex_size;i++)             //��ʼ����������
    {
        if (i != v)                                 //����������v
        {
            Edge[i].data = v;
            Edge[i].lowestcost = adjmatrix[v][i];
        }
    }
    for(int n = 1;n <= vertex_size-1;n++)           //n-1����ʱ�˳�
    {
        int k = MinEdge(Edge);                      //ѡ����СȨֵ��
        cout<<"��: "<<vertex[Edge[k].data]<<"-->"<<vertex[k]<<"   ";
        cout<<"Ȩֵ: "<<Edge[k].lowestcost<<endl;    //������ļ�mcstree.txt
        Edge[k].lowestcost = 0;                     //Ȩֵ��Ϊ0
        for(int i = 0;i < vertex_size;i++)          //���¶�����С���۱���Ϣ
        {
            if(adjmatrix[k][i] < Edge[i].lowestcost)
            {
                Edge[i].data = k;
                Edge[i].lowestcost = adjmatrix[k][i];
            }
        }
    }
    //out.close();                                    //�ر��ļ� 
}

#endif
