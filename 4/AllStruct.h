#pragma once
#include<vector>
#include<qrect.h>
#include<set>
#include<tuple>
#include"Graphlnk/Graphlnk.h"   //(���������ݽṹͼģ��)

// ö�����ͣ���ʾ��������
enum class VertexType
{
    None,        // ������
    Site,        // վ������
    RoadNode     // ·�ڵ�����
};

// �������ݽṹ
struct VertexData
{
    VertexType type = VertexType::None; // �������ͣ�Ĭ��ΪNone
    int index = -1;                     // ��������
    float x = 0.0f;                            // �����X����
    float y = 0.0f;                            // �����Y����
    string name = "";                   // ��������
    string category = "";               // ������Ϣ

    VertexData() {}                     // Ĭ�Ϲ��캯��
    VertexData(int) {}                  // ���������캯������ʵ�֣�

    // �Ƚϲ��������أ������ж��������������Ƿ����
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

// Dijkstra�㷨·���ʹ��۽ṹ
struct DjikstraPathsAndCost
{
    float cost = std::numeric_limits<float>::max(); // ·�����ۣ�Ĭ��Ϊ�����
    vector<int> pathIndex;                          // ·���ϵĶ�������
};



// ö�����ͣ���ʾͼ������״̬
enum class State
{
    AddVertex,      // ��Ӷ���
    AddEdge,        // ��ӱ�
    CalculatePath,  // ����·��
    None            // �޲���
};

/*ǰһ�������������ͣ���һ������Ȩֵ����*/
typedef Edge<VertexData, float> Edgef;
typedef Vertex<VertexData, float> Vertexf;
typedef Graphlnk<VertexData, float> Graphf;

// ͼ���ڽӱ��ʾ�࣬�̳���Graphlnk
class GraphAdjList : public Graphf
{
public:
    GraphAdjList(int sz) :Graphf(sz) {};	//���캯��
    ~GraphAdjList() {};		//��������

    // �����������������ͻ�ȡ�������ڽӱ��е�λ��
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
        return -1;// δ�ҵ���Ӧ���� 
    }

    // ��ȡ���бߵ���Ϣ������һ��������㡢�յ��Ȩֵ��Ԫ���б�
    vector<tuple<int, int, float>> getEdges()
    {
        std::set<std::pair<int, int>> visitedEdges; // ���ڸ����ѷ��ʵı�
        std::vector<std::tuple<int, int, float>> edges; // �洢�ߵ���Ϣ

        for (int i = 0; i < numVertices; ++i)
        {
            Edgef* edge = NodeTable[i].adj; // ��ǰ������ڽӱ߱�
            while (edge != nullptr)
            {
                int u = i;              // ���
                int v = edge->dest;     // �յ�
                if (visitedEdges.find({ v, u }) == visitedEdges.end())
                { // ���������δ�����ʹ�
                    visitedEdges.insert({ u, v }); // ���Ϊ�ѷ���
                    edges.push_back({ u, v, edge->cost });
                }
                edge = edge->link; // ������һ����
            }
        }
        return edges;
    }

    // ����������ȡָ�������ָ��
    const Vertexf* getVertex(int index)
    {
        if (index < 0 || index >= numVertices)
            return nullptr;
        return &NodeTable[index];
    }
    // ��ȡ����վ�����͵Ķ���
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
    // ��ȡ����·�ڵ����͵Ķ���
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
    // ��ȡվ������
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
    // ��ȡ·�ڵ�����
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
    // ��ȡͼ�ı߽����
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