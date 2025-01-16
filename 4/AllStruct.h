#pragma once
#include<vector>
#include<qrect.h>
#include<set>
#include<tuple>
#include"Graphlnk/Graphlnk.h"   //(殷人昆数据结构图模板)

// 枚举类型，表示顶点类型
enum class VertexType
{
    None,        // 无类型
    Site,        // 站点类型
    RoadNode     // 路节点类型
};

// 顶点数据结构
struct VertexData
{
    VertexType type = VertexType::None; // 顶点类型，默认为None
    int index = -1;                     // 数据索引
    float x = 0.0f;                            // 顶点的X坐标
    float y = 0.0f;                            // 顶点的Y坐标
    string name = "";                   // 顶点名称
    string category = "";               // 分类信息

    VertexData() {}                     // 默认构造函数
    VertexData(int) {}                  // 带参数构造函数（空实现）

    // 比较操作符重载，用于判断两个顶点数据是否相等
    bool operator==(const VertexData& other) const
    {
        return type == other.type
            && index == other.index
            && x == other.x
            && y == other.y
            && name == other.name
            && category == other.category;
    }
};

// Dijkstra算法路径和代价结构
struct DjikstraPathsAndCost
{
    float cost = std::numeric_limits<float>::max(); // 路径代价，默认为无穷大
    vector<int> pathIndex;                          // 路径上的顶点索引
};



// 枚举类型，表示图操作的状态
enum class State
{
    AddVertex,      // 添加顶点
    AddEdge,        // 添加边
    CalculatePath,  // 计算路径
    None            // 无操作
};

/*前一个代表数据类型，后一个代表权值类型*/
typedef Edge<VertexData, float> Edgef;
typedef Vertex<VertexData, float> Vertexf;
typedef Graphlnk<VertexData, float> Graphf;

// 图的邻接表表示类，继承自Graphlnk
class GraphAdjList : public Graphf
{
public:
    GraphAdjList(int sz) :Graphf(sz) {};	//构造函数
    ~GraphAdjList() {};		//析构函数

    // 根据数据索引和类型获取顶点在邻接表中的位置
    int getVertexPosByDataIndex(int _index, VertexType type)
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (NodeTable[i].data.type != type)
                continue;
            int index = NodeTable[i].data.index;
            if (index == _index)
                return i;
        }
        return -1;// 未找到对应顶点 
    }

    // 获取所有边的信息，返回一个包含起点、终点和权值的元组列表
    vector<tuple<int, int, float>> getEdges()
    {
        std::set<std::pair<int, int>> visitedEdges; // 用于跟踪已访问的边
        std::vector<std::tuple<int, int, float>> edges; // 存储边的信息

        for (int i = 0; i < numVertices; ++i)
        {
            Edgef* edge = NodeTable[i].adj; // 当前顶点的邻接边表
            while (edge != nullptr)
            {
                int u = i;              // 起点
                int v = edge->dest;     // 终点
                if (visitedEdges.find({ v, u }) == visitedEdges.end())
                { // 如果这条边未被访问过
                    visitedEdges.insert({ u, v }); // 标记为已访问
                    edges.push_back({ u, v, edge->cost });
                }
                edge = edge->link; // 遍历下一条边
            }
        }
        return edges;
    }

    // 根据索引获取指定顶点的指针
    const Vertexf* getVertex(int index)
    {
        if (index < 0 || index >= numVertices)
            return nullptr;
        return &NodeTable[index];
    }
    // 获取所有站点类型的顶点
    const vector<Vertexf*> getAllSiteVertexs()
    {
        vector<Vertexf*> vertexs;
        for (int i = 0; i < numVertices; i++)
        {
            if (NodeTable[i].data.type == VertexType::Site)
            {
                vertexs.push_back(&NodeTable[i]);
            }
        }
        return vertexs;
    }
    // 获取所有路节点类型的顶点
    const vector<Vertexf*> getAllRoadNodeVertexs()
    {
		vector<Vertexf*> vertexs;
        for (int i = 0; i < numVertices; i++)
        {
            if (NodeTable[i].data.type == VertexType::RoadNode)
            {
				vertexs.push_back(&NodeTable[i]);
			}
		}
		return vertexs;
	}
    // 获取站点数量
    int NumberOfSites()
    {
		int count = 0;
        for (int i = 0; i < numVertices; i++)
        {
			if (NodeTable[i].data.type == VertexType::Site)
				count++;
		}
		return count;
	}
    // 获取路节点数量
    int NumberOfRoadNodes()
    {
        int count = 0;
        for (int i = 0; i < numVertices; i++)
        {
			if (NodeTable[i].data.type == VertexType::RoadNode)
				count++;
		}
        return count;
    }
    // 获取图的边界矩形
    QRectF getBoundingRect()
    {
        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::min();
        float maxY = std::numeric_limits<float>::min();

        for (int i = 0; i < numVertices; i++)
        {
            float x = NodeTable[i].data.x;
            float y = NodeTable[i].data.y;
            if (x < minX)
                minX = x;
            if (x > maxX)
                maxX = x;
            if (y < minY)
                minY = y;
            if (y > maxY)
                maxY = y;
        }
        return QRectF(minX, minY, maxX - minX, maxY - minY);
    }


};