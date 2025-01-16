#include "DecisionTree.h"

// 构造函数
DecisionTree::DecisionTree(AlgorithmType algoType) : root(nullptr), algorithmType(algoType) {}

// 析构函数
DecisionTree::~DecisionTree() {
    freeTree(root);
}

// 释放内存
void DecisionTree::freeTree(TreeNode* node) {
    if (!node) return;
    for (auto& branch : node->branches) {
        freeTree(branch.second);
    }
    delete node;
}

// 计算信息熵
double DecisionTree::calculateEntropy(const std::vector<Sample>& samples) const {
    std::map<std::string, int> labelCount;
    for (const auto& sample : samples) {
        labelCount[sample.date]++;
    }

    double entropy = 0.0;
    int total = samples.size();
    for (const auto& pair : labelCount) {
        double p = static_cast<double>(pair.second) / total;
        entropy -= p * log2(p);
    }
    return entropy;
}

// 按属性分组
std::map<std::string, std::vector<Sample>> DecisionTree::splitByAttribute(
    const std::vector<Sample>& samples, const std::string& attribute) const {
    std::map<std::string, std::vector<Sample>> groups;

    for (const auto& sample : samples) {
        std::string value;
        if (attribute == "Weather") value = sample.weather;
        if (attribute == "Temperature") value = sample.temperature;
        if (attribute == "Humidity") value = sample.humidity;
        if (attribute == "Wind") value = sample.wind;

        groups[value].push_back(sample);
    }
    return groups;
}

// 计算信息增益
double DecisionTree::calculateGain(const std::vector<Sample>& samples, const std::string& attribute) const {
    auto groups = splitByAttribute(samples, attribute);
    double totalEntropy = calculateEntropy(samples);
    double weightedEntropy = 0.0;
    int totalSamples = samples.size();

    for (const auto& pair : groups) {
        double p = static_cast<double>(pair.second.size()) / totalSamples;
        weightedEntropy += p * calculateEntropy(pair.second);
    }

    return totalEntropy - weightedEntropy;
}

//计算分裂信息
double DecisionTree::calculateSplitInfo(const std::vector<Sample>& samples, const std::string& attribute) const {
    auto groups = splitByAttribute(samples, attribute);
    double splitInfo = 0.0;
    int totalSamples = samples.size();

    for (const auto& pair : groups) {
        double p = static_cast<double>(pair.second.size()) / totalSamples;
        if (p > 0) {
            splitInfo -= p * log2(p);
        }
    }
    return splitInfo;
}

//计算信息增益率
double DecisionTree::calculateGainRatio(const std::vector<Sample>& samples, const std::string& attribute) const {
    double gain = calculateGain(samples, attribute);
    double splitInfo = calculateSplitInfo(samples, attribute);

    // 避免分母为0
    if (splitInfo == 0) return 0.0;

    return gain / splitInfo;
}



// 构建决策树
TreeNode* DecisionTree::buildTree(const std::vector<Sample>& samples, const std::set<std::string>& attributes) {
    // 如果样本全属于一个类别
    std::string firstLabel = samples.front().date;
    bool allSame = std::all_of(samples.begin(), samples.end(), [&firstLabel](const Sample& s) {
        return s.date == firstLabel;
        });
    if (allSame) {
        TreeNode* leaf = new TreeNode();
        leaf->label = firstLabel;
        return leaf;
    }

    // 如果没有剩余属性
    if (attributes.empty()) {
        TreeNode* leaf = new TreeNode();
        std::map<std::string, int> labelCount;
        for (const auto& sample : samples) {
            labelCount[sample.date]++;
        }

        leaf->label = std::max_element(labelCount.begin(), labelCount.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            })
            ->first;
            return leaf;
    }

    // 选择最佳属性
    double maxMetric = -1;
    std::string bestAttribute;
    for (const auto& attr : attributes) {
        double metric;
        if (algorithmType == ID3) {
            metric = calculateGain(samples, attr); // ID3 使用信息增益
        }
        else {
            metric = calculateGainRatio(samples, attr); // C4.5 使用信息增益率
        }
        if (metric > maxMetric) {
            maxMetric = metric;
            bestAttribute = attr;
        }
    }

    // 创建当前节点
    TreeNode* node = new TreeNode();
    node->attribute = bestAttribute;

    // 按最佳属性划分
    auto groups = splitByAttribute(samples, bestAttribute);

    std::set<std::string> remainingAttributes = attributes;
    remainingAttributes.erase(bestAttribute);

    for (const auto& pair : groups) {
        node->branches[pair.first] = buildTree(pair.second, remainingAttributes);
    }

    return node;
}

// 预测
std::string DecisionTree::predict(const Sample& sample, TreeNode* node) const {
    if (node->label != "") return node->label;

    std::string value;
    if (node->attribute == "Weather") value = sample.weather;
    if (node->attribute == "Temperature") value = sample.temperature;
    if (node->attribute == "Humidity") value = sample.humidity;
    if (node->attribute == "Wind") value = sample.wind;

    auto it = node->branches.find(value);
    if (it != node->branches.end()) {
        return predict(sample, it->second);
    }
    return "Unknown";
}


// 可视化决策树
void DecisionTree::visualizeTree(QGraphicsScene* scene, TreeNode* node, int x, int y, int dx, int dy) const {
    if (!node) return;

    // 节点样式
    int nodeRadius = 20; // 节点半径
    QColor nodeColor = node->label.empty() ? Qt::yellow : Qt::green; // 叶子节点用绿色，非叶子用黄色
    QGraphicsEllipseItem* ellipse = scene->addEllipse(
        x - nodeRadius, y - nodeRadius, nodeRadius * 2, nodeRadius * 2, QPen(Qt::black), QBrush(nodeColor)
    );

    // 节点文字
    QGraphicsTextItem* text = scene->addText(QString::fromStdString(node->label.empty() ? node->attribute : node->label));
    text->setDefaultTextColor(Qt::black);
    text->setFont(QFont("Arial", 10, QFont::Bold));
    text->setPos(x - text->boundingRect().width() / 2, y - text->boundingRect().height() / 2);

    // 如果是叶子节点，终止递归
    if (!node->label.empty()) return;

    // 动态调整分支间距
    int childCount = static_cast<int>(node->branches.size());
    if (childCount == 0) return;

    int totalWidth = (childCount - 1) * dx; // 子节点总宽度
    int startX = x - totalWidth / 2;       // 子节点起始位置

    // 遍历子节点，绘制分支线和递归调用
    int index = 0;
    for (const auto& branch : node->branches) {
        int childX = startX + index * dx; // 子节点X坐标
        int childY = y + dy;              // 子节点Y坐标

        // 绘制分支线
        QGraphicsLineItem* line = scene->addLine(
            x, y + nodeRadius, childX, childY - nodeRadius, QPen(Qt::black, 2)
        );

        // 绘制分支文字
        QGraphicsTextItem* branchText = scene->addText(QString::fromStdString(branch.first));
        branchText->setDefaultTextColor(Qt::darkGray);
        branchText->setFont(QFont("Arial", 10));
        branchText->setPos
        (
            (x + childX) / 2 - branchText->boundingRect().width() / 2,
            (y + childY) / 2 - branchText->boundingRect().height() + 30
        );

        // 递归绘制子节点
        visualizeTree(scene, branch.second, childX, childY, dx / 2, dy);
        ++index;
    }
}

