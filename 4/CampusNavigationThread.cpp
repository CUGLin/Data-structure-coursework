#include "CampusNavigationThread.h"


// ����ʾ�������͵��ַ���ת��Ϊ��Ӧ�� VertexType ö��ֵ
VertexType getVertexTypeFromStdString(string type) {
    if (type == "Site")
        return VertexType::Site;  // ��������� "Site"������ Site ����
    else if (type == "RoadNode")
        return VertexType::RoadNode;  // ��������� "RoadNode"������ RoadNode ����
    else
        return VertexType::None;  // ���򷵻� None ����
}

// �� VertexType ö��ֵת��Ϊ��Ӧ���ַ���
string getVertexTypeAsString(VertexType type)
{
    switch (type)
    {
    case VertexType::Site:
        return "Site";  // ���� "Site"
    case VertexType::RoadNode:
        return "RoadNode";  // ���� "RoadNode"
    default:
        return "None";  // ���� "None" ������Ч����
    }
}

// ��JSON�ļ�����ͼ������
bool CampusNavigationThread::LoadGraph(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  // ����ļ��޷��򿪣����� false
        return false;

    QByteArray jsonData = file.readAll();  // ��ȡ�ļ�����
    file.close();  // �ر��ļ�

    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));  // ����JSON����
    QJsonObject root = jsonDoc.object();  // ��ȡ������

    QVector<VertexData> AllNodesData;  // �洢���нڵ�����

    // ��ȡ���е� "Site" ����
    QJsonArray sites = root["Sites"].toArray();
    for (int i = 0; i < sites.size(); i++)
    {
        QJsonObject site = sites[i].toObject();

        // ��� "Site" �еı��������Ƿ����
        if (!site.contains("Index") || !site.contains("x") || !site.contains("y") || !site.contains("Name") || !site.contains("Category")) {
            continue;  // ���ȱ�����ԣ������˽ڵ�
        }

        VertexData siteData;
        siteData.type = VertexType::Site;  // ���ýڵ�����Ϊ Site

        siteData.index = site["Index"].toInt();  // ��ȡ�ڵ�����
        siteData.x = site["x"].toDouble();  // ��ȡx����
        siteData.y = site["y"].toDouble();  // ��ȡy����
        siteData.name = site["Name"].toString().toStdString();  // ��ȡ�ڵ�����
        siteData.category = site["Category"].toString().toStdString();  // ��ȡ�ڵ����

        AllNodesData.push_back(siteData);  // ���ڵ�������ӵ��б�
    }

    // ��ȡ���е� "RoadNodes" ����
    QJsonArray roadNodes = root["RoadNodes"].toArray();
    for (int i = 0; i < roadNodes.size(); i++)
    {
        QJsonObject roadNode = roadNodes[i].toObject();

        // ��� "RoadNode" �еı��������Ƿ����
        if (!roadNode.contains("Index") || !roadNode.contains("x") || !roadNode.contains("y")) {
            continue;  // ���ȱ�����ԣ������˽ڵ�
        }

        VertexData roadNodeData;
        roadNodeData.type = VertexType::RoadNode;  // ���ýڵ�����Ϊ RoadNode

        roadNodeData.index = roadNode["Index"].toInt();  // ��ȡ�ڵ�����
        roadNodeData.x = roadNode["x"].toDouble();  // ��ȡx����
        roadNodeData.y = roadNode["y"].toDouble();  // ��ȡy����

        AllNodesData.push_back(roadNodeData);  // ���ڵ�������ӵ��б�
    }

    // ������нڵ㵽ͼ��
    for (int i = 0; i < AllNodesData.size(); i++)
    {
        mGraph->insertVertex(AllNodesData[i]);
    }

    // ��ȡ���е� "Edges" ����
    QJsonArray edges = root["Edges"].toArray();
    // ������еı�
    for (int i = 0; i < edges.size(); i++)
    {
        QJsonObject edge = edges[i].toObject();

        int fromIndex = edge["FromIndex"].toInt();  // ��ȡ��ʼ�ڵ�����
        VertexType fromType = getVertexTypeFromStdString(edge["FromType"].toString().toStdString());  // ��ȡ��ʼ�ڵ�����
        int toIndex = edge["ToIndex"].toInt();  // ��ȡĿ��ڵ�����
        VertexType toType = getVertexTypeFromStdString(edge["ToType"].toString().toStdString());  // ��ȡĿ��ڵ�����

        int fromVertexIndex = mGraph->getVertexPosByDataIndex(fromIndex, fromType);  // ������ʼ�ڵ���ͼ�е�λ��
        int toVertexIndex = mGraph->getVertexPosByDataIndex(toIndex, toType);  // ����Ŀ��ڵ���ͼ�е�λ��

        if (fromVertexIndex == -1 || toVertexIndex == -1)
            continue;  // ����޷��ҵ����㣬�����˱�

        float weight = edge["Cost"].toDouble();  // ��ȡ�ߵ�Ȩ��
        mGraph->insertEdge(fromVertexIndex, toVertexIndex, weight);  // ����ߵ�ͼ��
    }
    return true;  // ���سɹ�
}

