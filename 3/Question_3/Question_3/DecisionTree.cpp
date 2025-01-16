#include "DecisionTree.h"

// ���캯��
DecisionTree::DecisionTree(AlgorithmType algoType) : root(nullptr), algorithmType(algoType) {}

// ��������
DecisionTree::~DecisionTree() {
    freeTree(root);
}

// �ͷ��ڴ�
void DecisionTree::freeTree(TreeNode* node) {
    if (!node) return;
    for (auto& branch : node->branches) {
        freeTree(branch.second);
    }
    delete node;
}

// ������Ϣ��
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

// �����Է���
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

// ������Ϣ����
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

//���������Ϣ
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

//������Ϣ������
double DecisionTree::calculateGainRatio(const std::vector<Sample>& samples, const std::string& attribute) const {
    double gain = calculateGain(samples, attribute);
    double splitInfo = calculateSplitInfo(samples, attribute);

    // �����ĸΪ0
    if (splitInfo == 0) return 0.0;

    return gain / splitInfo;
}



// ����������
TreeNode* DecisionTree::buildTree(const std::vector<Sample>& samples, const std::set<std::string>& attributes) {
    // �������ȫ����һ�����
    std::string firstLabel = samples.front().date;
    bool allSame = std::all_of(samples.begin(), samples.end(), [&firstLabel](const Sample& s) {
        return s.date == firstLabel;
        });
    if (allSame) {
        TreeNode* leaf = new TreeNode();
        leaf->label = firstLabel;
        return leaf;
    }

    // ���û��ʣ������
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

    // ѡ���������
    double maxMetric = -1;
    std::string bestAttribute;
    for (const auto& attr : attributes) {
        double metric;
        if (algorithmType == ID3) {
            metric = calculateGain(samples, attr); // ID3 ʹ����Ϣ����
        }
        else {
            metric = calculateGainRatio(samples, attr); // C4.5 ʹ����Ϣ������
        }
        if (metric > maxMetric) {
            maxMetric = metric;
            bestAttribute = attr;
        }
    }

    // ������ǰ�ڵ�
    TreeNode* node = new TreeNode();
    node->attribute = bestAttribute;

    // ��������Ի���
    auto groups = splitByAttribute(samples, bestAttribute);

    std::set<std::string> remainingAttributes = attributes;
    remainingAttributes.erase(bestAttribute);

    for (const auto& pair : groups) {
        node->branches[pair.first] = buildTree(pair.second, remainingAttributes);
    }

    return node;
}

// Ԥ��
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


// ���ӻ�������
void DecisionTree::visualizeTree(QGraphicsScene* scene, TreeNode* node, int x, int y, int dx, int dy) const {
    if (!node) return;

    // �ڵ���ʽ
    int nodeRadius = 20; // �ڵ�뾶
    QColor nodeColor = node->label.empty() ? Qt::yellow : Qt::green; // Ҷ�ӽڵ�����ɫ����Ҷ���û�ɫ
    QGraphicsEllipseItem* ellipse = scene->addEllipse(
        x - nodeRadius, y - nodeRadius, nodeRadius * 2, nodeRadius * 2, QPen(Qt::black), QBrush(nodeColor)
    );

    // �ڵ�����
    QGraphicsTextItem* text = scene->addText(QString::fromStdString(node->label.empty() ? node->attribute : node->label));
    text->setDefaultTextColor(Qt::black);
    text->setFont(QFont("Arial", 10, QFont::Bold));
    text->setPos(x - text->boundingRect().width() / 2, y - text->boundingRect().height() / 2);

    // �����Ҷ�ӽڵ㣬��ֹ�ݹ�
    if (!node->label.empty()) return;

    // ��̬������֧���
    int childCount = static_cast<int>(node->branches.size());
    if (childCount == 0) return;

    int totalWidth = (childCount - 1) * dx; // �ӽڵ��ܿ��
    int startX = x - totalWidth / 2;       // �ӽڵ���ʼλ��

    // �����ӽڵ㣬���Ʒ�֧�ߺ͵ݹ����
    int index = 0;
    for (const auto& branch : node->branches) {
        int childX = startX + index * dx; // �ӽڵ�X����
        int childY = y + dy;              // �ӽڵ�Y����

        // ���Ʒ�֧��
        QGraphicsLineItem* line = scene->addLine(
            x, y + nodeRadius, childX, childY - nodeRadius, QPen(Qt::black, 2)
        );

        // ���Ʒ�֧����
        QGraphicsTextItem* branchText = scene->addText(QString::fromStdString(branch.first));
        branchText->setDefaultTextColor(Qt::darkGray);
        branchText->setFont(QFont("Arial", 10));
        branchText->setPos
        (
            (x + childX) / 2 - branchText->boundingRect().width() / 2,
            (y + childY) / 2 - branchText->boundingRect().height() + 30
        );

        // �ݹ�����ӽڵ�
        visualizeTree(scene, branch.second, childX, childY, dx / 2, dy);
        ++index;
    }
}

