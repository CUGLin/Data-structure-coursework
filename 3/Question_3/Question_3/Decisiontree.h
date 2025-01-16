#pragma once

#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QString>
#include <QDebug>

// 样本数据结构
struct Sample {
    std::string weather;
    std::string temperature;
    std::string humidity;
    std::string wind;
    std::string date; // 标签列：yes/no
};

// 决策树节点结构
struct TreeNode {
    std::string attribute;                    // 当前节点分裂的属性
    std::map<std::string, TreeNode*> branches; // 每个分支指向的子节点
    std::string label;                        // 叶子节点类别（yes/no）
};

//增加一个枚举类作为算法选择
enum AlgorithmType {
    ID3,
    C45
};

// 决策树类
class DecisionTree {
public:
    TreeNode* root; // 决策树根节点
    AlgorithmType algorithmType; // 算法类型：ID3 或 C4.5


    DecisionTree(AlgorithmType algoType = ID3); // 构造函数支持选择算法(默认为ID3)
    ~DecisionTree();

    TreeNode* buildTree(const std::vector<Sample>& samples, const std::set<std::string>& attributes); // 构建决策树
    std::string predict(const Sample& sample, TreeNode* node) const; // 预测
    void visualizeTree(QGraphicsScene* scene, TreeNode* node, int x, int y, int dx, int dy) const; // 可视化决策树

private:
    double calculateEntropy(const std::vector<Sample>& samples) const; // 计算信息熵
    double calculateGain(const std::vector<Sample>& samples, const std::string& attribute) const; // 计算信息增益
    double calculateGainRatio(const std::vector<Sample>& samples, const std::string& attribute) const; //计算信息增益率
    double calculateSplitInfo(const std::vector<Sample>& samples, const std::string& attribute) const; //计算分裂信息
    std::map<std::string, std::vector<Sample>> splitByAttribute(const std::vector<Sample>& samples, const std::string& attribute) const; // 按属性分组
    void freeTree(TreeNode* node); // 及时delete节点释放内存
};

#endif // DECISIONTREE_H