//��ͼ�����ݱ��浽JSON�ļ�
bool CampusNavigationThread::SaveGraph(QString path)
{
    QJsonObject root;

    // ����Sites����
    QJsonArray sitesArray;
    

    const vector<Vertexf*> AllSites = mGraph->getAllSiteVertexs();
    for (const auto& site : AllSites)
    {
        QJsonObject siteObject;
        siteObject["Index"] = site->data.index;
        siteObject["x"] = site->data.x;
        siteObject["y"] = site->data.y;
        siteObject["Name"] = QString::fromStdString(site->data.name);
        siteObject["Category"] = QString::fromStdString(site->data.category);
        sitesArray.append(siteObject);
    }
    root["Sites"] = sitesArray;

    // ���� RoadNodes ����
    QJsonArray roadNodesArray;
    const vector<Vertexf*> AllRoadNodes = mGraph->getAllRoadNodeVertexs();  // ��ȡ����·�ڵ�Ķ�������
    for (const auto& roadNode : AllRoadNodes)
    {
        QJsonObject roadNodeObject;
        roadNodeObject["Index"] = roadNode->data.index;
        roadNodeObject["x"] = roadNode->data.x;
        roadNodeObject["y"] = roadNode->data.y;
        roadNodesArray.append(roadNodeObject);
    }
    root["RoadNodes"] = roadNodesArray;

    // ����Edges����
    QJsonArray edgesArray;
    vector<tuple<int, int, float>> edges = mGraph->getEdges();

    for (const auto& edge : edges)
    {
        QJsonObject edgeObject;
        edgeObject["FromType"] = QString::fromStdString(getVertexTypeAsString(mGraph->getValue(std::get<0>(edge)).type));
        edgeObject["FromIndex"] = mGraph->getValue(std::get<0>(edge)).index;
        edgeObject["ToType"] = QString::fromStdString(getVertexTypeAsString(mGraph->getValue(std::get<1>(edge)).type));
        edgeObject["ToIndex"] = mGraph->getValue(std::get<1>(edge)).index;
        edgeObject["Cost"] = std::get<2>(edge);
        edgesArray.append(edgeObject);
    }
    root["Edges"] = edgesArray;


    // ��ͼ���ݱ���ΪJSON����
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument jsonDoc(root);
        file.write(jsonDoc.toJson());
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool CampusNavigationThread::Dijkstra(int startVertexIndex, map<int, DjikstraPathsAndCost>& S_vertexPosAndCost)
{

	if (startVertexIndex <  0 || startVertexIndex >= mGraph->NumberOfVertices())
		return false;
    
    map<int,DjikstraPathsAndCost> U_vertexPosAndCost;

    // ��ʼ��U����
    for (int i = 0; i < mGraph->NumberOfVertices(); i++)
    {
        if(i==startVertexIndex)     //��㲻����U����
			continue;

        float cost = mGraph->getWeight(startVertexIndex, i);
        DjikstraPathsAndCost pathAndCost;
        if(cost != -1)  // ����I�����֮���б�
        {
            pathAndCost.cost = cost;
        }
        else
        {
            pathAndCost.cost = std::numeric_limits<float>::max();
        }
        pathAndCost.pathIndex.push_back(i);
        U_vertexPosAndCost.insert(pair<int, DjikstraPathsAndCost>(i, pathAndCost));
    }

    // ��ʼ��S����
    DjikstraPathsAndCost startPathAndCost;
    startPathAndCost.cost = 0;
    startPathAndCost.pathIndex.push_back(startVertexIndex);
    S_vertexPosAndCost.insert(pair<int, DjikstraPathsAndCost>(startVertexIndex, startPathAndCost));

    while (!U_vertexPosAndCost.empty())
    {
        // Ѱ��U������Ȩֵ��С�Ķ���I
        auto minPos = min_element(U_vertexPosAndCost.begin(), U_vertexPosAndCost.end(),
            [](const pair<int, DjikstraPathsAndCost>& a, const pair<int, DjikstraPathsAndCost>& b) { return a.second.cost < b.second.cost; });

        S_vertexPosAndCost.insert(*minPos);        // ��Ȩֵ��С�Ķ���I����S����

        float oldCost = minPos->second.cost;     // ��㵽����I�ľ���
        vector<int> oldPath = minPos->second.pathIndex;  // ��㵽����I��·��

        // ��U�������Ƴ�����I
        int minIndex = minPos->first;
        U_vertexPosAndCost.erase(minPos);

        // ����U�����еĸ����㵽���ľ���
        for (auto& K_pair : U_vertexPosAndCost)
        {
            int i = K_pair.first;
            float minCost = K_pair.second.cost;

            float newCost = mGraph->getWeight(minIndex, i);     // ����K�Ͷ���I֮��ľ���

            if (newCost == -1)  // ����K�Ͷ���I֮��û�б�,����ԭ���ľ���
                continue;

            newCost += oldCost;     // ����K�����ľ���

            if (newCost < minCost)
            {
                K_pair.second.cost = newCost;
                K_pair.second.pathIndex = oldPath;
                K_pair.second.pathIndex.push_back(i);
            }
        }
    }
	return true;
}