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
// ����ͼ�Ĵ�С������1000�����㣩
const int GraphSize = 1000;
// ��������ת���ĺ�������
VertexType getVertexTypeFromStdString(string type);
string getVertexTypeAsString(VertexType type);
// CampusNavigationThread �ฺ����ء������·�����㹦��
class CampusNavigationThread
{
public:
    // ���캯����ʼ��ͼ��ͼ�Ĵ�СΪ�̶�ֵ
    CampusNavigationThread() :mGraph(new GraphAdjList(GraphSize)) {};

    // ���������ͷ�ͼ���ڴ�
    ~CampusNavigationThread() { delete mGraph; }

    // ��JSON�ļ�����ͼ������
    bool LoadGraph(QString path);

    // ��ͼ�����ݱ��浽JSON�ļ�
    bool SaveGraph(QString path);

    // �����ִ��Dijkstra�㷨���������·��
    bool Dijkstra(int startVertexIndex, map<int, DjikstraPathsAndCost>& S_vertexPosAndCost);

    // ��ȡͼ��ָ��
    GraphAdjList* getGraph() { return mGraph; }


protected:
    GraphAdjList* mGraph;  // ͼ�����ݽṹ�����ڴ洢����ͱ�
};

