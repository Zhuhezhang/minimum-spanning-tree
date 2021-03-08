@[TOC](目录)
# 1.题目
【问题描述】
    若要在n个城市之间建设通信网络，只需要架设n-1条路线即可。如何以最低的经济代价建设这个通信网，是一个网的最小生成树问题。
【基本要求】
   （1）利用克鲁斯卡尔算法求网的最小生成树，其中，以课本中的等价类表示构造生成树过程中的连通分量；
   （2）利用普里姆算法求网的最小生成树；
   （3）以文本文件形式输出生成树中各条边及它们的权值。
# 2.程序设计
本程序定义两个文件：一个是存放主函数的文件mcstree.cpp，另一个是存放算法用到的函数声明和定义的头文件mcstree_head.h。
主函数文件较简单：包含一个图的邻接矩阵存储结构定义以及赋值，还有对Kruskal算法和Prim算法的调用。接着是头文件：程序前面定义边权值的最大值MAX=999，表示权值无穷大，两顶点之间不可达，还有定义ABCDEFG分别表示七个顶点以及顶点数量vertexsize。后面是图边信息的结构体变量Arc，包含边的起点和终点（所定义的是无向图，为了更好的表示才这样说）以及权值。接着就是图的邻接矩阵表示法，也就是用初始化其参数的函数，包括边（利用二维数组坐标表示）以及权值。接着就是为了方便更好的操作利用vector来保存图的边权值，并通过数据类型为vector<Arc>的形参vectorArc返回，函数比较简单，利用循环依次把邻接矩阵的所有数据传入即可，并将一组数组作为整体依次放入容器尾部。
然后就是比较数据类型为Arc的变量AB之间的权值的函数，A的小返回true，否则返回false。将顶点为from和to的边不在一棵树则合并并且返回true的函数Union。形参除了from和to还有一个二重vector的tree(为了更好的认识，可以将其理解为一个动态的二维数组)，利用循环依次判定数组每行中是否同时存在from和to（其中利用了在头文件algorithm.h中定义的函数find，在每行中寻找，其中的参数tree[i].end指的是该行元素的最后一位的后一位，也即为空），若不是同一棵树，则利用push_back把to的所在的行的顶点全部添加到from的中，并利用clear删除删除to所在的树（行）并返回true，否则返回false。
接下来是Kruskal算法算法主体函数：利用ofstream out("mcstree.txt")创建一个文件mcstree.txt和文件输出流out,默认ios::out,删除原有文件内容并写入。接下来是调用SaveArc(adjmatrix,vertexArc)存放边信息以及利用库函数sort将vertexArc里面的边从小大到排序好，利用for循环以及push_back初始化初始化vertex_size棵独立树的信息，依次检查此边的两个顶点是否在一颗树内，若不在，则合并并将其输出至文本文件，最后关闭文件即可。后面就是Prim算法的相关部分。首先是定义其辅助结构体数组（大小为vertex_size），含有data(0表示顶点A，1表示顶点B，依此类推，，，)，以及边权值lowestcost，特别说明的是这个结构体数组表示每次计算顶临接边的最小权值时用到的，根据计算的顶点权值来改变，例如Edge[2]而data为0表示此时所有结构数组的的data为0，计算结构体存放的是顶点A到每个顶点的边的权值。
接下来就是通过上面的结构体来返回最小权值的函数，函数返回参数即为结构体数组中最小权值对应的结构体坐标。Prim算法主体：利用上面定义的文本文件mcstree.txt输出数据，只不过文件打开方式为ios::app，表示不清除原来数据，在文件未加入新的数据。确定算法开始的顶点，然后初始化Prim算法的辅助数组（除了选定的算法开始顶点v），利用循环依次旋转边，直到vertex_size-1条边时退出循环，先根据排序后权值输出最小边至文件，之后将其对应的权值置为0，然后利用循环依次更新结构体数组Edge里面顶点最小代价边信息即可，最后在关闭文件。至此，所有代码说明结束。
# 3.测试结果
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021030822040431.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308220410862.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)
