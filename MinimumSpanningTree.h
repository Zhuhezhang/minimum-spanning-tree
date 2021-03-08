#ifndef MINIMUMSPANNINGTREE_H_
#define MINIMUMSPANNINGTREE_H_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#define MAX 999                                     //表示边的权值无限大
using namespace std;
char vertex[] = {'A','B','C','D','E','F','G'};      //顶点 
#define vertex_size ((sizeof(vertex))/(sizeof(vertex[0])))
                                                    //顶点数量

//图的边信息
typedef struct
{
    int from;                                       //边起点
    int to;                                         //边终点
    int cost;                                       //边的权值
}Arc;


//图的邻接矩阵表示法(课本P371的图结构)
void AdjMatrix(int adjmatrix[][vertex_size])
{
    for(int i = 0;i < vertex_size;i++)              //初始化邻接矩阵
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


//利用vector保存图的边权值
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
                vectorArc.push_back(*temp);         //元素放到尾部
            }
        }
    }
}


//A.cost<B.cost返回true
bool compare(Arc A,Arc B)
{
    return A.cost < B.cost ? true : false;
}


//from,to顶点不在一棵树则合并并返回true 
bool Union(int from,int to,vector<vector<int> > &tree) 
{                                                   //二重vector可以理解为动态二维数组
    int index_from = MAX;
    int index_to = MAX;
    for(int i = 0;i < tree.size();i++)              //检查from,to分别属于哪颗树
    {                                               //find包含在头文件algorithm.h中 
        if(find(tree[i].begin(),tree[i].end(),from) != tree[i].end())
            index_from = i;                         //在tree中的i行寻找from,找到则返回其地址
        if(find(tree[i].begin(),tree[i].end(),to) != tree[i].end())
            index_to = i;                           //在tree中的i行寻找to,找到则返回其地址
    }

    if(index_from != index_to)                      //from,to不在一颗树上，合并to到from
    {
        for(int i = 0;i < tree[index_to].size();i++)
        {
            tree[index_from].push_back(tree[index_to][i]);
        }
        tree[index_to].clear();                     //合并后删除to
        return true;
    }
    return false;
}


//Kruskal算法
void Kruskal(int adjmatrix[][vertex_size])
{
	//ofstream out("MinimumSpanningTree.txt");       //创建一个文件MinimumSpanningTree.txt,默认ios::out,删除原有文件内容并写入 
	cout<<"Kruskal算法:"<<endl;                      //输出至文件MinimumSpanningTree.txt
    vector<Arc> vertexArc;
    SaveArc(adjmatrix,vertexArc);                   //存放边信息
    sort(vertexArc.begin(),vertexArc.end(),compare);//对边权值从小到大排序
    vector<vector<int> > tree(vertex_size);         //vertex_size棵独立树

    for(int i = 0;i < vertex_size;i++)
    {
        tree[i].push_back(i);                       //初始化vertex_size棵独立树的信息
    }
    for(int i = 0;i < vertexArc.size();i++)         //依次从小到大取最小代价边
    {
        int from = vertexArc[i].from;  
        int to = vertexArc[i].to;
        if(Union(from,to,tree))                     //检查此边的两个顶点是否在一颗树内
        {                                           //不在同一棵树，则加入同一棵树并返回true
            cout<<"边: "<<vertex[to]<<"-->"<<vertex[from]<<"   ";
            cout<<"权值: "<<vertexArc[i].cost<<endl; //输出至文件MinimumSpanningTree.txt 
        }                                           
    }
    //out.close();                                    //关闭文件 
}


//用于Prim算法的辅助结构体，顶点data到顶点Edge[i]权值
struct node
{
    int data;                                       //0表示顶点A，1表示顶点B，依此类推，，， 
    int lowestcost;
}Edge[vertex_size];


//返回最小代价边
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


//Prim算法
void Prim(int adjmatrix[][vertex_size],int v)
{
	//ofstream out("MinimumSpanningTree.txt",ios::app);//写入文件被追加到末尾 
	cout<<"------------------------\n"<<"Prim算法:"<<endl;
    Edge[v].data = v;                               //从顶点v开始
    Edge[v].lowestcost = 0;
    for(int i = 0; i < vertex_size;i++)             //初始化辅助数组
    {
        if (i != v)                                 //不包含顶点v
        {
            Edge[i].data = v;
            Edge[i].lowestcost = adjmatrix[v][i];
        }
    }
    for(int n = 1;n <= vertex_size-1;n++)           //n-1条边时退出
    {
        int k = MinEdge(Edge);                      //选择最小权值边
        cout<<"边: "<<vertex[Edge[k].data]<<"-->"<<vertex[k]<<"   ";
        cout<<"权值: "<<Edge[k].lowestcost<<endl;    //输出至文件mcstree.txt
        Edge[k].lowestcost = 0;                     //权值置为0
        for(int i = 0;i < vertex_size;i++)          //更新顶点最小代价边信息
        {
            if(adjmatrix[k][i] < Edge[i].lowestcost)
            {
                Edge[i].data = k;
                Edge[i].lowestcost = adjmatrix[k][i];
            }
        }
    }
    //out.close();                                    //关闭文件 
}

#endif
