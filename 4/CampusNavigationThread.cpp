#include "CampusNavigationThread.h"


// 将表示顶点类型的字符串转换为对应的 VertexType 枚举值
VertexType getVertexTypeFromStdString(string type) {
    if (type == "Site")
        return VertexType::Site;  // 如果类型是 "Site"，返回 Site 类型
    else if (type == "RoadNode")
        return VertexType::RoadNode;  // 如果类型是 "RoadNode"，返回 RoadNode 类型
    else
        return VertexType::None;  // 否则返回 None 类型
}

// 将 VertexType 枚举值转换为对应的字符串
string getVertexTypeAsString(VertexType type)
{
    switch (type)
    {
    case VertexType::Site:
        return "Site";  // 返回 "Site"
    case VertexType::RoadNode:
        return "RoadNode";  // 返回 "RoadNode"
    default:
        return "None";  // 返回 "None" 代表无效类型
    }
}

// 从JSON文件加载图的数据
bool CampusNavigationThread::LoadGraph(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  // 如果文件无法打开，返回 false
        return false;

    QByteArray jsonData = file.readAll();  // 读取文件内容
    file.close();  // 关闭文件

    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));  // 解析JSON数据
    QJsonObject root = jsonDoc.object();  // 获取根对象

    QVector<VertexData> AllNodesData;  // 存储所有节点数据

    // 获取所有的 "Site" 数据
    QJsonArray sites = root["Sites"].toArray();
    for (int i = 0; i < sites.size(); i++)
    {
        QJsonObject site = sites[i].toObject();

        // 检查 "Site" 中的必需属性是否存在
        if (!site.contains("Index") || !site.contains("x") || !site.contains("y") || !site.contains("Name") || !site.contains("Category")) {
            continue;  // 如果缺少属性，跳过此节点
        }

        VertexData siteData;
        siteData.type = VertexType::Site;  // 设置节点类型为 Site

        siteData.index = site["Index"].toInt();  // 获取节点索引
        siteData.x = site["x"].toDouble();  // 获取x坐标
        siteData.y = site["y"].toDouble();  // 获取y坐标
        siteData.name = site["Name"].toString().toStdString();  // 获取节点名称
        siteData.category = site["Category"].toString().toStdString();  // 获取节点类别

        AllNodesData.push_back(siteData);  // 将节点数据添加到列表
    }

    // 获取所有的 "RoadNodes" 数据
    QJsonArray roadNodes = root["RoadNodes"].toArray();
    for (int i = 0; i < roadNodes.size(); i++)
    {
        QJsonObject roadNode = roadNodes[i].toObject();

        // 检查 "RoadNode" 中的必需属性是否存在
        if (!roadNode.contains("Index") || !roadNode.contains("x") || !roadNode.contains("y")) {
            continue;  // 如果缺少属性，跳过此节点
        }

        VertexData roadNodeData;
        roadNodeData.type = VertexType::RoadNode;  // 设置节点类型为 RoadNode

        roadNodeData.index = roadNode["Index"].toInt();  // 获取节点索引
        roadNodeData.x = roadNode["x"].toDouble();  // 获取x坐标
        roadNodeData.y = roadNode["y"].toDouble();  // 获取y坐标

        AllNodesData.push_back(roadNodeData);  // 将节点数据添加到列表
    }

    // 添加所有节点到图中
    for (int i = 0; i < AllNodesData.size(); i++)
    {
        mGraph->insertVertex(AllNodesData[i]);
    }

    // 获取所有的 "Edges" 数据
    QJsonArray edges = root["Edges"].toArray();
    // 添加所有的边
    for (int i = 0; i < edges.size(); i++)
    {
        QJsonObject edge = edges[i].toObject();

        int fromIndex = edge["FromIndex"].toInt();  // 获取起始节点索引
        VertexType fromType = getVertexTypeFromStdString(edge["FromType"].toString().toStdString());  // 获取起始节点类型
        int toIndex = edge["ToIndex"].toInt();  // 获取目标节点索引
        VertexType toType = getVertexTypeFromStdString(edge["ToType"].toString().toStdString());  // 获取目标节点类型

        int fromVertexIndex = mGraph->getVertexPosByDataIndex(fromIndex, fromType);  // 查找起始节点在图中的位置
        int toVertexIndex = mGraph->getVertexPosByDataIndex(toIndex, toType);  // 查找目标节点在图中的位置

        if (fromVertexIndex == -1 || toVertexIndex == -1)
            continue;  // 如果无法找到顶点，跳过此边

        float weight = edge["Cost"].toDouble();  // 获取边的权重
        mGraph->insertEdge(fromVertexIndex, toVertexIndex, weight);  // 插入边到图中
    }
    return true;  // 加载成功
}

//将图的数据保存到JSON文件
bool CampusNavigationThread::SaveGraph(QString path)
{
    QJsonObject root;

    // 保存Sites数据
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

    // 保存 RoadNodes 数据
    QJsonArray roadNodesArray;
    const vector<Vertexf*> AllRoadNodes = mGraph->getAllRoadNodeVertexs();  // 获取所有路节点的顶点数据
    for (const auto& roadNode : AllRoadNodes)
    {
        QJsonObject roadNodeObject;
        roadNodeObject["Index"] = roadNode->data.index;
        roadNodeObject["x"] = roadNode->data.x;
        roadNodeObject["y"] = roadNode->data.y;
        roadNodesArray.append(roadNodeObject);
    }
    root["RoadNodes"] = roadNodesArray;

    // 保存Edges数据
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


    // 将图数据保存为JSON数据
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

    // 初始化U集合
    for (int i = 0; i < mGraph->NumberOfVertices(); i++)
    {
        if(i==startVertexIndex)     //起点不加入U集合
			continue;

        float cost = mGraph->getWeight(startVertexIndex, i);
        DjikstraPathsAndCost pathAndCost;
        if(cost != -1)  // 顶点I和起点之间有边
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

    // 初始化S集合
    DjikstraPathsAndCost startPathAndCost;
    startPathAndCost.cost = 0;
    startPathAndCost.pathIndex.push_back(startVertexIndex);
    S_vertexPosAndCost.insert(pair<int, DjikstraPathsAndCost>(startVertexIndex, startPathAndCost));

    while (!U_vertexPosAndCost.empty())
    {
        // 寻找U集合中权值最小的顶点I
        auto minPos = min_element(U_vertexPosAndCost.begin(), U_vertexPosAndCost.end(),
            [](const pair<int, DjikstraPathsAndCost>& a, const pair<int, DjikstraPathsAndCost>& b) { return a.second.cost < b.second.cost; });

        S_vertexPosAndCost.insert(*minPos);        // 将权值最小的顶点I加入S集合

        float oldCost = minPos->second.cost;     // 起点到顶点I的距离
        vector<int> oldPath = minPos->second.pathIndex;  // 起点到顶点I的路径

        // 从U集合中移除顶点I
        int minIndex = minPos->first;
        U_vertexPosAndCost.erase(minPos);

        // 更新U集合中的各顶点到起点的距离
        for (auto& K_pair : U_vertexPosAndCost)
        {
            int i = K_pair.first;
            float minCost = K_pair.second.cost;

            float newCost = mGraph->getWeight(minIndex, i);     // 顶点K和顶点I之间的距离

            if (newCost == -1)  // 顶点K和顶点I之间没有边,保持原来的距离
                continue;

            newCost += oldCost;     // 顶点K到起点的距离

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