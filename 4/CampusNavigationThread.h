#pragma once
#include<vector>
#include<fstream>
#include<string>
#include<unordered_set>
#include<qdebug.h>
#include<qfile.h>
#include<qbytearray.h>
#include<qjsonarray.h>
#include<qvector.h>
#include<qjsonobject.h>
#include<qjsondocument.h>
#include"AllStruct.h"
// 定义图的大小常量（1000个顶点）
const int GraphSize = 1000;
// 顶点类型转换的函数声明
VertexType getVertexTypeFromStdString(string type);
string getVertexTypeAsString(VertexType type);
// CampusNavigationThread 类负责加载、保存和路径计算功能
class CampusNavigationThread
{
public:
    // 构造函数初始化图，图的大小为固定值
    CampusNavigationThread() :mGraph(new GraphAdjList(GraphSize)) {};

    // 析构函数释放图的内存
    ~CampusNavigationThread() { delete mGraph; }

    // 从JSON文件加载图的数据
    bool LoadGraph(QString path);

    // 将图的数据保存到JSON文件
    bool SaveGraph(QString path);

    // 从起点执行Dijkstra算法，计算最短路径
    bool Dijkstra(int startVertexIndex, map<int, DjikstraPathsAndCost>& S_vertexPosAndCost);

    // 获取图的指针
    GraphAdjList* getGraph() { return mGraph; }


protected:
    GraphAdjList* mGraph;  // 图的数据结构，用于存储顶点和边
};

