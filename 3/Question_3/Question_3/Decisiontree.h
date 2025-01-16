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

// �������ݽṹ
struct Sample {
    std::string weather;
    std::string temperature;
    std::string humidity;
    std::string wind;
    std::string date; // ��ǩ�У�yes/no
};

// �������ڵ�ṹ
struct TreeNode {
    std::string attribute;                    // ��ǰ�ڵ���ѵ�����
    std::map<std::string, TreeNode*> branches; // ÿ����ָ֧����ӽڵ�
    std::string label;                        // Ҷ�ӽڵ����yes/no��
};

//����һ��ö������Ϊ�㷨ѡ��
enum AlgorithmType {
    ID3,
    C45
};

// ��������
class DecisionTree {
public:
    TreeNode* root; // ���������ڵ�
    AlgorithmType algorithmType; // �㷨���ͣ�ID3 �� C4.5


    DecisionTree(AlgorithmType algoType = ID3); // ���캯��֧��ѡ���㷨(Ĭ��ΪID3)
    ~DecisionTree();

    TreeNode* buildTree(const std::vector<Sample>& samples, const std::set<std::string>& attributes); // ����������
    std::string predict(const Sample& sample, TreeNode* node) const; // Ԥ��
    void visualizeTree(QGraphicsScene* scene, TreeNode* node, int x, int y, int dx, int dy) const; // ���ӻ�������

private:
    double calculateEntropy(const std::vector<Sample>& samples) const; // ������Ϣ��
    double calculateGain(const std::vector<Sample>& samples, const std::string& attribute) const; // ������Ϣ����
    double calculateGainRatio(const std::vector<Sample>& samples, const std::string& attribute) const; //������Ϣ������
    double calculateSplitInfo(const std::vector<Sample>& samples, const std::string& attribute) const; //���������Ϣ
    std::map<std::string, std::vector<Sample>> splitByAttribute(const std::vector<Sample>& samples, const std::string& attribute) const; // �����Է���
    void freeTree(TreeNode* node); // ��ʱdelete�ڵ��ͷ��ڴ�
};

#endif // DECISIONTREE_H
